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
    {"_seqR_compute_polynomial_hash", (DL_FUNC) &_seqR_compute_polynomial_hash, 5},
    {"_seqR_compute_polynomial_multihash", (DL_FUNC) &_seqR_compute_polynomial_multihash, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_seqR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
