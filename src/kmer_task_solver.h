#ifndef SEQR_KMER_TASK_SOLVER_H
#define SEQR_KMER_TASK_SOLVER_H

#include <Rcpp.h>
// [[Rcpp::depends(RcppParallel)]]
//' @importFrom  RcppParallel RcppParallelLibs
#include <RcppParallel.h>
#include "kmer_manager.h"
#include "kmer_strings_creator.h"
#include "kmer_counting_result.h"
#include "dictionary/supported_dict_names.h"
#include "dictionary/linear_list_dictionary.h"
#include "dictionary/unordered_map_wrapper.h"
#include "gapped_kmer_counter.h"
#include "contiguous_kmer_counter.h"
#include "kmer_task_config.h"
#include <functional>
#include <vector>

inline Rcpp::List computeKMersInBatches(
        const std::function<void(KMerCountingResult &, int, int)> &batchFunc,
        int sequencesNum,
        const UserParams &userParams);

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        class algorithm_params_t>
inline void updateKMerCountingResult(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        algorithm_params_t &algorithmParams,
        KMerCountingResult &kMerCountingResult);

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
        KMerCountingResult &kMerCountingResult);

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        std::function<hashing::ComplexHasher()> &complexHasherFactory,
        KMerCountingResult &kMerCountingResult);

template<class input_vector_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
using CountingKMersProc_t = std::function<KMerManager<kmer_dictionary_t>(input_vector_t &)>;

template<class input_vector_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
class KMerCounterWorker;

template<class input_vector_t, class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingProc,
        KMerCountingResult &kMerCountingResult);

template<class input_vector_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
inline std::vector<KMerManager<kmer_dictionary_t>> computeKMersForAllSequences(
        int rowsNum,
        CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingProc,
        SequenceGetter_t<input_vector_t> sequenceGetter,
        bool parallelMode);

inline void printSequenceProcessingLogIfVerbose(
        bool verbose, int begin, int end);

// ------------------ IMPLEMENTATION ------------------

inline Rcpp::List computeKMersInBatches(
        const std::function<void(KMerCountingResult &, int, int)> &batchFunc,
        int sequencesNum,
        const UserParams &userParams) {
    KMerCountingResult kMerCountingResult;
    for (int begin = 0; begin < sequencesNum; begin += userParams.batchSize) {
        int end = std::min(begin + userParams.batchSize, sequencesNum);
        printSequenceProcessingLogIfVerbose(userParams.verbose, begin, end);
        Rcpp::checkUserInterrupt();
        batchFunc(kMerCountingResult, begin, end);
    }
    return kMerCountingResult.toRcppList();
}

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        class algorithm_params_t>
inline void updateKMerCountingResult(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        algorithm_params_t &algorithmParams,
        KMerCountingResult &kMerCountingResult) {
    if (kMerTaskConfig.userParams.kMerDictionaryName == dictionary::names::UNORDERED_MAP_NAME) {
        updateKMerCountingResultSpecifiedKMerDict<input_vector_t, input_elem_t, alphabet_encoding_t, dictionary::UnorderedMapWrapper>(
                kMerTaskConfig, alphabetEncoding, algorithmParams, kMerCountingResult);
    } else if (kMerTaskConfig.userParams.kMerDictionaryName == dictionary::names::LINEAR_LIST_NAME) {
        updateKMerCountingResultSpecifiedKMerDict<input_vector_t, input_elem_t, alphabet_encoding_t, dictionary::LinearListDictionary>(
                kMerTaskConfig, alphabetEncoding, algorithmParams, kMerCountingResult);
    } else {
        std::string errorMessage = "unsupported k-mer dictionary name: " + kMerTaskConfig.userParams.kMerDictionaryName;
        throw Rcpp::exception(errorMessage.c_str());
    }
}

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
        KMerCountingResult &kMerCountingResult) {
    std::size_t totalKMerSize = util::getKMerRange(kMerTaskConfig.userParams.gaps);
    updateKMerCountingResultSpecifiedKMerDict<input_vector_t, input_elem_t, alphabet_encoding_t, kmer_dictionary_t>(
            kMerTaskConfig,
            [&kMerTaskConfig, &alphabetEncoding, &totalKMerSize, &hasherConfigs]
                    (input_vector_t &v) -> KMerManager<kmer_dictionary_t> {
                return gappedKMers::count<input_vector_t, alphabet_encoding_t, kmer_dictionary_t>(
                        kMerTaskConfig.userParams.gaps,
                        totalKMerSize,
                        v,
                        alphabetEncoding,
                        kMerTaskConfig.userParams.positional,
                        kMerTaskConfig.userParams.withKMerCounts,
                        hasherConfigs
                );
            },
            kMerCountingResult
    );
}

template<class input_vector_t,
        class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        alphabet_encoding_t &alphabetEncoding,
        std::function<hashing::ComplexHasher()> &complexHasherFactory,
        KMerCountingResult &kMerCountingResult) {
    updateKMerCountingResultSpecifiedKMerDict<input_vector_t, input_elem_t, alphabet_encoding_t, kmer_dictionary_t>(
            kMerTaskConfig,
            [&kMerTaskConfig, &complexHasherFactory, &alphabetEncoding]
                    (input_vector_t &v) -> KMerManager<kmer_dictionary_t> {
                return contiguousKMer::count<input_vector_t, alphabet_encoding_t, kmer_dictionary_t>(
                        kMerTaskConfig.userParams.k,
                        v,
                        alphabetEncoding,
                        kMerTaskConfig.userParams.positional,
                        kMerTaskConfig.userParams.withKMerCounts,
                        std::move(complexHasherFactory())
                );
            },
            kMerCountingResult
    );
}

template<class input_vector_t, class input_elem_t,
        class alphabet_encoding_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResultSpecifiedKMerDict(
        KMerTaskConfig<input_vector_t, input_elem_t> &kMerTaskConfig,
        CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingProc,
        KMerCountingResult &kMerCountingResult) {
    auto kMersManagers = std::move(computeKMersForAllSequences<input_vector_t, kmer_dictionary_t>(
            kMerTaskConfig.sequencesNum,
            countingProc,
            kMerTaskConfig.sequenceGetter,
            kMerTaskConfig.userParams.parallelMode)
    );

    std::vector<stringsCreator::KMerPositionInfo> kMersToCreate;
    for (int seqNum = 0; seqNum < kMersManagers.size(); ++seqNum) {
        for (const auto &kMerPair: kMersManagers[seqNum].getDictionary()) {
            bool kMerStringNeedsCreation = kMerCountingResult.addKMer(kMerPair.first, seqNum, kMerPair.second.cnt);
            if (kMerStringNeedsCreation) {
                kMersToCreate.emplace_back(seqNum, kMerPair.second.seqStartPosition);
            }
        }
    }

    stringsCreator::generate<input_vector_t, input_elem_t>(
            kMersToCreate,
            kMerTaskConfig,
            kMerCountingResult.kMerStrings);

    kMerCountingResult.increaseProcessSequencesNum(kMerTaskConfig.sequencesNum);
}

template<class input_vector_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
inline std::vector<KMerManager<kmer_dictionary_t>> computeKMersForAllSequences(
        int rowsNum,
        CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingProc,
        SequenceGetter_t<input_vector_t> sequenceGetter,
        bool parallelMode) {
    KMerCounterWorker<input_vector_t, kmer_dictionary_t> worker(rowsNum, countingProc, sequenceGetter);
    if (parallelMode) {
        RcppParallel::parallelFor(0, rowsNum, worker);
    } else {
        worker(0, rowsNum);
    }
    return std::move(worker.kMers);
}

template<class input_vector_t,
        template<typename key, typename value, typename...> class kmer_dictionary_t>
class KMerCounterWorker : public RcppParallel::Worker {
public:
    KMerCounterWorker(int rowsNum,
                      CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingKMersProc,
                      SequenceGetter_t<input_vector_t> sequenceGetter) :
            countingKMersProc(countingKMersProc),
            sequenceGetter(sequenceGetter) {
        kMers.resize(rowsNum);
    }

    inline void operator()(size_t begin, size_t end) override {
        for (int rowNum = begin; rowNum < end; ++rowNum) {
            auto row = std::move(sequenceGetter(rowNum));
            kMers[rowNum] = std::move(countingKMersProc(row));
        }
    }

private:
    CountingKMersProc_t<input_vector_t, kmer_dictionary_t> countingKMersProc;
    SequenceGetter_t<input_vector_t> sequenceGetter;

public:
    std::vector<KMerManager<kmer_dictionary_t>> kMers;
};

inline void printSequenceProcessingLogIfVerbose(bool verbose, int begin, int end) {
    if (verbose) {
        Rcpp::Rcout << "Start processing sequences (batch: [" << begin + 1 << "-" << end << "])..." << std::endl;
    }
}

#endif //SEQR_KMER_TASK_SOLVER_H
