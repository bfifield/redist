/////////////////////////////////////
// Author: Rei Yatsuhashi
// Institution: American School In Japan
// Date Created: 2020/06/27
// Date Modified: 2020/06/27
// Purpose: Header file for redist_aList_beta class
/////////////////////////////////////

#ifndef REDIST_ALIST_B
#define REDIST_ALIST_B

#include "redist.h"
#include <time.h>
#include <R.h>
#include "sw_mh_helper.h"
#include "make_swaps_helper.h"
#include "constraint_calc_helper.h"
#include "redist_analysis.h"

class redist_aList_beta;
RCPP_EXPOSED_CLASS(redist_aList_beta)

// Class to consolidate methods relating to the constraints and tempering for redistricting
class redist_aList_beta: public redist_aList {
  
  protected:
    
    double pct_dist_parity;
  
    Rcpp::NumericVector grouppopvec;
  
    Rcpp::NumericVector beta_sequence;
    
    Rcpp::NumericMatrix ssdmat;
    
    Rcpp::NumericVector beta_weights = Rcpp::NumericVector::create(Rcpp::Named("population") = 0.0, Rcpp::Named("compact") = 0.0, 
                                                Rcpp::Named("segregation") = 0.0, Rcpp::Named("similar") = 0.0);
  
    Rcpp::NumericVector distswitch;
  
    int adjswap = 1;

    /* Inputs to function:
     
     pct_dist_parity: strength of population parity requirement
     
     grouppopvec: vector of subgroup populations for each geographic unit
     
     beta_sequence: sequence of betas to anneal over
     
     ssdmat: matrix of squared distances between geographic units. For constraining
     on compactness
     
     beta_weights: {beta_population, beta_compact, beta_segregation, beta_similar}
     
       beta_population: strength of constraint for achieving population parity
     
       beta_compact: strength of constraint for achieving district compactness
     
       beta_segregation: strength of constraint for packing group into district
     
       beta_similar: strength of constraint for examining plans similar to original district
     
     distswitch: vector containing the old district, and the proposed new district
     
     adjswap: flag - do we want adjacent swaps? default to 1
     
     */
  
  public:
  
    // Constructor for constraint-related values
    redist_aList_beta(double p = 0.05, Rcpp::NumericVector b_s = {0.0, 0.0, 0.0, 0.0}, Rcpp::NumericVector b_w = {0.0, 0.0, 0.0, 0.0}, Rcpp::NumericMatrix ssd = {0.0}, Rcpp::NumericVector d = {0.0});
    
    void update_current_dists(Rcpp::NumericVector c);
    void update_distswitch(); 
    Rcpp::NumericVector get_grouppopvec();
    Rcpp::NumericMatrix get_ssdmat();
    Rcpp::NumericVector get_beta_sequence();
    Rcpp::NumericVector get_beta_weights();
    double get_pct_dist_parity();

    void update_weights(double b, std::string s);

    // Function that applies the Geyer Thompson algorithm for simulated tempering
    Rcpp::List changeBeta(double beta, double constraint);
  
    // Function to calculate the strength of the beta constraint for population
    Rcpp::List calc_betapop(arma::vec new_dists);
    
    // Function to calculate the strength of the beta constraint for compactness
    // Fryer and Holden 2011 RPI index
    Rcpp::List calc_betacompact(arma::vec new_dists, double denominator = 1.0);
	
    // Function to constrain by segregating a group
    Rcpp::List calc_betasegregation(arma::vec new_dists);
  
    // Function to constrain on plan similarity to original plan
    Rcpp::List calc_betasimilar(arma::vec new_dists);

};

using namespace Rcpp;

// Class to consolidate methods relating to the constraints and tempering for redistricting

// Constructor

inline redist_aList_beta::redist_aList_beta(double p, NumericVector b_s, NumericVector b_w, NumericMatrix ssd, Rcpp::NumericVector d) 
{
  
  pct_dist_parity = p;
  beta_sequence = b_s;
  beta_weights= b_w;
  ssdmat = ssd;
  distswitch = d;
  
}

inline void redist_aList_beta::update_distswitch()
{

  for(int i = 0; i < cdvec.size(); i++){
    if(is_true(any(distswitch == cdvec(i))) == FALSE){
      distswitch.push_back(cdvec(i));
    }
  }
  
}

inline NumericVector redist_aList_beta::get_grouppopvec() 
{
  
  return grouppopvec;
  
}

inline NumericMatrix redist_aList_beta::get_ssdmat() 
{
  
  return ssdmat;
  
}

inline NumericVector redist_aList_beta::get_beta_sequence() 
{
  
  return beta_sequence;
  
}

inline NumericVector redist_aList_beta::get_beta_weights() 
{
  
  return beta_weights;
  
}

inline double redist_aList_beta::get_pct_dist_parity() 
{
  
  return pct_dist_parity;
  
}

inline void redist_aList_beta::update_weights(double b, std::string s)
{

  beta_weights[s] = b;
  
}


// Function that applies the Geyer Thompson algorithm for simulated tempering
inline List redist_aList_beta::changeBeta(double beta, double constraint)
{
  
  /* Inputs to function 
     
     beta: current value of the beta constraint
     
     constraint: the evaluation of the constraint on the current plan
     
   */
  
  // Find beta in betas
  arma::uvec findBetaVec = arma::find((arma::vec) (beta_sequence) == beta);
  int findBeta = findBetaVec(0);

  // Object to test whether beta is at RHS of vector
  int betaLoc = beta_sequence.size() - 1;

  // Get transition probabilities and propose a new beta
  double qij;
  double qji;
  double wi;
  double wj;
  double propBeta;

  // Procedure if conducting adjacent swaps
  if(adjswap == 1){
    if(findBeta == 0){ // At first element in betas   
      qij = 1;
      qji = .5;
      wi = beta_weights(0);
      wj = beta_weights(1);
      propBeta = beta_sequence(1);
    } else if(findBeta == betaLoc){ // At last element in betas
      qij = 1;
      qji = .5;
      wi = beta_weights(betaLoc);
      wj = beta_weights(betaLoc - 1);
      propBeta = beta_sequence(betaLoc - 1);
    } else{ // Anywhere in the middle of betas
      qij = .5;
      qji = .5;
      wi = beta_weights(findBeta);
      arma::vec betaswitch = runif(1);
      if(betaswitch(0) < .5){
        propBeta = beta_sequence(findBeta - 1);
        wj = beta_weights(findBeta - 1);
      }
      if(betaswitch(0) >= .5){
        propBeta = beta_sequence(findBeta + 1);
        wj = beta_weights(findBeta + 1);
      }
    }
  } else{
    // Procedure if not conducting adjacent swaps
    // qij = qji in non-adjacent framework, don't have to worry abt end units
    qij = 1;
    qji = 1;

    // Draw element from betavec
    arma::vec rand_randindex = runif(1, 0, 1000000000);
    int randindex = fmod(rand_randindex(0), betaLoc);

    // Weight wi 
    wi = beta_weights(findBeta);

    // Draw the proposed beta value
    if(randindex < findBeta){
      propBeta = beta_sequence(randindex);
      wj = beta_weights(randindex);
    } else{
      propBeta = beta_sequence(randindex + 1);
      wj = beta_weights(randindex + 1);
    }

  }

  // Accept or reject the proposal
  double mhprobGT = (double) exp(constraint * (propBeta - beta)) * wj / wi * qji / qij;
  if(mhprobGT > 1){
    mhprobGT = 1;
  }
  arma::vec testkeepGT = runif(1);
  int decision = 0;
  if(testkeepGT(0) <= mhprobGT){
    decision++;
    beta = propBeta;
  }

  // Create output
  List out;
  out["beta"] = beta;
  out["mh_decision"] = decision;
  out["mh_prob"] = mhprobGT;

  return out;

}

// Function to calculate the strength of the beta constraint for population
inline List redist_aList_beta::calc_betapop(arma::vec new_dists)
{

  /* Inputs to function
     
     new_dists: vector of the new cong district assignments
     
   */
	
  double beta_population = beta_sequence["population"];
  
  // Calculate parity
  double parity = (double) sum(popvec) / (max(cdvec) + 1);

  // Log_e(2)
  double loge2 = log(2.0);

  // Initialize psi values
  double psi_new = 0.0;
  double psi_old = 0.0;

  // Loop over congressional districts
  for(int i = 0; i < distswitch.size(); i++){

    // Population objects
    int pop_new = 0;
    int pop_old = 0;
    arma::uvec new_cds = arma::find((new_dists) == distswitch(i));
    arma::uvec current_cds = arma::find((arma::vec) (cdvec) == distswitch(i));

    // Get population of the old districts
    for(int j = 0; j < new_cds.size(); j++){
      pop_new += popvec(new_cds(j));
    }
    for(int j = 0; j < current_cds.size(); j++){
      pop_old += popvec(current_cds(j));
    }

    // Calculate the penalty
    psi_new += (double)std::abs((pop_new / parity) - 1);
    psi_old += (double)std::abs((pop_old / parity) - 1);

  }

  // Calculate the ratio
  double ratio = (double) exp(beta_population * loge2 * (psi_new - psi_old));

  // Create return object
  List out;
  out["pop_ratio"] = ratio;
  out["pop_new_psi"] = psi_new;
  out["pop_old_psi"] = psi_old;

  return out;

}

// Function to calculate the strength of the beta constraint for compactness
// Fryer and Holden 2011 RPI index
inline List redist_aList_beta::calc_betacompact(arma::vec new_dists,
		      double denominator){

  /* Inputs to function:
  
     new_dists: vector of the new cong district assignments
     
     denominator: normalizing constant for rpi
     
   */
  
  double beta_compact = beta_sequence["compact"];
  
  // Initialize psi values
  double psi_new = 0.0;
  double psi_old = 0.0;

  // Log_e(2)
  double loge2 = log(2.0);

  // Loop over the congressional districts
  for(int i = 0; i < distswitch.size(); i++){

    // Initialize objects
    double ssd_new = 0.0;
    double ssd_old = 0.0;
    arma::uvec new_cds = arma::find((new_dists) == distswitch(i));
    arma::uvec current_cds = arma::find((arma::vec) (cdvec) == distswitch(i));

    // SSD for new partition
    for(int j = 0; j < new_cds.size(); j++){
      for(int k = j + 1; k < new_cds.size(); k++){
	      ssd_new += (double) ssdmat(new_cds(j),new_cds(k)) *
	        popvec(new_cds(j)) * popvec(new_cds(k));
      }
    }

    // SSD for old partition
    for(int j = 0; j < current_cds.size(); j++){
      for(int k = j + 1; k < current_cds.size(); k++){
	      ssd_old += (double) ssdmat(current_cds(j),current_cds(k)) *
	      popvec(current_cds(j)) * popvec(current_cds(k));
      }
    }

    // Add to psi
    psi_new += ssd_new;
    psi_old += ssd_old;

  }

  // Normalize psi
  psi_new = (double) psi_new / denominator;
  psi_old = (double) psi_new / denominator;

  // Calculate ratio
  double ratio = (double) exp(beta_compact * loge2 * (psi_new - psi_old));

  // Create return object
  List out;
  out["compact_ratio"] = ratio;
  out["compact_new_psi"] = psi_new;
  out["compact_old_psi"] = psi_old;

  return out;

}

// Function to constrain by segregating a group
inline List redist_aList_beta::calc_betasegregation(arma::vec new_dists)
{

  /* Inputs to function:
     new_dists: vector of the new cong district assignments
     
  */
  
  double beta_segregation = beta_sequence["segregation"];

  // Initialize psi values
  double psi_new = 0.0;
  double psi_old = 0.0;

  // Log_e(2)
  double loge2 = log(2.0);

  // Initialize denominator
  int T = sum(popvec);
  double pAll = (double) sum(grouppopvec) / T;
  double denom = (double)2 * T * pAll * (1 - pAll);
  
  // Loop over congressional districts
  for(int i = 0; i < distswitch.size(); i++){

    // Initialize objects
    int oldpopall = 0;
    int newpopall = 0;
    int oldpopgroup = 0;
    int newpopgroup = 0;
    arma::uvec new_cds = arma::find((new_dists) == distswitch(i));
    arma::uvec current_cds = arma::find((arma::vec) (cdvec) == distswitch(i));
  
    // Segregation for proposed assignments
    for(int j = 0; j < new_cds.size(); j++){
      newpopall += popvec(new_cds(j));
      newpopgroup += grouppopvec(new_cds(j));
    }
  
    // Segregation for current assignments
    for(int j = 0; j < current_cds.size(); j++){
      oldpopall += popvec(current_cds(j));
      oldpopgroup += grouppopvec(current_cds(j));
    }
  
    // Calculate proportions
    // Rcout << "old population group " << oldpopgroup << std::endl;
    // Rcout << "old population all " << oldpopall << std::endl;
    double oldgroupprop = (double) oldpopgroup / oldpopall;
    // Rcout << "old proportion group " << oldgroupprop << std::endl;
    double newgroupprop = (double) newpopgroup / newpopall;

    // Get dissimilarity index
    psi_new += (double)(newpopall * std::abs(newgroupprop - pAll));
    psi_old += (double)(oldpopall * std::abs(oldgroupprop - pAll));

  }
  
  // Standardize psi
  psi_new = (double) psi_new / denom;
  psi_old = (double) psi_old / denom;

  // Get mh ratio
  double ratio = (double) exp(beta_segregation * loge2 * (psi_new - psi_old));

  // Create return object
  List out;
  out["segregation_ratio"] = ratio;
  out["segregation_new_psi"] = psi_new;
  out["segregation_old_psi"] = psi_old;

  return out;

}

// Function to constrain on plan similarity to original plan
inline List redist_aList_beta::calc_betasimilar(arma::vec new_dists)
{

  /* Inputs to function:
  
     new_dists: vector of the new cong district assignments
   */
  
  double beta_similar = beta_sequence["similar"];
  
  // Initialize psi values
  double psi_new = 0.0;
  double psi_old = 0.0;

  // Log_e(2)
  double loge2 = log(2.0);

  // Loop over congressional districts
  for(int i = 0; i < distswitch.size(); i++){

    // Initialize objects
    int new_count = 0;
    int old_count = 0;
    NumericVector orig_cds = wrap(arma::find((arma::vec) (cdorigvec) == distswitch(i)));
    arma::uvec new_cds = arma::find((new_dists) == distswitch(i));
    arma::uvec current_cds = arma::find((arma::vec) (cdvec) == distswitch(i));

    // Similarity measure for proposed assignments
    for(int j = 0; j < new_cds.size(); j++){
      if(any(cdorigvec == new_cds(j)).is_true()){
    	new_count++;
      }
    }

    // Similarity measure for current assignments
    for(int j = 0; j < current_cds.size(); j++){
      if(any((cdorigvec) == cdvec(j)).is_true()){
    	old_count++;
      }
    }

    // Calculate proportions
    double old_count_prop = (double) old_count / cdorigvec.size();
    double new_count_prop = (double) new_count / cdorigvec.size();
    
    // Add to psi
    psi_new += (double) std::abs(new_count_prop - 1);
    psi_old += (double) std::abs(old_count_prop - 1);

  }

  // Normalize by dividing by number of congressional districts
  psi_new = psi_new / distswitch.size();
  psi_old = psi_old / distswitch.size();

  // Get MH ratio
  double ratio = (double) exp(beta_similar * loge2 * (psi_new - psi_old));

  // Create return object
  List out;
  out["similar_ratio"] = ratio;
  out["similar_new_psi"] = psi_new;
  out["similar_old_psi"] = psi_old;

  return out;
}



#endif

// Expose classes to R:
RCPP_MODULE(redist_aList_beta_cpp){
  using namespace Rcpp;
  
  class_<redist_aList_beta>("redist_aList_beta")
    .default_constructor("Default Constructor")
    .method("update_weights", &redist_aList_beta::update_weights)
    .method("changeBeta", &redist_aList_beta::changeBeta)
    .method("calc_betapop", &redist_aList_beta::calc_betapop)
    .method("calc_betacompact", &redist_aList_beta::calc_betacompact)
    .method("calc_betasegregation", &redist_aList_beta::calc_betasegregation)
    .method("calc_betasimilar", &redist_aList_beta::calc_betasimilar)
  ;
}
//.method("", &redist_aList_beta::)
