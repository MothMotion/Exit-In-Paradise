#pragma once
#ifndef MATRIX_H
#define MATRIX_H



#include <cstdint>
#include <forward_list>



class SimpleMatrix;

class Matrix {
public:
  typedef struct MatrixCellStruct {
    std::forward_list<uint16_t> ticks;
    int16_t values[];
  } Cell;

  typedef std::forward_list<Cell>::iterator iterator;
private:
  std::forward_list<Cell> _rows;
  uint32_t _val_size = 0;

public:
  // Преобразовать простую матрицу.
  Matrix(SimpleMatrix& sm);

  inline const bool empty() const {return _rows.empty();}

  inline std::forward_list<Cell>& rows() {return _rows;}
  inline const uint32_t valSize() const {return _val_size;}

  inline std::forward_list<Cell>::iterator begin() {return _rows.begin();}
  inline std::forward_list<Cell>::iterator end() {return _rows.end();}

  inline operator bool() const {return !_rows.empty();}
};



#endif // !MATRIX_H
