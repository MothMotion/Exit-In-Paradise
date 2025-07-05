#include "functions.h"

#include <unordered_map>
#include <unordered_set>



Matrix minimize(SimpleMatrix& inp_matrix) {
  Matrix pre_matrix = simplify(inp_matrix);
  Matrix result(inp_matrix.sizeW()-3);

  return pre_matrix;
}

Matrix simplify(SimpleMatrix& inp_matrix) {
  Matrix result(inp_matrix.sizeW()-3);
  std::unordered_map<uint16_t, uint8_t> count_map;
  for(uint32_t i=1; i<5; ++i)
    count_map[i] = 2;

  // Fill up count map with values
  for(uint32_t i=0; i<inp_matrix.sizeH(); ++i)
    for(uint32_t j=1; j<inp_matrix.sizeW()-2; ++j)
      if(count_map[inp_matrix[i][j]])
        ++count_map[inp_matrix[i][j]];
      else
       count_map[inp_matrix[i][j]] = 1;

  // Simplify matrix
  std::unordered_set<uint16_t> exluded;
  // Cell parameters;
  std::deque<uint16_t> temp_ticks;
  int16_t* temp_values = new int16_t[result.valSize()];

  for(uint32_t i=0; i<inp_matrix.sizeH(); ++i) {
    // if we already imported this tick in group.
    if(exluded.find(inp_matrix[i][0]) != exluded.end())
      continue; 

    for(uint32_t j=1; j<inp_matrix.sizeH()-2; ++j) {
      temp_values[j-1] = inp_matrix[i][j];
      if(count_map[inp_matrix[i][j]] == 2 || inp_matrix[i][j] == inp_matrix[i][0]) {
        temp_values[j-1] *= -1;
        temp_ticks.push_back(inp_matrix[i][j]);
        exluded.insert(inp_matrix[i][j]);
      }
    }
    result.push(temp_ticks, temp_values);
    temp_ticks.clear();
    temp_values = new int16_t[result.valSize()];
  }
  delete[] temp_values;

  return result;
}
