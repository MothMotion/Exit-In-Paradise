#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H



#include "matrix.h"



// Минимизирует, применяя алгоритм упрощения и
// после присоединяет оставшиеся так, чтобы
// сохранялась связь.
Matrix minimize(const Matrix& input_matrix);

// Упрощение. Базово минимизирует матрицу,
// соединяющая единственные ссылки с их значением.
Matrix simplify(const Matrix& input_matrix);



#endif // !FUNCTIONS_H
