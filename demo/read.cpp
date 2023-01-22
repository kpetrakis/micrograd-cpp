#include <iostream>
#include "../engine.cpp"
#include <fstream>
#include <tuple>

/**
 * Na ta diavasw se ena vector<ValuePtr> apo Vectors me 2 stoixeia to kathe ena
*/
const uint n_samples = 100;
const uint n_features = 2;

std::tuple<
  std::array<std::array<float,n_features>, n_samples>, 
  std::array<float, n_samples>> read_data(std::string data_file, std::string label_file){
    /**
     * data_file: the path to the file containing the make_moons data
     * label_file : the path to the file containing the make_moons labels
     * It reads those 2 files on 2 arrays x and y respectively and returns a tuple with them.
    */

  float * x_memblock, *y_memblock;
  std::array<std::array <float, n_features>, n_samples> x;
  std::array<float, n_samples> y;
  std::ifstream x_file(data_file, std::ios::binary | std::ios::ate);
  std::ifstream y_file(label_file, std::ios::binary | std::ios::ate);
  // file.open("data", std::ios::ate);
  
  if (x_file.is_open() & y_file.is_open()){
    auto size = x_file.tellg();
    x_memblock = new float [size/sizeof(float)];
    y_memblock = new float [size/sizeof(float)];
    x_file.seekg(0, std::ios::beg);
    y_file.seekg(0, std::ios::beg);
    x_file.read(reinterpret_cast <char *> (&x_memblock[0]), size*sizeof(float));
    y_file.read(reinterpret_cast <char *> (&y_memblock[0]), size*sizeof(float));
    for (int i=0; i< x.size(); i++){
      y[i] = y_memblock[i];
      for (int j=0; j<x[0].size(); j++){
        x[i][j] = x_memblock[i*2 + j];
      }
    }
    for (int i=0; i< x.size(); i++){
      for (int j=0; j<x[0].size(); j++){
        // std::cout << x[i][j] << " ";
      }
      // std::cout << std::endl;
    }
    for (int i=0; i< y.size(); i++){
        // std::cout <<y[i] << std::endl;
    }

    x_file.close();
    y_file.close();

    delete[] x_memblock;
    delete[] y_memblock;
  }else{
    std::cerr << "Some file didn't open" << std::endl;
  }
    return std::make_tuple(x, y);
}
