#pragma once
#ifndef MATRIX_H
#define MATRIX_H



#include <cstdint>
#include <deque>



class SimpleMatrix;

class Matrix {
public:
  // Структура ряда.
  typedef struct MatrixRowStruct {
    // Набор тиков.
    std::deque<uint16_t> ticks = {};
    // Значения, соответствуют 000 001 011 111 101 100 110 010
    // Работает на самом деле с любой последовательности, т.к. абстрактна.
    //
    // В представленной предметной области представляет из себя ссылки на тики.
    std::deque<int16_t> values = {};

    // Очищает структуру, не трогает указатели.
    inline void clear() {ticks.clear(); values.clear();}
  } Row;

  // Именования для итераторов.
  typedef std::deque<Row>::iterator iterator;
  typedef std::deque<Row>::const_iterator const_iterator;
private:
  std::deque<Row> _rows = {};

public:
  inline const bool empty() const {return _rows.empty();}

  // Добавить новый ряд в конец.
  inline void push_back(const std::deque<uint16_t>& ticks, const std::deque<int16_t>& values) {_rows.push_back({ticks, values});}
  // Добавить существующий ряд в конец.
  inline void push_back(const Row& row_value) {_rows.push_back(row_value);};

  // Тривиальный аксессор.
  inline std::deque<Row>& rows() {return _rows;}

  // Выводит матрицу в консооль по рядам. Тики разделяются от данных при помощи вертикальной черты "|"
  const void print();

  inline const size_t size() const {return _rows.size();}

  // Работа с итераторами.
  inline iterator begin() {return _rows.begin();}
  inline iterator end() {return _rows.end();}
  inline const_iterator begin() const {return _rows.begin();}
  inline const_iterator end() const {return _rows.end();}

  inline operator bool() const {return !_rows.empty();}

  // Операторы доступа.
  inline const Row& operator[](const uint32_t& pos) const {return _rows[pos];}
  inline Row& operator[](const uint32_t& pos) {return _rows[pos];}
};



#endif // !MATRIX_H
