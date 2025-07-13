#pragma once
#ifndef MATRIX_H
#define MATRIX_H



#include <cstdint>
#include <deque>



class SimpleMatrix;

class Matrix {
public:
  typedef struct MatrixRowStruct {
    std::deque<uint16_t> ticks = {};
    std::deque<int16_t> values = {};

    // Clears row's deques w/o touching pointers
    inline void clear() {ticks.clear(); values.clear();}
  } Row;

  typedef std::deque<Row>::iterator iterator;
  typedef std::deque<Row>::const_iterator const_iterator;
private:
  std::deque<Row> _rows = {};

public:
  inline const bool empty() const {return _rows.empty();}

  inline void push_back(const std::deque<uint16_t>& ticks, const std::deque<int16_t>& values) {_rows.push_back({ticks, values});}
  inline void push_back(const Row& row_value) {_rows.push_back(row_value);};

  inline std::deque<Row>& rows() {return _rows;}

  const void print();

  inline const size_t size() const {return _rows.size();}

  inline iterator begin() {return _rows.begin();}
  inline iterator end() {return _rows.end();}
  inline const_iterator begin() const {return _rows.begin();}
  inline const_iterator end() const {return _rows.end();}

  inline operator bool() const {return !_rows.empty();}

  inline const Row& operator[](const uint32_t& pos) const {return _rows[pos];}
  inline Row& operator[](const uint32_t& pos) {return _rows[pos];}
};



#endif // !MATRIX_H
