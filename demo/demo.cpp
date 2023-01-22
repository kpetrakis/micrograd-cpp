#include <iostream>
#include "read.cpp"
#include <vector>
#include <array>
#include "../nn.cpp"

/**
 * Implement a micrograd demo, showing an MLP learning the make_moons dataset
*/

typedef std::tuple<
  std::vector<std::vector<std::shared_ptr<Value>>>, 
  std::vector<std::shared_ptr<Value>>> dataset_t; //can't use arrays cause it seg faults!

typedef std::vector<std::vector<std::shared_ptr<Value>>> vector2d;

dataset_t make_dataset(std::string data_file, std::string label_file){
  /**
   * data_file: the path to the file containing the make_moons data
   * label_file : the path to the file containing the make_moons labels
   * returns a tuple with the whole dataset in the form (x, y). e.g ([1.05,-0.93], -1)
  */
  // x_data and y_data are the arrays containing the float numbers
  auto [x_data, y_data] = read_data(data_file, label_file); 

  std::vector<std::vector<std::shared_ptr<Value>>> x;
  std::vector<std::shared_ptr<Value>> y;

  for (int i=0; i<x_data.size();i++){
    y.emplace_back(std::make_shared<Value>(y_data[i]));
    x.emplace_back(std::vector<std::shared_ptr<Value>>{std::make_shared<Value>(x_data[i][0]), std::make_shared<Value>(x_data[i][1])});
    }

  return std::make_tuple(x, y);
} 


vector2d forward(MLP& model, vector2d& inputs){
  /**
   * implements the forward pass through network.
  */
  vector2d outputs; // keep dimensionality of the input - torch like
  for (auto input: inputs){
    outputs.emplace_back(model(input));
  }

  return outputs;
}

void loss(){
  /**
   * implement the backward pass through the network..
  */
}

int main(){

  // std::array<std::array<float,n_features>, n_samples> x ;
  // std::array<float, n_samples> y;
  std::tuple<
    std::array<std::array<float,n_features>, n_samples>, 
    std::array<float, n_samples>> dataset;

  // auto [x, y] = read_data("dataset/data", "dataset/labels");
  // dataset = read_data("dataset/data", "dataset/labels");
  // x = std::get<0>(dataset);
  // y = std::get<1>(dataset);
  auto [x, y] = make_dataset("dataset/data", "dataset/labels");
  MLP model = MLP(2,{16,16,1});
  auto outputs = forward(model, x);
  for (auto item_vector: outputs){
    for (auto item : item_vector){
      std::cout << *item << std::endl;
    }
  }
  // std::cout << model << std::endl;
  // std::cout << *(x[1][0]) << std::endl;

  // std::cout << y.size() << std::endl;
  // std::cout << *y[1] << std::endl;
  return 0;
}