#include <iostream>
#include "engine.cpp"
#include <set>
#include <vector>

int main(){
  
  std::shared_ptr<Value> v = std::make_shared<Value>(3.0);
  std::shared_ptr<Value> y = std::make_shared<Value>(2.0);
  // std::shared_ptr<Value> r = v->relu();
  // std::shared_ptr<Value> r = v->pow(y);
  std::shared_ptr<Value> r = 2*(2-v) + 2*(-y) + 2;
  // std::shared_ptr<Value> r = v->pow(2);
  // std::shared_ptr<Value> r = v/y;

  // std::shared_ptr<Value> v = std::make_shared<Value>(-1.0);
  // std::cout << *v;
  // std::cout << *r;
  // std::cout << "r grad: " << (*r).grad() << std::endl;
  // r->build_topo();
  r->backward();
  std::cout << "r grad: "<< (*r).grad() << std::endl;
  std::cout << "v grad: "<< (*v).grad() << std::endl;
  std::cout << "y grad: "<< (*y).grad() << std::endl;

  return 0;
}
