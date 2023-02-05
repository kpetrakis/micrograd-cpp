#include <iostream>
#include "read.cpp"
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include "../nn.cpp"

/**
 * Implement a micrograd demo, showing an MLP learning on make_moons dataset
*/

typedef std::vector<std::vector<std::shared_ptr<Value>>> vector2d;
typedef std::tuple<vector2d, std::vector<std::shared_ptr<Value>>> dataset_t; //can't use arrays cause it seg faults!

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
  vector2d scores;  // each layer returns a vector!
  for (auto input: inputs){
    scores.emplace_back(model(input));
  }
  return scores;
}

static std::tuple<std::shared_ptr<Value>,float> loss(size_t batch_size,
                                              MLP& model,
                                              vector2d& x, 
                                              const std::vector<std::shared_ptr<Value>> y,
                                              const std::vector<std::shared_ptr<Value>>& parameters){
  /**
   * implement the backward pass through the network..
  */
  //implement batching
  std::vector<int> indexes(x.size()); // use list??
  vector2d Xb;
  std::vector<std::shared_ptr<Value>> yb;
  std::iota(indexes.begin(), indexes.end(), 0); // indexes = {0,1,2,3...99}
  std::random_shuffle(indexes.begin(), indexes.end()); // shuffle indexes
  // create batch
  for (int i=0; i<batch_size;i++){
    yb.emplace_back(y[indexes[i]]);
    Xb.emplace_back(x[indexes[i]]);
  }
  vector2d scores = forward(model, Xb);
  std::vector<std::shared_ptr<Value>> losses;
  for (int i=0; i<yb.size(); ++i){
    // svm "max-margin" loss
    losses.emplace_back((std::make_shared<Value>(1.0) + (-yb[i] * scores[i][0]))->relu());
  }
  std::shared_ptr<Value> data_loss = std::accumulate(losses.begin(), losses.end(), std::make_shared<Value>(0.0));
  data_loss = data_loss / losses.size();//std::make_shared<Value>(losses.size()); 
  // L2 reguralization
  auto alpha = std::make_shared<Value>(1e-4);
  auto square_sum = std::inner_product(parameters.begin(), parameters.end(),
    parameters.begin(), std::make_shared<Value>(0.0));
  auto reg_loss = alpha * square_sum;
  auto total_loss = data_loss + reg_loss;

  // also get accuracy
  float accuracy = 0.0;
  for (int i=0; i<yb.size();i++){
    accuracy += ((yb[i]->data()>0)==(scores[i][0]->data()>0));
  }
  accuracy /= yb.size();
  return std::make_tuple(total_loss, accuracy);
}

int main(){
  // dataset = read_data("dataset/data", "dataset/labels");
  // x = std::get<0>(dataset);
  // y = std::get<1>(dataset);
  // or
  // auto [x, y] = read_data("dataset/data", "dataset/labels");
  auto [x, y] = make_dataset("dataset/data", "dataset/labels");
  MLP model = MLP(2,{16,16,1});
  size_t batch_size=16;
  size_t steps = 100; // those are not epochs....I make approximately steps/(x.shape[0]/batch_size) passes through the whole dataset 
  // float learning_rate = 1e-2;
  for (size_t k=0; k<steps; k++){
    auto [total_loss, acc] = loss(batch_size, model, x, y, model.parameters());
    // backward
    model.zero_grad();
    
    total_loss->backward();
    // update (sgd)
    float learning_rate = 1.0 - 0.9*k/steps;
    for (auto p : model.parameters()){
      p->_data -= learning_rate * p->grad();
    }
    if (k % 1 == 0){
      std::cout << "Step: " << k << " loss: " << total_loss->data() 
      << ", accuracy: " << acc*100 << "%"<< std::endl;
      // ", learning_rate: " << learning_rate << std::endl;
    }
  }
  return 0;
}