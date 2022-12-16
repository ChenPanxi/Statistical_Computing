#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector concatenate(NumericVector A, NumericVector B) {
  NumericVector result;

  for (int i = 0; i < A.size(); i++) {
    result.push_back(A[i]);
  }
  for (int j = 0; j < B.size(); j ++){
   result.push_back(B[j]);
  }
  return result;
}

// [[Rcpp::export]]
NumericVector genseq(int from, int to, int by = 1) {
  NumericVector result;
  for (int i = from; i <= to; i += by) {
    result.push_back(i);
  }
  return result;
}


// [[Rcpp::export]]
List simulator_cpp(int nshape=5, int npoint=30, int nnoise=100, double p_min=-10, double p_max=10, double coef_min=-5, double coef_max=5, NumericVector radius=5, double noise_sd=0.1, double slope_sd=1,  std::string shape_type="line", bool line_noise=true, bool noise=true){
  
  NumericVector x_coords_shape;
  NumericVector y_coords_shape;
  
  NumericVector x_center;
  NumericVector y_center;
  NumericVector r_circle;
  
  if(radius.length()==1){
    NumericVector temp(2);
    temp[0]=radius[0];
    temp[1]=radius[0];
    radius=temp;
  }
  
  //Loop over number of shapes
  for(int i=0; i < nshape; i++){
    
    //Create a vector of error values
    NumericVector e;
    if(line_noise==true){
      e = rnorm(npoint, 0, noise_sd);
    }
    else if (line_noise==false){
      e = NumericVector(npoint, 0.0);
    }
    if (shape_type == "line") {
      NumericVector x = runif(npoint, p_min, p_max);
      NumericVector m = rnorm(1, 0, slope_sd);
      NumericVector b = runif(1, p_min, p_max);
      NumericVector y = m[0]*x + b[0] + e;
      x_coords_shape = concatenate(x_coords_shape, x);
      y_coords_shape = concatenate(y_coords_shape, y);
      // x_coords_shape.push_back(x);
      // y_coords_shape.push_back(y);
    } 
    else if (shape_type == "circle") {
      
      NumericVector s = runif(npoint, 0, 2*M_PI);
      NumericVector r = runif(1, radius[0], radius[1]);
      NumericVector cx = runif(1, coef_min, coef_max);
      NumericVector cy = runif(1, coef_min, coef_max);
      
      NumericVector sinx = r[0]*sin(s) + cx[0];
      NumericVector cosy = r[0]*cos(s) + cy[0];
      x_coords_shape = concatenate(x_coords_shape, sinx);
      y_coords_shape = concatenate(y_coords_shape, cosy);
      // x_coords_shape.push_back(sinx);
      // y_coords_shape.push_back(cosy);
      
      x_center.push_back(cx[0]);
      y_center.push_back(cy[0]);
      r_circle.push_back(r[0]);
    }
  }
  
  NumericVector x_coords_noise;
  NumericVector y_coords_noise;
  
  if(noise == false || nnoise <= 0){
    // noises = data.frame()
  }
  else {
    NumericVector random_x = runif(nnoise, p_min, p_max);
    NumericVector random_y = runif(nnoise, p_min, p_max);
    x_coords_noise = concatenate(x_coords_noise, random_x);
    y_coords_noise = concatenate(y_coords_noise, random_y);
  }
  
  NumericVector x_coords = concatenate(x_coords_shape, x_coords_noise);
  NumericVector y_coords = concatenate(y_coords_shape, y_coords_noise);
  
  DataFrame coord = DataFrame::create(Named("x")=x_coords, Named("y")=y_coords);
  
  DataFrame coord_shape = DataFrame::create(Named("x")=x_coords_shape, Named("y")=y_coords_shape);
  DataFrame coord_center = DataFrame::create(Named("x")=x_center, Named("y")=y_center);

  return List::create(Named("coord")=coord, Named("radius")=r_circle, Named("center")=coord_center, Named("coord_shape")=coord_shape);
}


// [[Rcpp::export]]
NumericMatrix hough_trans_cpp(NumericVector points, 
                 NumericVector points_hs, 
                 LogicalVector points_shape = false, 
                 int steps = 30, 
                 std::string shape_type = "line", 
                 int radius = 5,
                 double point_size = 1, 
                 double point_width = 2, 
                 int point_shape = 1, 
                 std::string point_color = "cornflowerblue",
                 bool show = true, 
                 bool show_simulation = false) {
  
  if (points_shape.size() != 0) {
    show_simulation = TRUE;
  }
  
  if (points_shape.size() == 0 && show_simulation == TRUE) {
    Rcpp::Rcout << "Shape data is missing." << std::endl;
  }
  
  NumericMatrix params;
  if (shape_type == "circle") {
    
    NumericVector x_center = points_hs[Range(0, points_hs.size()/2 - 1)];
    NumericVector y_center = points_hs[Range(points_hs.size()/2, points_hs.size() - 1)];
    
    NumericVector theta = genseq(0, 2 * M_PI, M_PI/steps);
    NumericVector xx = radius * sin(theta) + x_center;
    NumericVector yy = radius * cos(theta) + y_center;
    NumericVector radiusCol (radius, theta.length());
    // params = cbind(xx, yy, radius);
    params = NumericMatrix(theta.length(), 3);
    params.column(0) = xx;
    params.column(1) = yy;
    params.column(2) =radiusCol;
      
    
  } else if (shape_type == "line") {
    
    NumericVector x_coords = points_hs[Range(0, points_hs.size()/2 - 1)];
    NumericVector y_coords = points_hs[Range(points_hs.size()/2, points_hs.size() - 1)];
    
    NumericVector slope = -cos(x_coords) / sin(x_coords);
    NumericVector intercept = y_coords / sin(x_coords);
    
    params = NumericMatrix(slope.length(), 2);
    params.column(0) = slope;
    params.column(1) = intercept;
    
    // List params = List::create(Named("slope") = slope, Named("intercept") = intercept);
  }

  return params;
}
