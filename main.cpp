#include <iostream>
#include "engine.cpp"
#include <set>
#include <vector>

int main(){
  
  // Karpathy example
  std::shared_ptr<Value> a = std::make_shared<Value>(-4.0);
  std::shared_ptr<Value> b = std::make_shared<Value>(2.0);  
  std::shared_ptr<Value> c, d, e, f, g; 
  c = (a + b);
  d = a * b + b->pow(3);
  c = c + (c + 1);
  c = c + (1 + c + (-a));
  d = d + (d * 2 + (b + a)->relu());
  d = d + (d * 3 + (b - a)->relu());
  e = c - d;
  f = e->pow(2);
  g = f / 2.0;
  g = g + (10.0 / f);
  std::cout << *g << std::endl;
  g->backward();
  std::cout << "a.grad: " << (*b).grad() << std::endl;


  // std::shared_ptr<Value> v = std::make_shared<Value>(3.0);
  // std::shared_ptr<Value> y = std::make_shared<Value>(2.0);
  // // std::shared_ptr<Value> r = v->relu();
  // // std::shared_ptr<Value> r = v->pow(y);
  // // std::shared_ptr<Value> r = 2*(2-v) + 2*(-y) + 2;
  // // std::shared_ptr<Value> r = v->pow(2);
  // std::shared_ptr<Value> r = (v/y);
  // auto g = r + (y - v)->relu();

  // // std::shared_ptr<Value> v = std::make_shared<Value>(-1.0);
  // // std::cout << *v;
  // // std::cout << *r;
  // // std::cout << "r grad: " << (*r).grad() << std::endl;
  // // r->build_topo();
  // g->backward();
  // std::cout << "g grad: "<< (*g).grad() << std::endl;
  // std::cout << "r grad: "<< (*r).grad() << std::endl;
  // std::cout << "v grad: "<< (*v).grad() << std::endl;
  // std::cout << "y grad: "<< (*y).grad() << std::endl;

  return 0;
}
