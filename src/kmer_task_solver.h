#pragma once

// [[Rcpp::depends(RcppParallel)]]
//' @importFrom  RcppParallel RcppParallelLibs
#include <RcppParallel.h>

#include <functional>
#include <vector>

#include "contiguous_kmer_counter.h"
#include "gapped_kmer_counter.h"
#include "kmer_counting_result.h"
#include "kmer_strings_creator.h"
#include "kmer_task_config.h"

template <template <class K, class V, class...> class result_dictionary_t>
inline Rcpp::List computeKMersInBatches(
    const std::function<void(KMerCountingResult<result_dictionary_t> &, std::size_t, std::size_t)> &batchFunc,
    int sequencesNum,
    const UserParams &userParams);

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult);

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    std::function<hashing::ComplexHasher()> &complexHasherFactory,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult);

template <class encoded_sequence_t,
          class kmer_manager_t>
using CountingKMersForOneSeqProc_t = std::function<kmer_manager_t(const encoded_sequence_t &)>;

template <class encoded_sequences_list_t,
          class kmer_manager_t>
class KMerCounterWorker;

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingProc,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult);

template <class encoded_sequences_list_t,
          class kmer_manager_t>
inline std::vector<kmer_manager_t> computeKMersForAllSequences(
    bool paralellMode,
    CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingProc,
    const encoded_sequences_list_t &encodedSequencesList);

inline void printSequenceProcessingLogIfVerbose(
    bool verbose, int begin, int end);

// ------------------ IMPLEMENTATION ------------------

template <template <class K, class V, class...> class result_dictionary_t>
inline Rcpp::List computeKMersInBatches(
    const std::function<void(KMerCountingResult<result_dictionary_t> &, std::size_t, std::size_t)> &batchFunc,
    int sequencesNum,
    const UserParams &userParams) {
  KMerCountingResult<result_dictionary_t> kMerCountingResult;
  for (int begin = 0; begin < sequencesNum; begin += userParams.batchSize) {
    int end = std::min(begin + userParams.batchSize, sequencesNum);
    printSequenceProcessingLogIfVerbose(userParams.verbose, begin, end);
    Rcpp::checkUserInterrupt();
    batchFunc(kMerCountingResult, begin, end);
  }
  return kMerCountingResult.toRcppList();
}

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult) {
  using sequenceEntry = typename encoded_sequences_list_t::Entry;
  std::size_t totalKMerSize = util::getKMerRange(kMerTaskConfig.userParams.gaps);
  updateKMerCountingResult<encoded_sequences_list_t, kmer_manager_t, result_dictionary_t>(
      kMerTaskConfig,
      [&kMerTaskConfig, &totalKMerSize, &hasherConfigs](const sequenceEntry &seq)
          -> kmer_manager_t {
        return gappedKMers::count<sequenceEntry, kmer_manager_t>(
            seq,
            kMerTaskConfig.userParams.gaps,
            totalKMerSize,
            kMerTaskConfig.userParams.positional,
            hasherConfigs);
      },
      kMerCountingResult);
}

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    std::function<hashing::ComplexHasher()> &complexHasherFactory,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult) {
  using sequenceEntry = typename encoded_sequences_list_t::Entry;
  updateKMerCountingResult<encoded_sequences_list_t, kmer_manager_t, result_dictionary_t>(
      kMerTaskConfig,
      [&kMerTaskConfig, &complexHasherFactory](const sequenceEntry &seq)
          -> kmer_manager_t {
        return contiguousKMer::count<sequenceEntry, kmer_manager_t>(
            seq,
            kMerTaskConfig.userParams.k,
            kMerTaskConfig.userParams.positional,
            std::move(complexHasherFactory()));
      },
      kMerCountingResult);
}

template <class encoded_sequences_list_t,
          class kmer_manager_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline void updateKMerCountingResult(
    const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
    CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingProc,
    KMerCountingResult<result_dictionary_t> &kMerCountingResult) {
  auto sequencesNum = kMerTaskConfig.encodedSequencesList.size();
  auto kMersManagers = computeKMersForAllSequences<encoded_sequences_list_t, kmer_manager_t>(
      kMerTaskConfig.userParams.parallelMode,
      countingProc,
      kMerTaskConfig.encodedSequencesList);

  std::vector<stringsCreator::KMerPositionInfo> kMersToCreate;
  for (std::size_t seqNum = 0; seqNum < kMersManagers.size(); ++seqNum) {
    for (const auto &kMerPair : kMersManagers[seqNum].getDictionary()) {
      bool kMerStringNeedsCreation = kMerCountingResult.addKMer(
          kMerPair.first,
          seqNum,
          kMerPair.second.cnt);

      if (kMerTaskConfig.userParams.withKMerNames && kMerStringNeedsCreation) {
        kMersToCreate.emplace_back(seqNum, kMerPair.second.seqStartPosition);
      }
    }
  }

  if (kMerTaskConfig.userParams.withKMerNames) {
    stringsCreator::generate<encoded_sequences_list_t>(
        kMersToCreate,
        kMerTaskConfig,
        kMerCountingResult.kMerStrings);
  }

  kMerCountingResult.increaseProcessedSequencesNum(sequencesNum);
}

template <class encoded_sequences_list_t,
          class kmer_manager_t>
inline std::vector<kmer_manager_t> computeKMersForAllSequences(
    bool parallelMode,
    CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingProc,
    const encoded_sequences_list_t &encodedSequencesList) {
  KMerCounterWorker<encoded_sequences_list_t, kmer_manager_t> worker(countingProc, encodedSequencesList);
  util::invokeRcppParallelOrSequentialIfSingle(worker, parallelMode);
  return worker.kMers;
}

template <class encoded_sequences_list_t,
          class kmer_manager_t>
class KMerCounterWorker : public RcppParallel::Worker {
 public:
  KMerCounterWorker(
      CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingKMersProc,
      const encoded_sequences_list_t &encodedSequencesList)
      : countingKMersProc(countingKMersProc),
        encodedSequencesList(encodedSequencesList) {
    kMers.resize(encodedSequencesList.size());
  }

  inline void operator()(size_t begin, size_t end) override {
    for (std::size_t rowNum = begin; rowNum < end; ++rowNum) {
      auto row = encodedSequencesList[rowNum];
      kMers[rowNum] = countingKMersProc(row);
    }
  }

  inline std::size_t tasksNum() const {
    return encodedSequencesList.size();
  }

 private:
  CountingKMersForOneSeqProc_t<typename encoded_sequences_list_t::Entry, kmer_manager_t> countingKMersProc;
  const encoded_sequences_list_t &encodedSequencesList;

 public:
  std::vector<kmer_manager_t> kMers;
};

inline void printSequenceProcessingLogIfVerbose(bool verbose, int begin, int end) {
  if (verbose) {
    Rcpp::Rcout << "Start processing sequences (batch: [" << begin + 1 << "-" << end << "])..." << std::endl;
  }
}
