#pragma once

#include <Rcpp.h>
// [[Rcpp::depends(RcppParallel)]]
//' @importFrom  RcppParallel RcppParallelLibs
#include <RcppParallel.h>
#include "kmer_manager.h"
#include "kmer_strings_creator.h"
#include "kmer_counting_result.h"
#include "gapped_kmer_counter.h"
#include "contiguous_kmer_counter.h"
#include "kmer_task_config.h"
#include "dictionary/supported_dict_names.h"
#include "dictionary/linear_list_dictionary.h"
#include <functional>
#include <vector>

template <template <class K, class V, class...> class kmer_dictionary_t>
inline Rcpp::List computeKMersInBatches(
	const std::function<void(KMerCountingResult<kmer_dictionary_t> &, int, int)> &batchFunc,
	int sequencesNum,
	const UserParams &userParams);

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult);

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	std::function<hashing::ComplexHasher()> &complexHasherFactory,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult);

template <class encoded_sequence_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
using CountingKMersProc_t = std::function<KMerManager<kmer_dictionary_t>(const encoded_sequence_t &)>;

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
class KMerCounterWorker;

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingProc,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult);

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline std::vector<KMerManager<kmer_dictionary_t>> computeKMersForAllSequences(
	CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingProc,
	const encoded_sequences_list_t &encodedSequencesList,
	bool parallelMode);

inline void printSequenceProcessingLogIfVerbose(
	bool verbose, int begin, int end);

// ------------------ IMPLEMENTATION ------------------

template <template <class K, class V, class...> class kmer_dictionary_t>
inline Rcpp::List computeKMersInBatches(
	const std::function<void(KMerCountingResult<kmer_dictionary_t> &, int, int)> &batchFunc,
	int sequencesNum,
	const UserParams &userParams)
{
	KMerCountingResult<kmer_dictionary_t> kMerCountingResult;
	for (int begin = 0; begin < sequencesNum; begin += userParams.batchSize)
	{
		int end = std::min(begin + userParams.batchSize, sequencesNum);
		printSequenceProcessingLogIfVerbose(userParams.verbose, begin, end);
		Rcpp::checkUserInterrupt();
		batchFunc(kMerCountingResult, begin, end);
	}
	return kMerCountingResult.toRcppList();
}

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	std::vector<hashing::PolynomialSingleHasherConfig> &hasherConfigs,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult)
{
	using sequenceEntry = typename encoded_sequences_list_t::Entry;
	std::size_t totalKMerSize = util::getKMerRange(kMerTaskConfig.userParams.gaps);
	updateKMerCountingResult<encoded_sequences_list_t, kmer_dictionary_t>(
		kMerTaskConfig,
		[&kMerTaskConfig, &totalKMerSize, &hasherConfigs](const sequenceEntry &seq)
			-> KMerManager<kmer_dictionary_t> {
			return gappedKMers::count<sequenceEntry, kmer_dictionary_t>(
				seq,
				kMerTaskConfig.userParams.gaps,
				totalKMerSize,
				kMerTaskConfig.userParams.positional,
				kMerTaskConfig.userParams.withKMerCounts,
				hasherConfigs);
		},
		kMerCountingResult);
}

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	std::function<hashing::ComplexHasher()> &complexHasherFactory,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult)
{
	using sequenceEntry = typename encoded_sequences_list_t::Entry;
	updateKMerCountingResult<encoded_sequences_list_t, kmer_dictionary_t>(
		kMerTaskConfig,
		[&kMerTaskConfig, &complexHasherFactory](const sequenceEntry &seq)
			-> KMerManager<kmer_dictionary_t> {
			return contiguousKMer::count<sequenceEntry, kmer_dictionary_t>(
				seq,
				kMerTaskConfig.userParams.k,
				kMerTaskConfig.userParams.positional,
				kMerTaskConfig.userParams.withKMerCounts,
				std::move(complexHasherFactory()));
		},
		kMerCountingResult);
}

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline void updateKMerCountingResult(
	const KMerTaskConfig<encoded_sequences_list_t> &kMerTaskConfig,
	CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingProc,
	KMerCountingResult<kmer_dictionary_t> &kMerCountingResult)
{
	auto sequencesNum = kMerTaskConfig.encodedSequencesList.size();
	auto kMersManagers = computeKMersForAllSequences<encoded_sequences_list_t, kmer_dictionary_t>(
		countingProc,
		kMerTaskConfig.encodedSequencesList,
		kMerTaskConfig.userParams.parallelMode);

	std::vector<stringsCreator::KMerPositionInfo> kMersToCreate;
	for (int seqNum = 0; seqNum < kMersManagers.size(); ++seqNum)
	{
		for (const auto &kMerPair : kMersManagers[seqNum].getDictionary())
		{
			bool kMerStringNeedsCreation = kMerCountingResult.addKMer(
				kMerPair.first,
				seqNum,
				kMerPair.second.cnt);

			if (kMerStringNeedsCreation)
			{
				kMersToCreate.emplace_back(seqNum, kMerPair.second.seqStartPosition);
			}
		}
	}

	stringsCreator::generate<encoded_sequences_list_t>(
		kMersToCreate,
		kMerTaskConfig,
		kMerCountingResult.kMerStrings);

	kMerCountingResult.increaseProcessSequencesNum(sequencesNum);
}

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
inline std::vector<KMerManager<kmer_dictionary_t>> computeKMersForAllSequences(
	CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingProc,
	const encoded_sequences_list_t &encodedSequencesList,
	bool parallelMode)
{
	KMerCounterWorker<encoded_sequences_list_t, kmer_dictionary_t> worker(countingProc, encodedSequencesList);
	if (parallelMode)
	{
		RcppParallel::parallelFor(0, encodedSequencesList.size(), worker);
	}
	else
	{
		worker(0, encodedSequencesList.size());
	}
	return worker.kMers;
}

template <class encoded_sequences_list_t,
		  template <typename key, typename value, typename...> class kmer_dictionary_t>
class KMerCounterWorker : public RcppParallel::Worker
{
public:
	KMerCounterWorker(
		CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingKMersProc,
		const encoded_sequences_list_t &encodedSequencesList)
		: countingKMersProc(countingKMersProc),
		  encodedSequencesList(encodedSequencesList)
	{
		kMers.resize(encodedSequencesList.size());
	}

	inline void operator()(size_t begin, size_t end) override
	{
		for (int rowNum = begin; rowNum < end; ++rowNum)
		{
			auto row = encodedSequencesList[rowNum];
			kMers[rowNum] = countingKMersProc(row);
		}
	}

private:
	CountingKMersProc_t<typename encoded_sequences_list_t::Entry, kmer_dictionary_t> countingKMersProc;
	const encoded_sequences_list_t &encodedSequencesList;

public:
	std::vector<KMerManager<kmer_dictionary_t>>
		kMers;
};

inline void printSequenceProcessingLogIfVerbose(bool verbose, int begin, int end)
{
	if (verbose)
	{
		Rcpp::Rcout << "Start processing sequences (batch: [" << begin + 1 << "-" << end << "])..." << std::endl;
	}
}
