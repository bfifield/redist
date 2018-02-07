// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// cppGeneratePartitions
List cppGeneratePartitions(List adjList, int numBlocks, NumericVector popSizes, int numConstraintLow, int numConstraintHigh, double popConstraintLow, double popConstraintHigh);
RcppExport SEXP redist_cppGeneratePartitions(SEXP adjListSEXP, SEXP numBlocksSEXP, SEXP popSizesSEXP, SEXP numConstraintLowSEXP, SEXP numConstraintHighSEXP, SEXP popConstraintLowSEXP, SEXP popConstraintHighSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type adjList(adjListSEXP);
    Rcpp::traits::input_parameter< int >::type numBlocks(numBlocksSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type popSizes(popSizesSEXP);
    Rcpp::traits::input_parameter< int >::type numConstraintLow(numConstraintLowSEXP);
    Rcpp::traits::input_parameter< int >::type numConstraintHigh(numConstraintHighSEXP);
    Rcpp::traits::input_parameter< double >::type popConstraintLow(popConstraintLowSEXP);
    Rcpp::traits::input_parameter< double >::type popConstraintHigh(popConstraintHighSEXP);
    rcpp_result_gen = Rcpp::wrap(cppGeneratePartitions(adjList, numBlocks, popSizes, numConstraintLow, numConstraintHigh, popConstraintLow, popConstraintHigh));
    return rcpp_result_gen;
END_RCPP
}
// countpartitions
int countpartitions(List aList);
RcppExport SEXP redist_countpartitions(SEXP aListSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type aList(aListSEXP);
    rcpp_result_gen = Rcpp::wrap(countpartitions(aList));
    return rcpp_result_gen;
END_RCPP
}
// calcPWDh
NumericMatrix calcPWDh(NumericMatrix x);
RcppExport SEXP redist_calcPWDh(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(calcPWDh(x));
    return rcpp_result_gen;
END_RCPP
}
// segregationcalc
NumericVector segregationcalc(NumericMatrix distmat, NumericVector grouppop, NumericVector fullpop);
RcppExport SEXP redist_segregationcalc(SEXP distmatSEXP, SEXP grouppopSEXP, SEXP fullpopSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type distmat(distmatSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type grouppop(grouppopSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type fullpop(fullpopSEXP);
    rcpp_result_gen = Rcpp::wrap(segregationcalc(distmat, grouppop, fullpop));
    return rcpp_result_gen;
END_RCPP
}
// rsg
List rsg(List adj_list, NumericVector population, int Ndistrict, double target_pop, double thresh, int maxiter);
RcppExport SEXP redist_rsg(SEXP adj_listSEXP, SEXP populationSEXP, SEXP NdistrictSEXP, SEXP target_popSEXP, SEXP threshSEXP, SEXP maxiterSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type adj_list(adj_listSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type population(populationSEXP);
    Rcpp::traits::input_parameter< int >::type Ndistrict(NdistrictSEXP);
    Rcpp::traits::input_parameter< double >::type target_pop(target_popSEXP);
    Rcpp::traits::input_parameter< double >::type thresh(threshSEXP);
    Rcpp::traits::input_parameter< int >::type maxiter(maxiterSEXP);
    rcpp_result_gen = Rcpp::wrap(rsg(adj_list, population, Ndistrict, target_pop, thresh, maxiter));
    return rcpp_result_gen;
END_RCPP
}
// swMH
List swMH(List aList, NumericVector cdvec, NumericVector cdorigvec, NumericVector popvec, NumericVector grouppopvec, NumericVector areas_vec, NumericVector county_membership, arma::mat borderlength_mat, int nsims, double eprob, double pct_dist_parity, NumericVector beta_sequence, NumericVector beta_weights, NumericMatrix ssdmat, int lambda, double beta, double weight_population, double weight_compact, double weight_segregation, double weight_similar, double weight_countysplit, int anneal_beta, int adjswap, int exact_mh, int adapt_eprob, int adapt_lambda, std::string compactness_measure);
RcppExport SEXP redist_swMH(SEXP aListSEXP, SEXP cdvecSEXP, SEXP cdorigvecSEXP, SEXP popvecSEXP, SEXP grouppopvecSEXP, SEXP areas_vecSEXP, SEXP county_membershipSEXP, SEXP borderlength_matSEXP, SEXP nsimsSEXP, SEXP eprobSEXP, SEXP pct_dist_paritySEXP, SEXP beta_sequenceSEXP, SEXP beta_weightsSEXP, SEXP ssdmatSEXP, SEXP lambdaSEXP, SEXP betaSEXP, SEXP weight_populationSEXP, SEXP weight_compactSEXP, SEXP weight_segregationSEXP, SEXP weight_similarSEXP, SEXP weight_countysplitSEXP, SEXP anneal_betaSEXP, SEXP adjswapSEXP, SEXP exact_mhSEXP, SEXP adapt_eprobSEXP, SEXP adapt_lambdaSEXP, SEXP compactness_measureSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type aList(aListSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type cdvec(cdvecSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type cdorigvec(cdorigvecSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type popvec(popvecSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type grouppopvec(grouppopvecSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type areas_vec(areas_vecSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type county_membership(county_membershipSEXP);
    Rcpp::traits::input_parameter< arma::mat >::type borderlength_mat(borderlength_matSEXP);
    Rcpp::traits::input_parameter< int >::type nsims(nsimsSEXP);
    Rcpp::traits::input_parameter< double >::type eprob(eprobSEXP);
    Rcpp::traits::input_parameter< double >::type pct_dist_parity(pct_dist_paritySEXP);
    Rcpp::traits::input_parameter< NumericVector >::type beta_sequence(beta_sequenceSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type beta_weights(beta_weightsSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type ssdmat(ssdmatSEXP);
    Rcpp::traits::input_parameter< int >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< double >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type weight_population(weight_populationSEXP);
    Rcpp::traits::input_parameter< double >::type weight_compact(weight_compactSEXP);
    Rcpp::traits::input_parameter< double >::type weight_segregation(weight_segregationSEXP);
    Rcpp::traits::input_parameter< double >::type weight_similar(weight_similarSEXP);
    Rcpp::traits::input_parameter< double >::type weight_countysplit(weight_countysplitSEXP);
    Rcpp::traits::input_parameter< int >::type anneal_beta(anneal_betaSEXP);
    Rcpp::traits::input_parameter< int >::type adjswap(adjswapSEXP);
    Rcpp::traits::input_parameter< int >::type exact_mh(exact_mhSEXP);
    Rcpp::traits::input_parameter< int >::type adapt_eprob(adapt_eprobSEXP);
    Rcpp::traits::input_parameter< int >::type adapt_lambda(adapt_lambdaSEXP);
    Rcpp::traits::input_parameter< std::string >::type compactness_measure(compactness_measureSEXP);
    rcpp_result_gen = Rcpp::wrap(swMH(aList, cdvec, cdorigvec, popvec, grouppopvec, areas_vec, county_membership, borderlength_mat, nsims, eprob, pct_dist_parity, beta_sequence, beta_weights, ssdmat, lambda, beta, weight_population, weight_compact, weight_segregation, weight_similar, weight_countysplit, anneal_beta, adjswap, exact_mh, adapt_eprob, adapt_lambda, compactness_measure));
    return rcpp_result_gen;
END_RCPP
}
// genAlConn
List genAlConn(List aList, NumericVector cds);
RcppExport SEXP redist_genAlConn(SEXP aListSEXP, SEXP cdsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type aList(aListSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type cds(cdsSEXP);
    rcpp_result_gen = Rcpp::wrap(genAlConn(aList, cds));
    return rcpp_result_gen;
END_RCPP
}
// findBoundary
NumericVector findBoundary(List fullList, List conList);
RcppExport SEXP redist_findBoundary(SEXP fullListSEXP, SEXP conListSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type fullList(fullListSEXP);
    Rcpp::traits::input_parameter< List >::type conList(conListSEXP);
    rcpp_result_gen = Rcpp::wrap(findBoundary(fullList, conList));
    return rcpp_result_gen;
END_RCPP
}
