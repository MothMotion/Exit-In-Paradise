#pragma once
#ifndef MATRIX_H
#define MATRIX_H



#include <cstdint>
#include <deque>



class SimpleMatrix;

class Matrix {
public:
  typedef struct MatrixCellStruct {
    std::deque<uint16_t> ticks = {};
    int16_t* values = nullptr;
  } Cell;

  typedef std::deque<Cell>::iterator iterator;
private:
  std::deque<Cell> _rows = {};
  uint32_t _val_size = 0;

public:
  // Преобразовать простую матрицу.
  Matrix(SimpleMatrix& sm);
  Matrix(const uint32_t& val_size);
  ~Matrix();

  inline const bool empty() const {return _rows.empty();}

  void push(const std::deque<uint16_t>& ticks, const int16_t* const values);

  inline std::deque<Cell>& rows() {return _rows;}
  inline const uint32_t& valSize() const {return _val_size;}

  const void print();

  inline std::deque<Cell>::iterator begin() {return _rows.begin();}
  inline std::deque<Cell>::iterator end() {return _rows.end();}

  inline operator bool() const {return !_rows.empty();}
};



#endif // !MATRIX_H
