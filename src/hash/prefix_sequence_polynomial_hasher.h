#pragma once

#include <vector>

#include "globals.h"
#include "polynomial_single_hasher.h"

namespace hashing {

template <class encoded_sequence_t>
class PrefixSequencePolynomialHasher {
 public:
  using hash_t = config::multidim_hash_t;

  PrefixSequencePolynomialHasher(const encoded_sequence_t &sequence,
                                 const std::vector<PolynomialSingleHasherConfig> &polynomialHasherConfigs)
      : polynomialHasherConfigs(polynomialHasherConfigs) {
    initModuloMComputers(polynomialHasherConfigs);
    computePrefixValues(sequence);
  }

  [[nodiscard]] inline hash_t getHash(int begin, int end) const {
    hash_t res(polynomialHasherConfigs.size());
    for (int hasherInd = 0; hasherInd < res.size(); ++hasherInd) {
      auto M = polynomialHasherConfigs[hasherInd].M;
      res[hasherInd] = moduloMComputers[hasherInd].get(
          M + prefixComplexHashes[end + 1][hasherInd] -
          moduloMComputers[hasherInd].get(
              prefixComplexHashes[begin][hasherInd] * prefixP[end - begin + 1][hasherInd]));
    }
    return res;
  }

  [[nodiscard]] inline hash_t getHashForSeveralIntervals(
      int beginPosition,
      const std::vector<std::pair<int, int>> &contiguousIntervals) const {
    hash_t res(this->getHashersNum());
    for (const auto &interval : contiguousIntervals) {
      auto intervalHash = this->getHash(
          interval.first + beginPosition,
          interval.second + beginPosition);
      int intervalLength = util::getIntervalLength(interval);
      for (int hasherInd = 0; hasherInd < res.size(); ++hasherInd) {
        int powerP = this->getHasherP(hasherInd, intervalLength);
        int M = this->getHasherM(hasherInd);
        res[hasherInd] = moduloMComputers[hasherInd].get(
            res[hasherInd] * powerP + intervalHash[hasherInd]);
      }
    }
    return res;
  }

 private:
  const std::vector<PolynomialSingleHasherConfig> &polynomialHasherConfigs;
  std::vector<hash_t> prefixP;
  std::vector<hash_t> prefixComplexHashes;
  std::vector<util::ModuloComputer> moduloMComputers;

  void initModuloMComputers(const std::vector<PolynomialSingleHasherConfig> &configs) {
    for (const auto &config : configs) {
      moduloMComputers.emplace_back(config.M);
    }
  }

  inline void computePrefixValues(const encoded_sequence_t &sequence) {
    initPrefixP(sequence.size(), polynomialHasherConfigs.size());
    initPrefixComplexHashes(sequence.size(), polynomialHasherConfigs.size());
    for (int seqInd = 0; seqInd < sequence.size(); ++seqInd) {
      appendPrefixValues(sequence, seqInd);
    }
  }

  inline void initPrefixP(int sequenceLength, int hashersNum) {
    prefixP.reserve(sequenceLength);
    prefixP.push_back(std::move(hash_t(hashersNum, 1)));
  }

  inline void initPrefixComplexHashes(int sequenceLength, int hashersNum) {
    prefixComplexHashes.reserve(sequenceLength);
    prefixComplexHashes.push_back(
        std::move(hash_t(hashersNum)));
  }

  inline void appendPrefixValues(const encoded_sequence_t &sequence,
                                 int seqInd) {
    appendCurrentComplexHash(sequence[seqInd]);
    appendCurrentPowerP();
  }

  inline void appendCurrentComplexHash(const typename encoded_sequence_t::encoded_elem_t &encodedElem) {
    hash_t prefixHash(polynomialHasherConfigs.size());
    for (int hasherInd = 0; hasherInd < prefixHash.size(); ++hasherInd) {
      auto P = polynomialHasherConfigs[hasherInd].P;
      auto M = polynomialHasherConfigs[hasherInd].M;
      prefixHash[hasherInd] = moduloMComputers[hasherInd].get(
          prefixComplexHashes.back()[hasherInd] * P + encodedElem);
    }
    prefixComplexHashes.push_back(std::move(prefixHash));
  }

  inline void appendCurrentPowerP() {
    hash_t powersP(polynomialHasherConfigs.size());
    for (int hasherInd = 0; hasherInd < powersP.size(); ++hasherInd) {
      auto P = polynomialHasherConfigs[hasherInd].P;
      auto M = polynomialHasherConfigs[hasherInd].M;
      powersP[hasherInd] = moduloMComputers[hasherInd].get(prefixP.back()[hasherInd] * P);
    }
    prefixP.push_back(std::move(powersP));
  }

  [[nodiscard]] inline PolynomialSingleHasherConfig::elem_t getHasherP(int hasherIndex, int power = 1) const {
    return this->prefixP[power][hasherIndex];
  }

  [[nodiscard]] inline PolynomialSingleHasherConfig::elem_t getHasherM(int hasherIndex) const {
    return this->polynomialHasherConfigs[hasherIndex].M;
  }

  [[nodiscard]] inline int getHashersNum() const {
    return this->polynomialHasherConfigs.size();
  }
};
}  // namespace hashing
