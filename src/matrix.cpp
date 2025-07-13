#include "matrix.h"

#include <cstdint>
#include <iostream>



const void Matrix::print() {
  for(Matrix::iterator i = begin(); i != end(); ++i) {
    // Print ticks
    for(std::deque<uint16_t>::iterator j=i->ticks.begin(); j != i->ticks.end(); ++j)
      std::cout << *j << " ";
    std::cout << "\t|\t";

    // Print values
    for(std::deque<int16_t>::iterator j=i->values.begin(); j != i->values.end(); ++j)
      std::cout << *j << "\t";

    std::cout << "\n";
  }
}
