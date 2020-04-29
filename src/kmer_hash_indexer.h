#ifndef KMER_HASH_INDEXER_H
#define KMER_HASH_INDEXER_H

#include "kmer_counts_manager.h"
#include <vector>
#include <tuple>
#include <memory>

class KMerPositionInfo {
public:
    int seqNum;

    int position;

    KMerPositionInfo(int seqNum, int position) :
            seqNum(seqNum), position(position) {
    }

    KMerPositionInfo(const KMerPositionInfo &) = default;

    KMerPositionInfo &operator=(const KMerPositionInfo &) = default;

};

template<template<typename key, typename value> class kmer_dictionary_t>
inline
std::tuple<
        kmer_dictionary_t<std::vector<int>, int>,
        std::vector<KMerPositionInfo>>
indexKMerHashes(const std::vector<KMerCountsManager<kmer_dictionary_t>> &kmerCounts) {
    kmer_dictionary_t<std::vector<int>, int> hashIndexer;
    std::vector<KMerPositionInfo> uniqueKMers;
    int currentIndex = 0;
    for (int seqNum = 0; seqNum < kmerCounts.size(); ++seqNum) {
        for (const auto &hashPair: kmerCounts[seqNum].getDictionary()) {
            auto hash = hashPair.first;
            auto seqStartPosition = hashPair.second.seqStartPosition;
            if (!hashIndexer.isPresent(hash)) {
                hashIndexer[hash] = currentIndex++;
                uniqueKMers.emplace_back(seqNum, seqStartPosition);
            }
        }
    }
    return {
            std::move(hashIndexer),
            std::move(uniqueKMers)
    };
}

#endif
