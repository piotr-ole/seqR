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
// count_gapped_kmers_string
Rcpp::IntegerMatrix count_gapped_kmers_string(Rcpp::StringVector& alphabet, Rcpp::StringMatrix& sequenceMatrix, Rcpp::IntegerVector& gaps, bool positionalKMers);
RcppExport SEXP _seqR_count_gapped_kmers_string(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_gapped_kmers_string(alphabet, sequenceMatrix, gaps, positionalKMers));
    return rcpp_result_gen;
END_RCPP
}
// count_gapped_kmers_integer
Rcpp::IntegerMatrix count_gapped_kmers_integer(Rcpp::IntegerVector& alphabet, Rcpp::IntegerMatrix& sequenceMatrix, Rcpp::IntegerVector& gaps, bool positionalKMers);
RcppExport SEXP _seqR_count_gapped_kmers_integer(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_gapped_kmers_integer(alphabet, sequenceMatrix, gaps, positionalKMers));
    return rcpp_result_gen;
END_RCPP
}
// count_gapped_kmers_numeric
Rcpp::IntegerMatrix count_gapped_kmers_numeric(Rcpp::NumericVector& alphabet, Rcpp::NumericMatrix& sequenceMatrix, Rcpp::IntegerVector& gaps, bool positionalKMers);
RcppExport SEXP _seqR_count_gapped_kmers_numeric(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP gapsSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type gaps(gapsSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_gapped_kmers_numeric(alphabet, sequenceMatrix, gaps, positionalKMers));
    return rcpp_result_gen;
END_RCPP
}
// count_kmers_string
Rcpp::IntegerMatrix count_kmers_string(Rcpp::StringVector& alphabet, Rcpp::StringMatrix& sequenceMatrix, int k, bool positionalKMers);
RcppExport SEXP _seqR_count_kmers_string(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP kSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_kmers_string(alphabet, sequenceMatrix, k, positionalKMers));
    return rcpp_result_gen;
END_RCPP
}
// count_kmers_integer
Rcpp::IntegerMatrix count_kmers_integer(Rcpp::IntegerVector& alphabet, Rcpp::IntegerMatrix& sequenceMatrix, int k, bool positionalKMers);
RcppExport SEXP _seqR_count_kmers_integer(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP kSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_kmers_integer(alphabet, sequenceMatrix, k, positionalKMers));
    return rcpp_result_gen;
END_RCPP
}
// count_kmers_numeric
Rcpp::IntegerMatrix count_kmers_numeric(Rcpp::NumericVector& alphabet, Rcpp::NumericMatrix& sequenceMatrix, int k, bool positionalKMers);
RcppExport SEXP _seqR_count_kmers_numeric(SEXP alphabetSEXP, SEXP sequenceMatrixSEXP, SEXP kSEXP, SEXP positionalKMersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type alphabet(alphabetSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix& >::type sequenceMatrix(sequenceMatrixSEXP);
    Rcpp::traits::input_parameter< int >::type k(kSEXP);
    Rcpp::traits::input_parameter< bool >::type positionalKMers(positionalKMersSEXP);
    rcpp_result_gen = Rcpp::wrap(count_kmers_numeric(alphabet, sequenceMatrix, k, positionalKMers));
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
    {"_seqR_count_gapped_kmers_string", (DL_FUNC) &_seqR_count_gapped_kmers_string, 4},
    {"_seqR_count_gapped_kmers_integer", (DL_FUNC) &_seqR_count_gapped_kmers_integer, 4},
    {"_seqR_count_gapped_kmers_numeric", (DL_FUNC) &_seqR_count_gapped_kmers_numeric, 4},
    {"_seqR_count_kmers_string", (DL_FUNC) &_seqR_count_kmers_string, 4},
    {"_seqR_count_kmers_integer", (DL_FUNC) &_seqR_count_kmers_integer, 4},
    {"_seqR_count_kmers_numeric", (DL_FUNC) &_seqR_count_kmers_numeric, 4},
    {"_seqR_compute_polynomial_hash", (DL_FUNC) &_seqR_compute_polynomial_hash, 5},
    {"_seqR_compute_polynomial_multihash", (DL_FUNC) &_seqR_compute_polynomial_multihash, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_seqR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
