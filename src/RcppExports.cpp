// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// NumberConnectedComponents
int NumberConnectedComponents(std::vector<std::string> strs, int mmallowed);
RcppExport SEXP _Rncc_NumberConnectedComponents(SEXP strsSEXP, SEXP mmallowedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<std::string> >::type strs(strsSEXP);
    Rcpp::traits::input_parameter< int >::type mmallowed(mmallowedSEXP);
    rcpp_result_gen = Rcpp::wrap(NumberConnectedComponents(strs, mmallowed));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Rncc_NumberConnectedComponents", (DL_FUNC) &_Rncc_NumberConnectedComponents, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_Rncc(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
