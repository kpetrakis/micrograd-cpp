#include <iostream>
#include "engine.cpp"
#include <cstdlib>
#include <random>
#include <cassert>
#include <numeric> 
#include <sstream>

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
    Neuron(size_t nin, bool nonlin=true){
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
    
    //__call__
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


    // neuron parameters = [weights + bias]
    std::vector<std::shared_ptr<Value>> parameters(){
    //  std::vector<std::shared_ptr<Value>> 
      auto parameters = _w; // copy assignement??
      parameters.push_back(_b);
      return parameters;
    }
    // __repr__
    friend std::ostream& operator<<(std::ostream& os, const Neuron& n){
      std::string act = "Linear";
      if (n._nonlin) { act = "ReLU";}
      os << act << " Neuron(" << n._w.size() << ")" << std::endl; 
      return os;
    }
};

class Layer :public Module{
  /**
   * nin : the num of inputs for each neuron
   * nout : the number of neurons in the Layer
  */
  public:
    Layer(size_t nin, size_t nout, bool nonlin=true){
      for (int i=0; i<nout; i++){
        _neurons.emplace_back(nin, nonlin);
      }
    }
    std::vector<Neuron> _neurons;
    
    //__call__
    std::vector<std::shared_ptr<Value>> operator()(std::vector<std::shared_ptr<Value>> x){
      // i just check the first neuron because all of the will have the same nin
      assert((void("Dimension don't fit"), _neurons[0]._w.size()==x.size()));

      std::vector<std::shared_ptr<Value>> out;
      for (auto neuron: _neurons){
        out.emplace_back(neuron(x));
      }
      return out;
    }

    // layer parameters
    std::vector<std::shared_ptr<Value>> parameters(){
      std::vector<std::shared_ptr<Value>> layer_params; // all layer params
      for (auto neuron: _neurons){
        for (auto neuron_param: neuron.parameters()){
          layer_params.push_back(neuron_param);
        }
      }
      return layer_params;
    }
    //__repr__
    friend std::ostream& operator<<(std::ostream& os, const Layer& l){
      std::string str = "Layer of [";
      for (auto& n: l._neurons){
        std::stringstream ss;
        ss << n;
        str += ss.str() + ", ";
      }
      str = str.substr(0, str.size() - 2);
      str += "]";
      os << str <<std::endl;
      return os;
    }

};

class MLP: public Module{
  /**
   * nin : dimensionality of input
   * nouts : list with number of neurons per layer
  */
  public:
    MLP(size_t nin, std::vector<size_t> nouts){
      auto sz = nouts;
      sz.insert(sz.begin(), nin); // insert nin at the beginning
      for (size_t i=0; i<nouts.size(); i++){
        _layers.emplace_back(sz[i], sz[i+1], i!= (nouts.size() - 1));
      }
    }
    std::vector<Layer> _layers;

    //__call__
    std::vector<std::shared_ptr<Value>> operator()(std::vector<std::shared_ptr<Value>> x){
      for (auto layer: _layers){
        x = layer(x); // forward pass
      }
      return x; // the output of the MLP
    }

    // MLP parameters
    std::vector<std::shared_ptr<Value>> parameters(){
    std::vector<std::shared_ptr<Value>> mlp_params;
    for (auto layer: _layers){
      for (auto param : layer.parameters()){
        mlp_params.push_back(param);
        }
      }
      return mlp_params;
    }

    //__repr__
    friend std::ostream& operator<<(std::ostream& os, const MLP& mlp){
      std::string str = "MLP of [";
      for (auto& layer: mlp._layers){
        std::stringstream ss;
        ss << layer;
        str += ss.str() + ", ";
      }
      str = str.substr(0, str.size() - 2);
      str += "]";
      os << str;
      return os;
    }

};

int main(){

  std::shared_ptr<Value> a = std::make_shared<Value>(1.0);
  std::shared_ptr<Value> b = std::make_shared<Value>(-3.0);
  std::shared_ptr<Value> c = std::make_shared<Value>(1.0);
  std::shared_ptr<Value> d = std::make_shared<Value>(2.0);
  std::shared_ptr<Value> e = std::make_shared<Value>(5.0);
  std::vector<std::shared_ptr<Value>> x;
  x.push_back(a);
  x.push_back(b);
  x.push_back(c);
  x.push_back(d);
  x.push_back(e);

  // Neuron neuron = Neuron(5);
  // std::cout << neuron << std::endl;
  // for (auto weight: neuron._w){
  //   std::cout << *weight << std::endl;
  // }
  // for (auto param: neuron.parameters()){
  //   std::cout << *param << std::endl;
  // }

  // std::shared_ptr<Value> res = neuron(x);
  // std::cout << "result: " << *res << std::endl;

  // Layer l = Layer(5,10);
  // std::cout << l << std::endl;
  std::vector<std::shared_ptr<Value>> res;
  // res = l(x);
  // for (auto neuron_res: res){
  //   std::cout << *neuron_res << std::endl;
  // }
  // for (auto param: l.parameters()){
  //   std::cout << *param <<std::endl;
  // }
  // for (auto n: l._neurons){
  //   std::cout << " Neuron params:"<< std::endl;
  //   for (auto param : n.parameters()){
  //   }
  //     std::cout << *param<< std::endl;
  // }

  // an MLP with 2 hidden layers 16 neuros each and 1 output neuron
  MLP mlp = MLP(5, {16,16,1});
  std::cout << mlp << std::endl;
  for (auto param: mlp.parameters()){
    std::cout << *param <<std::endl;
  }
  res = mlp(x); 
  std::cout << "MLP out: " <<*res[0] << std::endl; // 1 outpu neuron
  
  return 0;
}