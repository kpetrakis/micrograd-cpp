#include <iostream>
#include "read.cpp"

/**
 * Implement a micrograd demo, showing an MLP learning the make_moons dataset
*/

int main(){

  // std::array<std::array<float,n_features>, n_samples> x ;
  // std::array<float, n_samples> y;
  std::tuple<
    std::array<std::array<float,n_features>, n_samples>, 
    std::array<float, n_samples>> dataset;

  auto [x, y] = read_data("dataset/data", "dataset/labels");

  x = std::get<0>(dataset);
  y = std::get<1>(dataset);

  // std::cout << y.size();
  return 0;
}