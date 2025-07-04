#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H



#include <forward_list>
#include <cstdint>



typedef struct MatrixCell {
  std::forward_list<uint16_t> ticks;
  std::forward_list<int16_t> values;
} Cell;
typedef std::forward_list<MatrixCell> Matrix;



Matrix minimize(const uint16_t* const inp_matrix[]);

Matrix simplify(const uint16_t* const inp_matrix[]);



#endif // !FUNCTIONS_H
