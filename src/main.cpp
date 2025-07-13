#include "functions.h"
#include "matrix.h"

#include <cstdint>
#include <iostream>
#include <cstdlib>



int main (int argc, char *argv[]) {
  if(argc <= 3) {
    std::cerr << "Invalid format: [size_h] [size_w] [matrix_0_0] [matrix_0_1] ...\n";
    return -1;
  }

  uint32_t size_h = std::atoi(argv[1]);
  uint32_t size_w = std::atoi(argv[2]);

  if(argc != 3 + size_h * size_w) {
    std::cout << "size_h: " << size_h << " size_w: " << size_w << "\n";
    std::cout << "argc: " << argc << "\t size_h*size_w: " << size_h * size_w << "\n";
    std::cerr << "Invalid amount of args for current size_h and size_w\n";
    return -2;
  }

  Matrix input_matrix;
  Matrix::Row temp;

  std::cout << "Filling input matrix\n";

  for(uint32_t i=0; i<size_h; ++i) {
    temp.ticks.push_back( (uint16_t)std::atoi(argv[3 + i*size_h]) );
    for(uint32_t j=1; j<size_w; ++j)
      temp.values.push_back( std::atoi(argv[3 + i*size_h + j]) );
    input_matrix.push_back(temp);
    temp.clear();
  }

  std::cout << "Input matrix filled\n";
  input_matrix.print();


  std::cout << "Minimizing\n";
  Matrix result = minimize(input_matrix);
  std::cout << "Minimizing done\n";

  result.print();


  return 0;
}
