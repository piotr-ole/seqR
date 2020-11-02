// [[Rcpp::plugins("cpp17")]]
#include <Rcpp.h>
#include <memory>
#include <vector>
#include "hash/primes.h"
#include "kmer_task_solver_type_specific.h"
#include "hash/polynomial_single_hasher.h"

inline ComplexHasher createKMerComplexHasher(int hashDim) {
    std::vector<std::unique_ptr<SingleHasher>> singleHashers;
    for (int i = 0; i < hashDim; ++i) {
        singleHashers.emplace_back(
                new PolynomialSingleHasher(
                        PolynomialSingleHasherConfig(hashPrimes[i].first, hashPrimes[i].second)));
    }
    ComplexHasher complexHasher(std::move(singleHashers));
    return complexHasher;
}

template<class sequences_t,
        class alphabet_t>
Rcpp::List findKMers(sequences_t &sequences,
                     alphabet_t &alphabet,
                     int k,
                     bool positionalKMers,
                     bool withKMerCounts,
                     const std::string &kmerDictionaryName,
                     int batchSize,
                     int hashDim) {
    std::function<ComplexHasher()> algorithmParams = [hashDim]() -> ComplexHasher { return createKMerComplexHasher(hashDim); };
    std::vector<int> gaps(k - 1);
    return findKMersSpecific<decltype(algorithmParams)>(
            sequences, alphabet, gaps, positionalKMers, withKMerCounts, kmerDictionaryName,
            batchSize,
            algorithmParams);
}

//' @export
// [[Rcpp::export]]
Rcpp::List find_kmers_string(Rcpp::StringMatrix &sequenceMatrix,
                             Rcpp::StringVector &alphabet,
                             int k,
                             bool positionalKMers,
                             bool withKMerCounts,
                             const std::string &kmerDictionaryName,
                             int batchSize,
                             int hashDim) {
    return findKMers(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts,
                     kmerDictionaryName,
                     batchSize,
                     hashDim
    );
}

//' @export
// [[Rcpp::export]]
Rcpp::List find_kmers_integer(Rcpp::IntegerMatrix &sequenceMatrix,
                              Rcpp::IntegerVector &alphabet,
                              int k,
                              bool positionalKMers,
                              bool withKMerCounts,
                              const std::string &kmerDictionaryName,
                              int batchSize,
                              int hashDim) {
    return findKMers(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts,
                     kmerDictionaryName,
                     batchSize,
                     hashDim
    );
}

//' @export
// [[Rcpp::export]]
Rcpp::List find_kmers_numeric(Rcpp::NumericMatrix &sequenceMatrix,
                              Rcpp::NumericVector &alphabet,
                              int k,
                              bool positionalKMers,
                              bool withKMerCounts,
                              const std::string &kmerDictionaryName,
                              int batchSize,
                              int hashDim) {
    return findKMers(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts,
                     kmerDictionaryName,
                     batchSize,
                     hashDim
    );
}

//' @export
// [[Rcpp::export]]
Rcpp::List find_kmers_list(Rcpp::List &sq,
                           Rcpp::StringVector &alphabet,
                           int k,
                           bool positionalKMers,
                           bool withKMerCounts,
                           const std::string &kmerDictionaryName,
                           int batchSize,
                           int hashDim) {
    return findKMers(sq, alphabet, k, positionalKMers, withKMerCounts, kmerDictionaryName, batchSize,
                     hashDim);
}
