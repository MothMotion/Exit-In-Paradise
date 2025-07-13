#include "functions.h"
#include "matrix.h"
#include "config.h"

#include <cstdint>
#include <unordered_map>
#include <iostream>



Matrix minimize(const Matrix& in) {
  const Matrix simplified = simplify(in);
  Matrix result;
  for(uint32_t i=0; i<RESULT_MATRIX_SIZE; ++i)
    result.push_back(simplified[i]);

  for(uint32_t row_i=RESULT_MATRIX_SIZE, col_i; row_i<simplified.size(); ++row_i) {
    // Find column
    for(col_i=0; col_i<simplified[row_i].values.size() &&
        -simplified[row_i].values[col_i] != simplified[row_i].ticks[0];
      ++col_i);
    if(col_i == simplified[row_i].values.size()) {
      std::cerr << "Couldn't find column\n";
      return Matrix();
    }

    // Finding valid position
    uint32_t valid_row_pos = 0;
    for(; valid_row_pos<RESULT_MATRIX_SIZE &&
        !(result[(valid_row_pos+1)%RESULT_MATRIX_SIZE].values[col_i] == simplified[row_i].ticks[0] &&
        (result[valid_row_pos].values[col_i] == simplified[row_i].ticks[0] ||
        result[(valid_row_pos-1 + RESULT_MATRIX_SIZE)%RESULT_MATRIX_SIZE].values[col_i] == simplified[row_i].ticks[0]));
      ++valid_row_pos);
    if(valid_row_pos == RESULT_MATRIX_SIZE) {
      std::cerr << "Couldn't find optimal row position\n";
      return Matrix();
    }

    // Write data to matrix
    result[valid_row_pos].ticks.push_back(simplified[row_i].ticks[0]);
    result[valid_row_pos].values[col_i] = -simplified[row_i].ticks[0];
  }


  return result;
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
  for(Matrix::const_iterator i=in.begin(); i != in.end(); ++i) {
    // Exclude attached
    if(i->ticks[0] > RESULT_MATRIX_SIZE && repeats[i->ticks[0]] == 1)
      continue;

    for(std::deque<int16_t>::const_iterator j = i->values.begin(); j != i->values.end()-FUNCTION_Z_OUTPUT_SIZE; ++j) {
      if(*j == i->ticks[0] || repeats[*j] == 1) {
        temp.values.push_back(- *j);
        temp.ticks.push_back(*j);
      } else
        temp.values.push_back(*j);
    }
    result.push_back(temp);
    temp.clear();
  }
  
  return result;
}
