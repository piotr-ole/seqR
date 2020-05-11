// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// encode_integer_alphabet
Rcpp::IntegerVector encode_integer_alphabet(Rcpp::IntegerVector& input);
RcppExport SEXP _seqR_encode_integer_alphabet(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(encode_integer_alphabet(input));
    return rcpp_result_gen;
END_RCPP
}
// encode_numeric_alphabet
Rcpp::IntegerVector encode_numeric_alphabet(Rcpp::NumericVector& input);
RcppExport SEXP _seqR_encode_numeric_alphabet(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(encode_numeric_alphabet(input));
    return rcpp_result_gen;
END_RCPP
}
// encode_string_alphabet
Rcpp::IntegerVector encode_string_alphabet(Rcpp::StringVector& input);
RcppExport SEXP _seqR_encode_string_alphabet(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(encode_string_alphabet(input));
    return rcpp_result_gen;
END_RCPP
}
// get_contiguous_intervals_matrix
Rcpp::IntegerMatrix get_contiguous_intervals_matrix(const Rcpp::IntegerVector& gaps);
RcppExport SEXP _seqR_get_contiguous_intervals_matrix(SEXP gapsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    rcpp_result_gen = Rcpp::wrap(get_contiguous_intervals_matrix(gaps));
    return rcpp_result_gen;
END_RCPP
}
// find_gapped_kmers_string
Rcpp::IntegerMatrix find_gapped_kmers_string(Rcpp::StringMatrix& sequenceMatrix, Rcpp::StringVector& alphabet, Rcpp::IntegerVector& gaps, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_gapped_kmers_string(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_gapped_kmers_string(sequenceMatrix, alphabet, gaps, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_gapped_kmers_integer
Rcpp::IntegerMatrix find_gapped_kmers_integer(Rcpp::IntegerMatrix& sequenceMatrix, Rcpp::IntegerVector& alphabet, Rcpp::IntegerVector& gaps, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_gapped_kmers_integer(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_gapped_kmers_integer(sequenceMatrix, alphabet, gaps, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_gapped_kmers_numeric
Rcpp::IntegerMatrix find_gapped_kmers_numeric(Rcpp::NumericMatrix& sequenceMatrix, Rcpp::NumericVector& alphabet, Rcpp::IntegerVector& gaps, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_gapped_kmers_numeric(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_gapped_kmers_numeric(sequenceMatrix, alphabet, gaps, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_gapped_kmers_tidysq
Rcpp::IntegerMatrix find_gapped_kmers_tidysq(Rcpp::List& sq, Rcpp::StringVector& alphabet, Rcpp::IntegerVector& gaps, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_gapped_kmers_tidysq(SEXP sqSEXP, SEXP alphabetSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type sq(sqSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_gapped_kmers_tidysq(sq, alphabet, gaps, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_kmers_string
Rcpp::IntegerMatrix find_kmers_string(Rcpp::StringMatrix& sequenceMatrix, Rcpp::StringVector& alphabet, int k, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_kmers_string(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP kSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_kmers_string(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_kmers_integer
Rcpp::IntegerMatrix find_kmers_integer(Rcpp::IntegerMatrix& sequenceMatrix, Rcpp::IntegerVector& alphabet, int k, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_kmers_integer(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP kSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_kmers_integer(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_kmers_numeric
Rcpp::IntegerMatrix find_kmers_numeric(Rcpp::NumericMatrix& sequenceMatrix, Rcpp::NumericVector& alphabet, int k, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_kmers_numeric(SEXP sequenceMatrixSEXP, SEXP alphabetSEXP, SEXP kSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_kmers_numeric(sequenceMatrix, alphabet, k, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// find_kmers_tidysq
Rcpp::IntegerMatrix find_kmers_tidysq(Rcpp::List& sq, Rcpp::StringVector& alphabet, int k, bool positionalKMers, bool withKMerCounts, const std::string& kmerDictionaryName);
RcppExport SEXP _seqR_find_kmers_tidysq(SEXP sqSEXP, SEXP alphabetSEXP, SEXP kSEXP, SEXP positionalKMersSEXP, SEXP withKMerCountsSEXP, SEXP kmerDictionaryNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type sq(sqSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    Rcpp::traits::input_parameter< bool >::type withKMerCounts(withKMerCountsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kmerDictionaryName(kmerDictionaryNameSEXP);
    rcpp_result_gen = Rcpp::wrap(find_kmers_tidysq(sq, alphabet, k, positionalKMers, withKMerCounts, kmerDictionaryName));
    return rcpp_result_gen;
END_RCPP
}
// compute_polynomial_hash
int compute_polynomial_hash(int P, int M, Rcpp::IntegerVector items, int begin, int position);
RcppExport SEXP _seqR_compute_polynomial_hash(SEXP PSEXP, SEXP MSEXP, SEXP itemsSEXP, SEXP beginSEXP, SEXP positionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type P(PSEXP);
    Rcpp::traits::input_parameter< int >::type M(MSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type items(itemsSEXP);
    Rcpp::traits::input_parameter< int >::type begin(beginSEXP);
    Rcpp::traits::input_parameter< int >::type position(positionSEXP);
    rcpp_result_gen = Rcpp::wrap(compute_polynomial_hash(P, M, items, begin, position));
    return rcpp_result_gen;
END_RCPP
}
// compute_polynomial_multihash
std::vector<int> compute_polynomial_multihash(Rcpp::IntegerVector P, Rcpp::IntegerVector M, Rcpp::IntegerVector items, int begin, int position);
RcppExport SEXP _seqR_compute_polynomial_multihash(SEXP PSEXP, SEXP MSEXP, SEXP itemsSEXP, SEXP beginSEXP, SEXP positionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type P(PSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type M(MSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type items(itemsSEXP);
    Rcpp::traits::input_parameter< int >::type begin(beginSEXP);
    Rcpp::traits::input_parameter< int >::type position(positionSEXP);
    rcpp_result_gen = Rcpp::wrap(compute_polynomial_multihash(P, M, items, begin, position));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_seqR_encode_integer_alphabet", (DL_FUNC) &_seqR_encode_integer_alphabet, 1},
    {"_seqR_encode_numeric_alphabet", (DL_FUNC) &_seqR_encode_numeric_alphabet, 1},
    {"_seqR_encode_string_alphabet", (DL_FUNC) &_seqR_encode_string_alphabet, 1},
    {"_seqR_get_contiguous_intervals_matrix", (DL_FUNC) &_seqR_get_contiguous_intervals_matrix, 1},
    {"_seqR_find_gapped_kmers_string", (DL_FUNC) &_seqR_find_gapped_kmers_string, 6},
    {"_seqR_find_gapped_kmers_integer", (DL_FUNC) &_seqR_find_gapped_kmers_integer, 6},
    {"_seqR_find_gapped_kmers_numeric", (DL_FUNC) &_seqR_find_gapped_kmers_numeric, 6},
    {"_seqR_find_gapped_kmers_tidysq", (DL_FUNC) &_seqR_find_gapped_kmers_tidysq, 6},
    {"_seqR_find_kmers_string", (DL_FUNC) &_seqR_find_kmers_string, 6},
    {"_seqR_find_kmers_integer", (DL_FUNC) &_seqR_find_kmers_integer, 6},
    {"_seqR_find_kmers_numeric", (DL_FUNC) &_seqR_find_kmers_numeric, 6},
    {"_seqR_find_kmers_tidysq", (DL_FUNC) &_seqR_find_kmers_tidysq, 6},
    {"_seqR_compute_polynomial_hash", (DL_FUNC) &_seqR_compute_polynomial_hash, 5},
    {"_seqR_compute_polynomial_multihash", (DL_FUNC) &_seqR_compute_polynomial_multihash, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_seqR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
