#include "matrix.h"
#include "simple_matrix.h"

#include <cstdint>
#include <cstring>
#include <iostream>



Matrix::Matrix(const uint32_t& val_size) {
  _val_size = val_size;
}

Matrix::Matrix(SimpleMatrix& sm) {
  _val_size = sm.sizeW() - 3;

  Matrix::Cell temp;
  for(uint32_t i=0; i < sm.sizeH(); ++i) {
    // clear temp
    temp.ticks.clear();
    temp.values = new int16_t[sm.sizeW()];

    // fill temp
    temp.ticks.push_back(sm[i][0]);
    for(uint32_t j=1; j<sm.sizeW()-2; ++j)
      temp.values[j-1] = sm[i][j];
    // push new row
    _rows.push_back(temp);
  }
}

Matrix::~Matrix() {
  for(Matrix::iterator i = begin(); i != end(); ++i) {
    i->ticks.clear();
    delete i->values;
  }
}

void Matrix::push(const std::deque<uint16_t>& ticks, const int16_t* const values) {
  Matrix::Cell temp;
  temp.ticks = ticks;
  temp.values = new int16_t[_val_size];

  std::memcpy(temp.values, values, _val_size * sizeof(int16_t));

  _rows.push_back(temp);
}

const void Matrix::print() {
  for(Matrix::iterator i = begin(); i != end(); ++i) {
    // Print ticks
    for(std::deque<uint16_t>::iterator j=i->ticks.begin(); j != i->ticks.end(); ++j)
      std::cout << *j << " ";
    std::cout << "\t|\t";

    // Print values
    for(uint32_t j=0; j<_val_size; ++j)
      std::cout << i->values[j] << "\t";

    std::cout << "\n";
  }
}
