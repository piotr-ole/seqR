#ifndef SEQR_FIND_KMERS_STRING_MATRIX_H
#define SEQR_FIND_KMERS_STRING_MATRIX_H

#include <Rcpp.h>
#include <vector>
#include "../kmer_task_config.h"
#include "../default_alphabet_encoder.h"
#include "../dictionary/unordered_map_wrapper.h"
#include "../kmer_counting_result.h"
#include "../kmer_task_solver.h"
#include "../sequence_getter.h"
#include "../common_config.h"

template<class encoded_elem_t>
class FastStringMatrixWrapper {
public:

    class Row {
    public:
        Row(std::shared_ptr<encoded_elem_t[]> encoded, int begin, int size)
                : encoded_(std::move(encoded)), begin_(begin), size_(size) {}

        inline const encoded_elem_t &operator[](int index) const {
            return this->encoded_[begin_ + index];
        }

        inline std::size_t size() const {
            return this->size_;
        }

    private:
        std::shared_ptr<encoded_elem_t[]> encoded_;
        std::size_t begin_, size_;
    };

    FastStringMatrixWrapper(Rcpp::StringMatrix &matrix,
                            std::unordered_map<Rcpp::StringMatrix::stored_type, encoded_elem_t> &encoder,
                            int notAllowedEncodingNum,
                            int begin, int end) :
            nrow(end - begin), ncol(matrix.ncol()) {
        this->encoded = std::move(std::shared_ptr<encoded_elem_t[]>(new encoded_elem_t[nrow * ncol]));

        for (int r = begin; r < end; ++r) {
            for (int c = 0; c < ncol; ++c) {
                int encodedIndex = (r - begin) * ncol + c;
                auto matrixElem = matrix(r, c);
                encoded[encodedIndex] = encoder.find(matrixElem) != encoder.end() ?
                                        encoder[matrixElem] :
                                        notAllowedEncodingNum;
            }
        }
    }

    inline Row row(int index) {
        return std::move(Row(encoded, index * ncol, ncol));
    }

private:
    std::shared_ptr<encoded_elem_t[]> encoded;
    int ncol, nrow;
};

template<class encoded_elem_t_>
class IdentityAlphabetEncoder {
public:
    using encoded_elem_t = encoded_elem_t_;
    using input_elem_t = encoded_elem_t;

    IdentityAlphabetEncoder(encoded_elem_t_ allowedBegin,
                            encoded_elem_t_ allowedEnd)
            : allowedBegin(allowedBegin), allowedEnd(allowedEnd) {}

    inline encoded_elem_t encode(const input_elem_t &inputElem) {
        return inputElem;
    }

    inline encoded_elem_t encodeUnsafe(const input_elem_t &inputElem) {
        return encode(inputElem);
    }

    inline bool isAllowed(const input_elem_t &inputElem) const {
        return allowedBegin <= inputElem && inputElem <= allowedEnd;
    }

    inline std::size_t size() const {
        return (allowedEnd - allowedBegin + 1);
    }

private:
    encoded_elem_t_ allowedBegin, allowedEnd;

};

template<class encoded_elem_t>
inline SequenceGetter_t<typename FastStringMatrixWrapper<encoded_elem_t>::Row>
getFastEncodedMatrixGetter(FastStringMatrixWrapper<encoded_elem_t> &wrapper, int rowOffset = 0) {
    return [&wrapper, rowOffset](int rowNum) -> typename FastStringMatrixWrapper<encoded_elem_t>::Row {
        return std::move(wrapper.row(rowNum + rowOffset));
    };
}

template<class algorithm_params_t>
inline
Rcpp::List findKMersSpecific(Rcpp::StringMatrix &sequenceMatrix,
                             Rcpp::StringVector &alphabet,
                             std::vector<int> &gaps,
                             bool positionalKMers,
                             bool withKMerCounts,
                             const std::string &kmerDictionaryName,
                             int batchSize,
                             bool verbose,
                             algorithm_params_t &algorithmParams) {
    using encoded_elem_t = config::encoded_elem_t;
    std::unordered_map<Rcpp::StringVector::stored_type, encoded_elem_t> stringAlphabetEncoder;
    std::vector<std::string> alphabetStrings;
    encoded_elem_t alphabetBeginCnt = 1;
    encoded_elem_t alphabetCnt = alphabetBeginCnt;
    for (const auto &alphabetElem: alphabet) {
        if (stringAlphabetEncoder.find(alphabetElem) == stringAlphabetEncoder.end()) {
            stringAlphabetEncoder[alphabetElem] = alphabetCnt++;
            alphabetStrings.push_back(Rcpp::as<std::string>(alphabetElem));
        }
    }
    IdentityAlphabetEncoder<encoded_elem_t> alphabetEncoder(alphabetBeginCnt, alphabetCnt - 1);

    auto batchFunc = [&](KMerCountingResult &kMerCountingResult, int seqBegin, int seqEnd) {
        FastStringMatrixWrapper<encoded_elem_t> safeMatrixWrapper(sequenceMatrix,
                                                                  stringAlphabetEncoder,
                                                                   alphabetBeginCnt - 1,
                                                                  seqBegin, seqEnd);
        KMerTaskConfig<typename decltype(safeMatrixWrapper)::Row, decltype(alphabetEncoder)::input_elem_t> kMerTaskConfig(
                (seqEnd - seqBegin),
                getFastEncodedMatrixGetter<encoded_elem_t>(safeMatrixWrapper),
                gaps,
                positionalKMers,
                withKMerCounts,
                [&alphabetStrings](const encoded_elem_t& encodedElem) -> std::string { return alphabetStrings[encodedElem - 1]; },
                DEFAULT_KMER_ITEM_SEPARATOR,
                DEFAULT_KMER_SECTION_SEPARATOR);
        computeResult<
                typename decltype(safeMatrixWrapper)::Row,
                decltype(alphabetEncoder)::input_elem_t,
                decltype(alphabetEncoder),
                algorithm_params_t>(kMerTaskConfig,
                                    alphabetEncoder,
                                    kmerDictionaryName,
                                    algorithmParams,
                                    kMerCountingResult);
    };

    return computeKMersInBatches(batchFunc, sequenceMatrix.nrow(), batchSize, verbose);
}


#endif //SEQR_FIND_KMERS_STRING_MATRIX_H