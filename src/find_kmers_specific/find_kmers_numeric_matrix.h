//
// Created by slowik on 28.11.2020.
//

#ifndef SEQR_FIND_KMERS_NUMERIC_MATRIX_H
#define SEQR_FIND_KMERS_NUMERIC_MATRIX_H

#include <Rcpp.h>
#include <vector>
#include "../kmer_task_config.h"
#include "../alphabet_encoder.h"
#include "../dictionary/unordered_map_wrapper.h"
#include "../kmer_counting_result.h"
#include "../kmer_task_solver.h"

template<class algorithm_params_t>
inline
Rcpp::List findKMersSpecific(Rcpp::NumericMatrix &sequenceMatrix,
                             Rcpp::NumericVector &alphabet,
                             std::vector<int> &gaps,
                             bool positionalKMers,
                             bool withKMerCounts,
                             const std::string &kmerDictionaryName,
                             int batchSize,
                             bool verbose,
                             algorithm_params_t &algorithmParams) {
    auto alphabetEncoding = std::move(
            getAlphabetEncoding<Rcpp::NumericVector, double, short, UnorderedMapWrapper>(alphabet));

    auto batchFunc = [&](KMerCountingResult &kMerCountingResult, int seqBegin, int seqEnd) {
        KMerTaskConfig<RcppParallel::RMatrix<double>::Row, double> kMerTaskConfig(
                (seqEnd - seqBegin),
                getRMatrixRowGetter<Rcpp::NumericMatrix, double>(sequenceMatrix, seqBegin),
                gaps,
                positionalKMers,
                withKMerCounts,
                getDoubleToStringConverter(3),
                DEFAULT_KMER_ITEM_SEPARATOR,
                DEFAULT_KMER_SECTION_SEPARATOR);
        computeResult<
                RcppParallel::RMatrix<double>::Row,
                double,
                short,
                UnorderedMapWrapper,
                algorithm_params_t>(kMerTaskConfig,
                                    alphabetEncoding,
                                    kmerDictionaryName,
                                    algorithmParams,
                                    kMerCountingResult);
    };

    return computeKMersInBatches(batchFunc, sequenceMatrix.nrow(), batchSize, verbose);
}

#endif //SEQR_FIND_KMERS_NUMERIC_MATRIX_H
