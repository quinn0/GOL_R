#include <iostream>
#include <vector>
#include <ctime>
#include <Rcpp.h>
#include <cstdlib> // For rand() and RAND_MAX
using namespace Rcpp;

// Function to generate a random state
// [[Rcpp::export]]
NumericMatrix random_state(int dimx = 500, int dimy = 500, double threshold = 0.48) {
  NumericMatrix rand_state(dimx, dimy);
  for (int i = 0; i < dimx; ++i) {
    for (int j = 0; j < dimy; ++j) {
      rand_state(i, j) = ((double) rand() / (RAND_MAX)) < threshold;
    }
  }
  return rand_state;
}

// Function to get neighbors
NumericMatrix get_neighbors(NumericMatrix state, int i, int j) {

  // Loop over the 3x3 neighborhood
  int xdim = state.nrow();
  int ydim = state.ncol();
  
  NumericMatrix neighborhood(3, 3);
  
  if (i == 0) {
    if (j == 0) {
      neighborhood(0, 0) = state(xdim - 1, ydim - 1);
      neighborhood(0, 1) = state(xdim - 1, j);
      neighborhood(0, 2) = state(xdim - 1, j + 1);
      neighborhood(1, 0) = state(i, ydim - 1);
      neighborhood(1, 1) = false;
      neighborhood(1, 2) = state(i, j + 1);
      neighborhood(2, 0) = state(i + 1, ydim - 1);
      neighborhood(2, 1) = state(i + 1, j);
      neighborhood(2, 2) = state(i + 1, j + 1);
    } else if (j == ydim - 1) {
      neighborhood(0, 0) = state(xdim - 1, j - 1);
      neighborhood(0, 1) = state(xdim - 1, j);
      neighborhood(0, 2) = state(xdim - 1, 0);
      neighborhood(1, 0) = state(i, j - 1);
      neighborhood(1, 1) = false;
      neighborhood(1, 2) = state(i, 0);
      neighborhood(2, 0) = state(i + 1, j - 1);
      neighborhood(2, 1) = state(i + 1, j);
      neighborhood(2, 2) = state(i + 1, 0);
    } else {
      neighborhood(0, 0) = state(xdim - 1, j - 1);
      neighborhood(0, 1) = state(xdim - 1, j);
      neighborhood(0, 2) = state(xdim - 1, j + 1);
      neighborhood(1, 0) = state(i, j - 1);
      neighborhood(1, 1) = false;
      neighborhood(1, 2) = state(i, j + 1);
      neighborhood(2, 0) = state(i + 1, j - 1);
      neighborhood(2, 1) = state(i + 1, j);
      neighborhood(2, 2) = state(i + 1, j + 1);
    }
  } else if (i == xdim - 1) {
      if(j == ydim - 1){
      
        neighborhood(0, 0) = state(i - 1, j - 1);
        neighborhood(0, 1) = state(i - 1, j);
        neighborhood(0, 2) = state(i - 1, 0);
        neighborhood(1, 0) = state(i, j-1);
        neighborhood(1, 1) = false;
        neighborhood(1, 2) = state(i, 0);
        neighborhood(2, 0) = state(0, j - 1);
        neighborhood(2, 1) = state(0, j);
        neighborhood(2, 2) = state(0, 0);
      }
      else if (j == 0) {
        neighborhood(0, 0) = state(i - 1, ydim - 1);
        neighborhood(0, 1) = state(i - 1, j);
        neighborhood(0, 2) = state(i - 1, j + 1);
        neighborhood(1, 0) = state(i, ydim - 1);
        neighborhood(1, 1) = false;
        neighborhood(1, 2) = state(i, j + 1);
        neighborhood(2, 0) = state(0, ydim - 1);
        neighborhood(2, 1) = state(0, j);
        neighborhood(2, 2) = state(0, j + 1);     
      
      } 
      else {
        neighborhood(0, 0) = state(i - 1, j - 1);
        neighborhood(0, 1) = state(i - 1, j);
        neighborhood(0, 2) = state(i - 1, j + 1);
        neighborhood(1, 0) = state(i, j - 1);
        neighborhood(1, 1) = false;
        neighborhood(1, 2) = state(i, j + 1);
        neighborhood(2, 0) = state(i- 1, j - 1);
        neighborhood(2, 1) = state(i - 1, j);
        neighborhood(2, 2) = state(i - 1, j + 1);     
      }
      
  } 
  else if (j == ydim-1){
    neighborhood(0, 0) = state(i - 1, j - 1);
    neighborhood(0, 1) = state(i - 1, j);
    neighborhood(0, 2) = state(i - 1, 0);
    neighborhood(1, 0) = state(i, j - 1);
    neighborhood(1, 1) = false;
    neighborhood(1, 2) = state(i, 0);
    neighborhood(2, 0) = state(i + 1, j - 1);
    neighborhood(2, 1) = state(i + 1, j);
    neighborhood(2, 2) = state(i + 1, 0);  
    
  } else if (j == 0)
    {
    neighborhood(0, 0) = state(i - 1, ydim - 1);
    neighborhood(0, 1) = state(i - 1, j);
    neighborhood(0, 2) = state(i - 1, j+1);
    neighborhood(1, 0) = state(i, ydim - 1);
    neighborhood(1, 1) = false;
    neighborhood(1, 2) = state(i, j + 1);
    neighborhood(2, 0) = state(i + 1, ydim - 1);
    neighborhood(2, 1) = state(i + 1, j);
    neighborhood(2, 2) = state(i + 1, 0);  
    }
  else {
        neighborhood(0, 0) = state(i - 1, j - 1);
        neighborhood(0, 1) = state(i - 1, j);
        neighborhood(0, 2) = state(i - 1, j + 1);
        neighborhood(1, 0) = state(i, j - 1);
        neighborhood(1, 1) = false;
        neighborhood(1, 2) = state(i, j + 1);
        neighborhood(2, 0) = state(i + 1, j - 1);
        neighborhood(2, 1) = state(i + 1, j);
        neighborhood(2, 2) = state(i + 1, j + 1);  
        } 
  return neighborhood;
}
// Function to count the number of live cells in a neighborhood
int bodycount(NumericMatrix vec) {
  int sum = 0;
  int nrow = vec.nrow();
  int ncol = vec.ncol();
  for (int i = 0; i < nrow; ++i) {
    for (int j = 0; j < ncol; ++j) {
      sum += vec(i, j);
    }
  }
  return sum;
}

// Function to evolve the state based on Game of Life rules
// [[Rcpp::export]]
NumericMatrix evolve(const NumericMatrix& state) {
  int xdim = state.nrow();
  int ydim = state.ncol();
  
  // Create a new matrix to hold the updated state
  NumericMatrix updatedState(xdim, ydim);
  
  for (int i = 0; i < xdim; ++i) {
    for (int j = 0; j < ydim; ++j) {
      NumericMatrix neighbors = get_neighbors(state, i, j);
      int check = bodycount(neighbors);
      // Game of Life rules to update the cell state
// #       # Any live cell with fewer than two live neighbors dies, as if by underpopulation.
// #       # Any live cell with two or three live neighbors lives on to the next generation.
// #       # Any live cell with more than three live neighbors dies, as if by overpopulation.
// #       # Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
      
      if (check < 2 && state(i, j)) {
        updatedState(i, j) = false;
      } else if (check > 3 && state(i, j)) {
        updatedState(i, j) = false;
      } else if (!state(i, j) && check == 3) {
        updatedState(i, j) = true;
      } else {
        updatedState(i, j) = state(i, j);
      }
    }
  }
  return updatedState;
}
DataFrame toDF(NumericMatrix y)
  {
  return DataFrame(y);
  }

//[[Rcpp::export]]
NumericMatrix DFtoNM(DataFrame x) {
  int xsize=x.size();
  NumericVector col=x(0); 
  NumericMatrix y(col.size(),xsize);
  for(int i=0;i<xsize;i++){
    y(_,i)=col;
    if(i<xsize-1){
      col=x(i+1);
    }
  }
  return y;
  }
RCPP_MODULE(GOL) {
  using namespace Rcpp;
  function("random_state" , &random_state );
  function("get_neighbors" , &get_neighbors );
  function("bodycount" , &bodycount );
  function("evolve" , &evolve );
  function("toDF" , &toDF);
  function("DFtoNM" , &DFtoNM);
}


