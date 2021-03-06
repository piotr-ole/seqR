#' Count k-mers of various types for a given collection of sequences
#' 
#' @description 
#' 
#' This is a wrapper over \link[seqR]{count_kmers} function
#' in order to enable the computation of many types of k-mers
#' in a single invocation of the function.
#' 
#' A user can input multiple k-mer configurations in the following way.
#' Each parameter that is related to the configuration
#' (i.e., \code{k_vector}, \code{positional_vector}, and \code{kmer_gaps_list})
#' is represented in a sequential form (i.e., a list or a vector).
#' The i-th entry of each sequence corresponds to the i-th configuration.
#' 
#' @inheritParams count_kmers
#' 
#' @param k_vector an \code{integer vector} that represents the lengths of k-mers.
#' The i-th element corresponds to the value of \code{k} for the i-th k-mer configuration.
#' 
#' @param positional_vector a \code{logical vector} that consists of k-mer configurations
#' related to the positional part.
#' The i-th element corresponds to the i-th k-mer configuration (i.e., whether the k-mer is positional or not)
#' 
#' @param kmer_gaps_list a \code{list} of \code{integer vectors} that represents the lengths of k-mer gaps
#' for each configuration separately. The i-th element of the list corresponds to the lengths of gaps of the i-th
#' k-mer configuration
#' 
#' 
#' @inherit count_kmers return
#' 
#' @inherit count_kmers details 
#'  
#' @examples
#' 
#' batch_size <- 1
#' 
#' # Counting 1-mers
#' count_multimers(
#'    c("AAAACFVV", "AAAAAA", "AAAAD"),
#'    k_vector = c(1),
#'    batch_size=batch_size)
#' 
#' # Counting 1-mers and 2-mers
#' count_multimers(
#'     c("AAAACFVV", "AAAAAA", "AAAAD"),
#'     k_vector = c(1, 2),
#'     batch_size = batch_size)
#' 
#' # Counting 1-mers, 2-mers, and gapped 2-mers with the length of the gap = 1
#' count_multimers(
#'    c("AAAACFVV", "AAAAAA", "AAAAD"),
#'    k_vector = c(1, 2, 2),
#'    kmer_gaps = list(NULL, NULL, c(1)),
#'    batch_size=batch_size)
#' 
#' # Counting 3-mers, positional 3-mers, and positional gapped 2-mers with the length of the gap = 1
#' count_multimers(
#'    c("AAAACFVV", "AAAAAA", "AAAAD"),
#'    k_vector = c(3, 3, 2),
#'    kmer_gaps_list = list(NULL, NULL, c(1)),
#'    positional_vector = c(FALSE, TRUE, TRUE),
#'    batch_size=batch_size)
#' 
#' @seealso Function that count k-mers of one type: \link[seqR]{count_kmers}
#' @seealso Function that merges several k-mer matrices (rbind): \link[seqR]{rbind_columnwise}
#' @md
#' @include common.R
#' @export
count_multimers <- function(sequences,
                            k_vector,
                            kmer_alphabet = getOption("seqR_kmer_alphabet_default"),
                            positional_vector = rep(getOption("seqR_positional_default"), length(k_vector)),
                            kmer_gaps_list = rep(list(c()), length(k_vector)),
                            with_kmer_counts = getOption("seqR_with_kmer_counts_default"),
                            with_kmer_names = getOption("seqR_with_kmer_names_default"),
                            batch_size = getOption("seqR_batch_size_default"),
                            hash_dim = getOption("seqR_hash_dim_default"),
                            verbose = getOption("seqR_verbose_default")) {
  .validate_verbose(verbose)
  .validate_kmer_configs(k_vector, kmer_gaps_list, positional_vector, batch_size)
  
  configs_num <- length(k_vector)
  r <- do.call(cbind, lapply(1:configs_num, function(index) {
    if(verbose) {
      print(paste0("Processing sequences for config no.", index))
    }
    
    suppressMessages(
      count_kmers(
        sequences = sequences,
        k = k_vector[index],
        kmer_alphabet = kmer_alphabet,
        positional = positional_vector[index],
        kmer_gaps = kmer_gaps_list[[index]],
        with_kmer_counts = with_kmer_counts,
        with_kmer_names = with_kmer_names,
        batch_size = batch_size,
        hash_dim = hash_dim,
        verbose = verbose))
  }))
  r
}

.validate_kmer_configs <- function(k_vector, kmer_gaps_list, positional_vector, batch_size) {
  if(length(k_vector) != length(kmer_gaps_list)) {
    stop("the length of 'k_vector' must have equal length to 'kmer_gaps_list' ")
  }
  
  if(length(k_vector) != length(positional_vector)) {
    stop("the length of 'k_vector' must have equal length to 'positional vector'")
  }
  
  .show_message_if_batch_size_1(batch_size)
}

.validate_verbose <- function(param) {
  if(!is_bool_value(param)) {
    stop("verbose must be a single logical value")
  }
}
