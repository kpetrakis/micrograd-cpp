#include <iostream>
#include "../engine.cpp"
#include <fstream>

void test_sanity_check(){

  std::shared_ptr<Value> x = std::make_shared<Value>(-4.0);  
	std::shared_ptr<Value> z, q, h, y;
	z = 2 * x + 2 + x;
	q = z->relu() + z * x;
	h = (z * z)->relu();
	y = h + q + q * x;
	y->backward();
	auto xmg = x;
	auto ymg = y;

	//std::cout << (*xmg).data() << std::endl;
	//std::cout << (*ymg).data() << std::endl;
	//std::cout << (*xmg).grad() << std::endl;
	
	std::ofstream file;
	file.open("test/sanity_check", std::ios::binary);
	float xmg_data = (*xmg).data();
	float ymg_data = (*ymg).data();
	float xmg_grad = (*xmg).grad();
	file.write(reinterpret_cast<const char*> (&xmg_data), sizeof(float)); 
	file.write(reinterpret_cast<const char*> (&ymg_data), sizeof(float)); 
	file.write(reinterpret_cast<const char*> (&xmg_grad), sizeof(float)); 

	file.close();
}

void test_more_ops(){
	
  std::shared_ptr<Value> a = std::make_shared<Value>(-4.0);
  std::shared_ptr<Value> b = std::make_shared<Value>(2.0);  
  std::shared_ptr<Value> c, d, e, f, g; 
  c = (a + b);
  d = a * b + b->pow(3);
  c = c + (c + 1);
  c = c + (1 + c + (-a));
  d = d + (d * 2 + (b + a)->relu());
  d = d + (3 * d + (b - a)->relu());
  e = c - d;
  f = e->pow(2);
  g = f / 2.0;
  g = g + (10.0 / f);
  g->backward();

	auto amg = a;
	auto bmg = b;
	auto gmg = g;

	//std::cout << *amg << std::endl;
	//std::cout << *bmg << std::endl;
	//std::cout << *gmg << std::endl;

	std::ofstream file;
	file.open("test/more_ops", std::ios::binary);
	float gmg_data = (*gmg).data();
	float amg_grad = (*amg).grad();
	float bmg_grad = (*bmg).grad();
	// std::cout << gmg_data << std::endl;
	// std::cout << amg_grad << std::endl;
	// std::cout << bmg_grad << std::endl;
	file.write(reinterpret_cast<const char*> (&gmg_data), sizeof(float)); 
	file.write(reinterpret_cast<const char*> (&amg_grad), sizeof(float)); 
	file.write(reinterpret_cast<const char*> (&bmg_grad), sizeof(float)); 

	file.close();
	
} 

int main(){
	
	test_sanity_check();

	test_more_ops();
	
	return 0;
}
