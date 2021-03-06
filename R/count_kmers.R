#' Count k-mers of one, particular type for a given collection of sequences
#' 
#' @description
#' This is an in-memory, probabilistic, highly-optimized,
#' and multi-threaded implementation of k-mer counting algorithm.
#' 
#' The function supports 
#' 1. several types of k-mers (contiguous, gapped, and positional variants)
#' 2. all biological sequences (in particular, nucleic acids and proteins)
#' 3. two common in-memory representations of sequences, i.e., string vectors and list of string vectors
#' 
#' Moreover, several extra features are provided
#' (for more information see `details`'):
#' 1. configurable k-mer alphabet
#' (i.e., which elements of a sequence should be considered during the k-mer counting procedure)
#' 2. verbose mode
#' 3. configurable batch size (i.e., how many sequences are processed in a single step)
#' 4. configurable dimension of the hash value of a k-mer
#' 5. possibility to compute k-mers with or without their frequencies
#' 6. possibility to compute a result k-mer matrix with or without human-readable k-mer (column) names
#' 
#' @param sequences input sequences of one of two supported types,
#' either \code{string vector} or \code{list} of \code{string vectors}
#' 
#' @param k an \code{integer} representing the length of a k-mer
#' 
#' @param kmer_alphabet a \code{string vector} representing the elements that should be used
#' during the construction of k-mers. By default, all elements that are present in sequences
#' are taking into account
#' 
#' @param positional a single \code{logical} value that determines whether positional k-mer
#' variant should be considered
#' 
#' @param kmer_gaps an \code{integer vector} representing the lengths of gaps between consecutive
#' k-mer elements. The length of the vector should be equal to \code{k - 1}
#' 
#' @param with_kmer_counts a single \code{logical} value that determines whether the result
#' should contain k-mer frequencies
#' 
#' @param with_kmer_names a single \code{logical} value that determines whether the result
#' should contain human-readable k-mer names
#' 
#' @param batch_size a single \code{integer} value that represents the number of sequences
#' that are being processed in a single step
#' 
#' @param hash_dim a single \code{integer} value (`1 <= hash_dim <= 500`) representing the length of a hash vector
#' that is internally used in the algorithm
#' 
#' @param verbose a single \code{logical} value that denotes whether a user wants to get
#' extra information on the current state of computations
#' 
#' @return a \code{\link[Matrix]{Matrix}} value that represents a result k-mer matrix.
#' The result is a sparse matrix in order to reduce memory consumption.
#' The i-th row of the matrix represents k-mers found in the i-th input sequence.
#' Each column represents a distinct k-mer.
#' The names of columns conform to human-readable schema for k-mers,
#' if parameter \code{with_kmer_names = TRUE} 
#' 
#' @details
#'
#' The comprehensive description of supported features is available
#' in \code{vignette("features-overview", package = "seqR")}. 
#'
#' @examples
#' 
#' batch_size <- 1
#' 
#' # Counting 1-mers af two DNA sequences
#' count_kmers(
#'    c("ACAT", "ACC"),
#'    batch_size=batch_size)
#' 
#' # Counting 2-mers of two DNA sequences
#' count_kmers(
#'     c("ACAT", "ACC"),
#'     k=2,
#'     batch_size=batch_size)
#' 
#' # Counting positional 2-mers of two DNA sequences
#' count_kmers(
#'     c("ACAT", "ACC"),
#'     k=2,
#'     positional=TRUE,
#'     batch_size=batch_size)
#' 
#' # Counting positional 2-mers of two DNA sequences (second representation)
#' count_kmers(
#'      list(c("A", "C", "A", "T"), c("A", "C", "C")),
#'      k=2,
#'      positional=TRUE,
#'      batch_size=batch_size)
#' 
#' # Counting 3-mers of two DNA sequences, considering only A and C elements
#' count_kmers(
#'     c("ACAT", "ACC"),
#'     k=2,
#'     kmer_alphabet=c("A", "C"),
#'     batch_size=batch_size)
#' 
#' # Counting gapped 3-mers with lengths of gaps 1 and 2
#' count_kmers(
#'     c("ACATACTAT", "ACCCCCC"),
#'     kmer_gaps=c(1,2),
#'     batch_size=batch_size)
#' 
#' @seealso Function that counts many k-mer variants in the single invocation: \link[seqR]{count_multimers}
#' @seealso Function that merges several k-mer matrices (rbind): \link[seqR]{rbind_columnwise}
#' @include atomic_validators.R
#' @include kmer_functions_provider.R
#' @export
#' @md
count_kmers <- function(sequences,
                        k = length(kmer_gaps) + 1,
                        kmer_alphabet = getOption("seqR_kmer_alphabet_default"),
                        positional = getOption("seqR_positional_default"),
                        kmer_gaps = c(),
                        with_kmer_counts = getOption("seqR_with_kmer_counts_default"),
                        with_kmer_names = getOption("seqR_with_kmer_names_default"),
                        batch_size = getOption("seqR_batch_size_default"),
                        hash_dim = getOption("seqR_hash_dim_default"),
                        verbose = getOption("seqR_verbose_default")) {
  kmer_alphabet <- unique(kmer_alphabet)
  
  .validate_kmer_alphabet(kmer_alphabet)
  .validate_sequences(sequences)
  .validate_k(k)
  .validate_kmer_gaps(kmer_gaps, k)
  .validate_batch_size(batch_size)
  .validate_hash_dim(hash_dim)
  .validate_verbose(verbose)
  
  params <- rlang::env(
    kmer_alphabet=kmer_alphabet,
    positional=positional,
    with_kmer_counts=with_kmer_counts,
    with_kmer_names=with_kmer_names,
    batch_size=batch_size,
    hash_dim=hash_dim,
    verbose=verbose,
    k=k
  )
  
  if(sum(kmer_gaps) == 0) {
    .invoke_contiguous_kmer_function(sequences=sequences, params=params)
  } else {
    params$gaps <- rep(kmer_gaps, length.out=k-1)
    .invoke_gapped_kmer_function(sequences=sequences, params=params)
  }
}

.validate_kmer_alphabet <- function(param) {
  if (is_empty(param)) {
    stop("alphabet param is empty")
  }
}

.validate_sequences <-function(param) {
  if(is_empty(param)) {
    stop("sequences param is empty")
  }
}

.validate_k <- function(param) {
  if(!has_integers_only(param) || param <= 0) {
    stop("k should be a positive integer")
  }
}

.validate_kmer_gaps <- function(param, k) {
  if(!is.null(param)) {
    if(!has_integers_only(param)) {
      stop("gaps should be an integer vector")
    }
    if(length(param) >= k) {
      stop("the length of kmer_gaps vector should be at most k-1")
    }
  }
}

#' @include common.R
.validate_batch_size <- function(param) {
  if(!is_positive_integer(param)) {
    stop("batch size field must be a positive integer number")
  }
  
  .show_message_if_batch_size_1(param)
}

.validate_hash_dim <- function(param) {
  if(!is_positive_integer(param) || param > 500) {
    stop("hash_dim is a single integer number from the range [1, 500]")
  }
}

.validate_verbose <- function(param) {
  if(!is_bool_value(param)) {
    stop("verbose must be a single logical value")
  }
}
