#include "simple_matrix.h"
#include "matrix.h"

#include <cstdint>
#include <iostream>
#include <iterator>



SimpleMatrix::SimpleMatrix(const uint32_t& size_h, const uint32_t& size_w) {
  if(_data != nullptr) {
    for(uint32_t i=0; i<_size_h; ++i)
      delete[] _data[i];
    delete[] _data;
  }

  _data = new uint16_t*[size_h];
  for(uint32_t i=0; i<size_h; ++i)
    _data[i] = new uint16_t[size_w];

  _size_h = size_h;
  _size_w = size_w;
}

SimpleMatrix::SimpleMatrix(Matrix& m) {
  if(m || _data)
    return;

  _size_h = std::distance(m.begin(), m.end());
  _size_w = 0;
  for(Matrix::iterator i=m.begin(); i != m.end(); ++i) {
    uint32_t temp = std::distance(i->ticks.begin(), i->ticks.end());
    if(temp > _size_w)
      _size_w = temp;
  }

  _data = new uint16_t*[_size_h];
  
  uint32_t j = 0;
  for(Matrix::iterator i=m.begin(); i != m.end(); ++i, ++j) {
    _data[j] = new uint16_t[_size_w + m.valSize()];

    // Fill up ticks
    uint16_t temp_size = _size_w;
    for(std::deque<uint16_t>::iterator k = i->ticks.begin(); k != i->ticks.end(); ++k, --temp_size)
      _data[j][_size_w - temp_size] = *k;
    while(temp_size != 1)
      _data[j][_size_w - temp_size] = 0;

    // Fill up values
    for(uint32_t k=0; k<m.valSize(); ++k)
      _data[j][_size_w + k] = i->values[k];
  }

  _size_w += m.valSize();
}

SimpleMatrix::~SimpleMatrix() {
  for(uint32_t i=0; i<_size_h; ++i) {
    delete[] _data[i];
    _data[i] = nullptr;
  }
  delete[] _data;
}

const void SimpleMatrix::print() const {
  for(uint32_t i=0; i<_size_h; ++i) {
    for(uint32_t j=0; j<_size_w; ++j)
      std::cout << _data[i][j] << " ";
    std::cout << "\n";
  }
}
