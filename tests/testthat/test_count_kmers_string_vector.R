library(testthat)
source("utils.R")

invoke_test <- function(expected_res, ...) {
  res <- seqR::count_kmers(hash_dim = 2,
                           verbose=FALSE,
                           parallel_mode=TRUE,
                           ...)
  expect_matrices_equal(as.matrix(res), expected_res)
}

test_that("count 3-mers for sequences A+ in a list", {
  sq <- c("AAAAA", "AA", "AAAAAAA")
  expected_res <- matrix(c(
    3,
    0,
    5
  ), nrow=3)
  colnames(expected_res) <- c("A.A.A_0.0")
  invoke_test(expected_res=expected_res,
              alphabet=c("A"),
              sequences=sq,
              k=3,
              positional=FALSE,
              with_kmer_counts=TRUE,
              kmer_dictionary_name = "linear_list",
              batch_size = 200)
})

test_that("count 3-mers for sequences A+ longer in a list", {
  sq <- c(strrep("A", 1000000), strrep("A", 1000), strrep("A", 100))
  expected_res <- matrix(c(
    999998,
    998,
    98
  ), nrow=3)
  colnames(expected_res) <- c("A.A.A_0.0")
  invoke_test(expected_res=expected_res,
              alphabet=c("A"),
              sequences=sq,
              k=3,
              positional=FALSE,
              with_kmer_counts=TRUE,
              kmer_dictionary_name = "linear_list",
              batch_size = 200)
})

test_that("count non positional 10-mers sequences A+ longer in a list", {
  sq <- c(strrep("A", 1000000), strrep("A", 100))
  expected_res <- matrix(c(
    999991,
    91
  ), nrow=2)
  colnames(expected_res) <- paste0(
    paste0(rep("A", 10), collapse="."),
    "_",
    paste0(rep("0", 9), collapse="."), collapse="")
  invoke_test(expected_res=expected_res,
              alphabet=c("A"),
              sequences=sq,
              k=10,
              positional=FALSE,
              with_kmer_counts=TRUE,
              kmer_dictionary_name="unordered_map",
              batch_size = 200)
})

test_that("find 3-mers for sequences A+ (without k-mer counts) in a list", {
  sq <- c("AAAAA", "AA", "AAAAAAA")
  expected_res <- matrix(c(
    1,
    0,
    1
  ), nrow=3)
  colnames(expected_res) <- c("A.A.A_0.0")
  invoke_test(expected_res=expected_res,
              alphabet=c("A"),
              sequences=sq,
              k=3,
              positional=FALSE,
              with_kmer_counts=FALSE,
              kmer_dictionary_name="linear_list",
              batch_size = 200)
})

test_that("find 15-mers for sequences (AC){1000000} in a list", {
  sq <- sapply(1:5, function(i) strrep("AC", 1000000))
  expected_res <- matrix(c(
    999993, 999993,
    999993, 999993,
    999993, 999993,
    999993, 999993,
    999993, 999993
  ), byrow=TRUE, nrow=5)
  colnames(expected_res) <- c("A.C.A.C.A.C.A.C.A.C.A.C.A.C.A_0.0.0.0.0.0.0.0.0.0.0.0.0.0",
                              "C.A.C.A.C.A.C.A.C.A.C.A.C.A.C_0.0.0.0.0.0.0.0.0.0.0.0.0.0")
  invoke_test(expected_res=expected_res,
              alphabet=c("A", "C"),
              sequences=sq,
              k=15,
              positional=FALSE,
              with_kmer_counts=TRUE,
              kmer_dictionary_name="unordered_map",
              batch_size = 10)
})