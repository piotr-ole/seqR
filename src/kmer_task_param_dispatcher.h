#pragma once

#include "../inst/thirdparty/dictionaries/robin_hood_martinus.h"
#include "count_kmers_specific/count_kmers_specific.h"
#include "kmer_manager.h"
#include "user_params.h"

template <class sequences_t,
          class alphabet_t,
          class algorithm_params_t>
inline Rcpp::List countKMers(
    sequences_t &sequences,
    alphabet_t &alphabet,
    const UserParams &userParams,
    algorithm_params_t &algorithmParams);

template <class sequences_t, class alphabet_t, class algorithm_params_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline Rcpp::List countKMersKMerManagerDispatch(
    sequences_t &sequences,
    alphabet_t &alphabet,
    const UserParams &userParams,
    algorithm_params_t &algorithmParams);

// ------------------ IMPLEMENTATION ------------------

template <class k, class v, class h = std::hash<k>>
using custom_hash_map = robin_hood::unordered_map<k, v, h>;

template <class sequences_t,
          class alphabet_t,
          class algorithm_params_t>
inline Rcpp::List countKMers(
    sequences_t &sequences,
    alphabet_t &alphabet,
    const UserParams &userParams,
    algorithm_params_t &algorithmParams) {
  return countKMersKMerManagerDispatch<sequences_t, alphabet_t, algorithm_params_t,
                                       custom_hash_map>(
      sequences, alphabet, userParams, algorithmParams);
}

template <class sequences_t, class alphabet_t, class algorithm_params_t,
          template <typename key, typename value, typename...> class result_dictionary_t>
inline Rcpp::List countKMersKMerManagerDispatch(
    sequences_t &sequences,
    alphabet_t &alphabet,
    const UserParams &userParams,
    algorithm_params_t &algorithmParams) {
  if (userParams.withKMerCounts) {
    return countKMersSpecific<algorithm_params_t,
                              CountingKMerManager<result_dictionary_t>,
                              result_dictionary_t>(
        sequences, alphabet, userParams, algorithmParams);
  } else {
    return countKMersSpecific<algorithm_params_t,
                              PresenceKMerManager<result_dictionary_t>,
                              result_dictionary_t>(
        sequences, alphabet, userParams, algorithmParams);
  }
}
