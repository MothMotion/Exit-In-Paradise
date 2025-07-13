#include "functions.h"
#include "matrix.h"
#include "config.h"

#include <cstdint>
#include <unordered_map>



Matrix minimize(const Matrix& in) {
  return simplify(in);
}

Matrix simplify(const Matrix& in) {
  Matrix result;

  std::unordered_map<uint16_t, uint16_t> repeats;

  for(Matrix::const_iterator i=in.begin(); i != in.begin()+RESULT_MATRIX_SIZE; ++i) {
    for(std::deque<int16_t>::const_iterator j = i->values.begin(); j != i->values.end()-FUNCTION_Z_OUTPUT_SIZE; ++j) {
      if(repeats[*j])
        ++repeats[*j];
      else
        repeats[*j] = 1;
    }
  }

  Matrix::Row temp;
  for(Matrix::const_iterator i=in.begin(); i != in.begin()+RESULT_MATRIX_SIZE; ++i) {
    temp.ticks = i->ticks; 
    for(std::deque<int16_t>::const_iterator j = i->values.begin(); j != i->values.end()-FUNCTION_Z_OUTPUT_SIZE; ++j) {
      if(*j == i->ticks[0] || repeats[*j] == 1)
        temp.values.push_back(- *j);
      else
        temp.values.push_back(*j);
    }
    result.push_back(temp);
    temp.clear();
  }
  
  return result;
}
