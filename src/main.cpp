#include "functions.h"
#include "simple_matrix.h"
#include "matrix.h"

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

  SimpleMatrix inp_matrix(size_h, size_w);

  for(uint32_t i=0; i<size_h; ++i)
    for(uint32_t j=0; j<size_w; ++j)
      inp_matrix[i][j] = std::atoi(argv[3 + i*size_h + j]);

  Matrix result = minimize(inp_matrix);

  result.print();


  return 0;
}
