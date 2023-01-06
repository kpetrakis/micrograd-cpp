#include <iostream>
#include "engine.cpp"
#include <cstdlib>
#include <random>
#include <cassert>
#include <numeric> 

// help class to imitate random.uniform()
class RandomGenerator{
  public:
    RandomGenerator(){
      std::random_device rd;  // to seed the generator
      gen = std::mt19937(rd()); 
      dist = std::uniform_real_distribution<> (-1.0, 1.0);
    } 
    std::mt19937 gen; // random number generator
    std::uniform_real_distribution<> dist;

    // return a random number in [-1.0, 1.0] 
    float operator()(){
      return dist(gen);
    }
};

class Module{
  public:
    void zero_grad(){
      for (auto param : parameters()){
        param->_grad = 0;  
      } 
    }

    virtual std::vector<std::shared_ptr<Value>> parameters(){
      return {};
    }

};

class Neuron: public Module{
  public:
    Neuron(int nin, bool nonlin=true){
      RandomGenerator rng = RandomGenerator();
      // init weights with random uniform values in [-1, 1]
      for(int i=0; i<nin; i++){
        float weight_value = rng();
        _w.emplace_back(std::make_shared<Value>(weight_value));
      }
      _b = std::make_shared<Value>(0.0);
      _nonlin = nonlin; 
    }
    std::vector<std::shared_ptr<Value>> _w;
    std::shared_ptr<Value> _b;
    bool _nonlin;

    std::shared_ptr<Value> operator()(std::vector<std::shared_ptr<Value>> x){

      assert((void("w and x dimensions don't fit"),_w.size() == x.size())); 
      std::shared_ptr<Value> r = _w[0] * x[0];
      for (int i=1; i<_w.size(); i++){
        r = r + (_w[i] * x[i]); // don't have +=
      }
      auto act = r + _b;
      if (_nonlin) {
        return act->relu();
      }
      return act;

      // std::shared_ptr<Value> r = std::make_shared<Value>(
      //   std::inner_product(_w.begin(), _w.end(), x.begin(), 0));
      // std::shared_ptr<Value> sum = r + _b;
      // return sum;
    }    


    // all parameters = [weights + bias]
    std::vector<std::shared_ptr<Value>> parameters(){
      auto parameters = _w; // copy assignement??
      parameters.push_back(_b);
      return parameters;
    }
    // __repr__
    friend std::ostream& operator<<(std::ostream& os, const Neuron& n){
      std::string act = "Linear";
      if (n._nonlin) { act = "ReLU";}
      os << act << " Neuron(" << n._w.size() << ")"<< std::endl; 
      return os;
    }

};

int main(){

  std::shared_ptr<Value> a = std::make_shared<Value>(1.0);
  std::shared_ptr<Value> b = std::make_shared<Value>(3.0);
  std::shared_ptr<Value> c = std::make_shared<Value>(-3.0);
  std::shared_ptr<Value> d = std::make_shared<Value>(2.0);
  std::shared_ptr<Value> e = std::make_shared<Value>(1.0);
  std::vector<std::shared_ptr<Value>> x;
  x.push_back(a);
  x.push_back(b);
  x.push_back(c);
  x.push_back(d);
  x.push_back(e);

  Neuron neuron = Neuron(5);
  std::cout << neuron << std::endl;
  for (auto weight: neuron._w){
    std::cout << *weight << std::endl;
  }
  // for (auto param: neuron.parameters()){
  //   std::cout << *param << std::endl;
  // }

  std::shared_ptr<Value> res = neuron(x);
  std::cout << "result: " << *res << std::endl;

  return 0;
}