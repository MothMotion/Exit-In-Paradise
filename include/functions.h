#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H



#include "matrix.h"
#include "simple_matrix.h"

#include <forward_list>
#include <cstdint>



Matrix minimize(SimpleMatrix& inp_matrix);

Matrix simplify(SimpleMatrix& inp_matrix);



#endif // !FUNCTIONS_H
