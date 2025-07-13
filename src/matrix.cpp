#include "matrix.h"

#include <cstdint>
#include <iostream>



const void Matrix::print() {
  for(Matrix::iterator i = begin(); i != end(); ++i) {
    // Выводим тики.
    for(std::deque<uint16_t>::iterator j=i->ticks.begin(); j != i->ticks.end(); ++j)
      std::cout << *j << " ";
    std::cout << "\t|\t";

    // Выводим значения(ссылки)
    for(std::deque<int16_t>::iterator j=i->values.begin(); j != i->values.end(); ++j)
      std::cout << *j << "\t";

    std::cout << "\n";
  }
}
