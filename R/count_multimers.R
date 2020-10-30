#' @include count_kmers.R
#' @export
count_multimers <- function(sequences,
                            k_vector,
                            alphabet,
                            positional_vector=rep(FALSE, length(k_vector)),
                            kmer_gaps_list=rep(list(c()), length(k_vector)),
                            with_kmer_counts=TRUE,
                            kmer_dictionary_name="unordered_map",
                            batch_size=200) {
  if(length(k_vector) != length(kmer_gaps_list)) {
    stop("the length of 'k_vector' must have equal length to 'kmer_gaps_list' ")
  }
  
  if(length(k_vector) != length(positional_vector)) {
    stop("the length of 'k_vector' must have equal length to 'positional vector'")
  }
  
  configs_num <- length(k_vector)
  do.call(cbind, lapply(1:configs_num, function(index) {
    count_kmers(sequences,
                k_vector[index],
                alphabet,
                positional_vector[index],
                kmer_gaps_list[[index]],
                with_kmer_counts,
                kmer_dictionary_name,
                batch_size)
  }))
}