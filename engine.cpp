#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <memory>

// capture shared_ptr in lambda-> BAD!!
// https://floating.io/2017/07/lambda-shared_ptr-memory-leak/

// Nmzw oloi oi operators prepei na epistrefoun shared_ptr<Value> wste
// na borw na parw shared_from_this() sto vector-set children
// stis relu kai pow pou exoun children ton idio komvo.

// stores a single scalar value and its gradient
class Value: public std::enable_shared_from_this<Value> {
  public:
    Value (float data)
      : _data(data), _grad(0.0f), _backward{[]() {}} {
        // std::cout << "constructor 1, data: " << _data << std::endl;
      }
    Value(float data, std::set<std::shared_ptr<Value>> _children, std::string _op="")
      : _data(data), _grad(0.0f), _prev(_children), _op(_op)  {
        // std::cout << "cunstructor 2, data: " << _data << std::endl;
      }
    // static std::set<std::shared_ptr<Value>> visited;
    bool visited = false;
    float _data, _grad;
    std::set<std::shared_ptr<Value>> _prev;
    std::string _op;
    // typedef std::function<void()> f_type;
    // f_type _backward;
    std::function<void()> _backward;

    float data() const{
      return _data;
    }
    float grad() const {
      return _grad;
    }
    //__relu__ 
    std::shared_ptr<Value> relu(){
      auto out = std::make_shared<Value>(std::max(0.0f, _data),
       std::set<std::shared_ptr<Value>>{shared_from_this()}, _op="relu"); 
      
      out->_backward = [out, self = shared_from_this()](){
        self->_grad += (out->data() > 0) * out->grad();
      };
      return out;
    }

    // __pow__
    std::shared_ptr<Value> pow(std::shared_ptr<Value> other){
      auto out = std::make_shared<Value>(std::pow(_data, other->data()),
        std::set<std::shared_ptr<Value>>{shared_from_this()}, _op="pow");
        
      out->_backward = [out, self=shared_from_this(), other](){
        self->_grad += other->data() * std::pow(self->data(), other->data()-1) * out->_grad; 
      };

      return out;
    }
    //__pow__
    std::shared_ptr<Value> pow(float exp){
      auto self = shared_from_this();
      auto other = std::make_shared<Value>(exp);
      return self->pow(other);
    }
    
    std::vector<std::shared_ptr<Value>> build_topo(){
      // kathe antikeimeno pou kalei tn methodo thelw na prosthetei 
      // sto idio vector, gi auto einai static-> na to kanw member?
      static std::vector<std::shared_ptr<Value>> topo{};
      auto v = shared_from_this(); // at first the node that called .backward()
      if (!v->visited){
        //std::cout << "not visited, node: " << v->data() << std::endl;
        v->visited = true; // mark visited
        for(auto child : v->_prev) {
          child->build_topo();
        }
        //std::cout << "pushing node " << v->data() << " in topo "<< std::endl;
        topo.push_back(v);
      }else{
        //std::cout << "visited, node: " << v->data() <<  std::endl;
      }
      return topo;
    }    

    void backward(){
      // self is the node that called .backward()
      auto self = shared_from_this();
      auto topo = self->build_topo();
      self->_grad = 1;
      // std::cout << "topo size:" << topo.size() << std::endl;
      for (auto it = topo.rbegin(); it!=topo.rend(); ++it){
        // std::cout << "grad in backward data("<< (*it)->data()<< "): " << (*it)->grad() << std::endl;
        (*it)->_backward();
      }
      // std::for_each(topo.rbegin(), topo.rend(), 
      // [](auto node){node->_backward();});
    }

    // __repr__ 
    friend std::ostream& operator<<(std::ostream& os, const Value& v){
      os << "Value(data="<< v.data() << ", grad=" << v.grad() << ")"<< std::endl; 
      return os;
    }
    // operator < needed just for sets
    bool operator<(const Value& other) const{
      if (this->data() < other.data()){
        return true;
      }else{
        return false;
      }
    }
};

//__add__ Value + Value
std::shared_ptr<Value> operator+(std::shared_ptr<Value> self, std::shared_ptr<Value> other){
  auto out = std::make_shared<Value>(self->data() + other->data(),
    std::set<std::shared_ptr<Value>>{self, other}, "+");

  out->_backward = [self, other, out](){
    self->_grad += out->grad();
    other->_grad += out->grad();
  };
  
  return out;
}
//__add__ Value + float
std::shared_ptr<Value> operator+(std::shared_ptr<Value> self, float num){
  auto other = std::make_shared<Value>(num);
  auto out = self + other;
  return out;
}
//__add__ float + Value
std::shared_ptr<Value> operator+(float num, std::shared_ptr<Value> self){
  auto other = std::make_shared<Value>(num);
  auto out = self + other;
  return out;
}

//__mul__ Value * Value
std::shared_ptr<Value> operator*(std::shared_ptr<Value> self, std::shared_ptr<Value> other){
  auto out = std::make_shared<Value>(self->data() * other->data(),
    std::set<std::shared_ptr<Value>>{self, other}, "*");

  out->_backward = [self, other, out](){
    self->_grad += other->data() * out->grad();
    other->_grad += self->data() * out->grad();
  };
  return out;
}
//__mul__ Value * float
std::shared_ptr<Value> operator*(std::shared_ptr<Value> self, float num){ 
  auto other = std::make_shared<Value>(num);
  auto out = self * other;
  return out;
}
//__mul__ float * Value 
std::shared_ptr<Value> operator*(float num, std::shared_ptr<Value> self){
  auto other = std::make_shared<Value>(num);
  auto out = self * other;
  return out;
}

//__neg__
std::shared_ptr<Value> operator-(std::shared_ptr<Value> self){
  return self * (-1.0); //std::make_shared<Value>(-1.0);
}

//__sub__ Value - Value
std::shared_ptr<Value> operator-(std::shared_ptr<Value> self, std::shared_ptr<Value> other){
  return self + (-other); 
}
//__sub__ Value - float
std::shared_ptr<Value> operator-(std::shared_ptr<Value> self, float num){
  auto other = std::make_shared<Value>(num);
  return self + (-other); 
}
//__sub__ float - Value
std::shared_ptr<Value> operator-(float num, std::shared_ptr<Value> self){
  auto other = std::make_shared<Value>(num);
  return other + (-self); 
}

//__truediv__ Value / Value
std::shared_ptr<Value> operator/(std::shared_ptr<Value> self, std::shared_ptr<Value> other){
  return self * (other->pow(-1.0));
}
//__truediv__ Value / float
std::shared_ptr<Value> operator/(std::shared_ptr<Value> self, float num){
  auto other = std::make_shared<Value>(num);
  return self / other;
}
//__truediv__ float / Value
std::shared_ptr<Value> operator/(float num, std::shared_ptr<Value> self){
  auto other = std::make_shared<Value>(num);
  return other / self;
}
