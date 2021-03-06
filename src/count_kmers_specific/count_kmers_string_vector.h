#pragma once

#include <Rcpp.h>

#include <algorithm>
#include <array>
#include <limits>
#include <string>
#include <vector>

#include "../common_config.h"
#include "../kmer_counting_result.h"
#include "../kmer_task_solver.h"
#include "./encoded_sequence/encoded_sequence_proxy.h"

class EncodedStringVectorList {
 public:
  using init_elem_t = std::string;
  using encoded_elem_t = char;
  using Entry = EncodedSequenceProxy<EncodedStringVectorList>;

  EncodedStringVectorList(
      const std::array<bool, CHAR_MAX> &isAllowed,
      Rcpp::StringVector sequences,
      std::size_t seqBegin,
      std::size_t seqEnd)
      : _isAllowed(isAllowed),
        _allElementsAllowed(std::all_of(std::begin(isAllowed),
                                        std::end(isAllowed),
                                        [](bool x) { return x; })) {
    _encode(sequences, seqBegin, seqEnd);
  }

  EncodedStringVectorList() = delete;

  inline Entry operator[](std::size_t sequenceNum) const {
    return Entry(sequenceNum, *this);
  }

  inline encoded_elem_t getElem(std::size_t sequenceNum,
                                std::size_t offset) const {
    return _encodedSequences[sequenceNum][offset];
  }

  inline init_elem_t decode(std::size_t sequenceNum,
                            std::size_t offset) const {
    return std::string(1, _encodedSequences[sequenceNum][offset]);
  }

  inline bool isAllowed(std::size_t sequenceNum,
                        std::size_t offset) const {
    return _isAllowed[_encodedSequences[sequenceNum][offset]];
  }

  inline bool areAllElementsAllowed() const {
    return _allElementsAllowed;
  }

  inline std::size_t getSequenceSize(std::size_t sequenceNum) const {
    return _encodedSequences[sequenceNum].size();
  }

  inline std::size_t size() const {
    return _encodedSequences.size();
  }

 private:
  const std::array<bool, CHAR_MAX> &_isAllowed;
  bool _allElementsAllowed;
  std::vector<std::string> _encodedSequences;

  void _encode(Rcpp::StringVector sequences, std::size_t seqBegin, std::size_t seqEnd) {
    _encodedSequences.resize(seqEnd - seqBegin);
    for (std::size_t i = seqBegin; i < seqEnd; ++i) {
      _encodedSequences[i - seqBegin] = Rcpp::as<std::string>(sequences[i]);
    }
  }
};

inline std::array<bool, CHAR_MAX> getIsAllowedArray(Rcpp::StringVector &alphabet) {
  std::array<bool, CHAR_MAX> isAllowedElem;
  if (alphabet[0] == config::ALPHABET_ALL_LABEL) {
    isAllowedElem.fill(true);
  } else {
    isAllowedElem.fill(false);
    for (const auto &alphabetElem : alphabet) {
      char elem = Rcpp::as<char>(alphabetElem);
      isAllowedElem[elem] = true;
    }
  }
  return isAllowedElem;
}

template <class algorithm_params_t,
          class kmer_manager_t,
          template <typename key, typename value, class...> class result_dictionary_t>
inline Rcpp::List countKMersSpecific(
    Rcpp::StringVector &sequences,
    Rcpp::StringVector &kmerAlphabet,
    const UserParams &userParams,
    algorithm_params_t &algorithmParams) {
  auto isAllowedElem = getIsAllowedArray(kmerAlphabet);

  auto batchFunc = [&](KMerCountingResult<result_dictionary_t> &kMerCountingResult,
                       std::size_t seqBegin, std::size_t seqEnd) {
    KMerTaskConfig<EncodedStringVectorList> kMerTaskConfig(
        EncodedStringVectorList(isAllowedElem, sequences, seqBegin, seqEnd),
        config::DEFAULT_KMER_ITEM_SEPARATOR,
        config::DEFAULT_KMER_SECTION_SEPARATOR,
        userParams);
    updateKMerCountingResult<EncodedStringVectorList, kmer_manager_t, result_dictionary_t>(
        kMerTaskConfig,
        algorithmParams,
        kMerCountingResult);
  };

  return computeKMersInBatches<result_dictionary_t>(batchFunc, sequences.size(), userParams);
}
