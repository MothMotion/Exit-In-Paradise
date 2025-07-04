#pragma once
#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H



#include <cstdint>



class Matrix;

class SimpleMatrix {
private:
  uint16_t** _data = nullptr;

protected:
  uint32_t _size_h = 0;
  uint32_t _size_w = 0;

public:
  SimpleMatrix(const uint32_t& size_h, const uint32_t& size_w);
  SimpleMatrix(Matrix& m);
  ~SimpleMatrix();

  inline const bool empty() const {return _data == nullptr;}

  // Возвращает указанную строку матрицы.
  inline uint16_t* operator[](const uint32_t& size_h) {return _data[size_h];}

  inline operator bool() const {return _data;}
};



#endif // !SIMPLE_MATRIX_H
