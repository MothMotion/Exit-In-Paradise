#include "functions.h"
#include "matrix.h"
#include "config.h"

#include <cstdint>
#include <unordered_map>
#include <iostream>



Matrix minimize(const Matrix& in) {
  // Для избежания проблем, будем использовать константную
  // упрощённую матрицу.
  const Matrix simplified = simplify(in);
  Matrix result;
  // Копируем строки, до которых уменьшаем
  for(uint32_t i=0; i<RESULT_MATRIX_SIZE; ++i)
    result.push_back(simplified[i]);

  // Проходим по строчкам, расположенным дальше от указанных для минимизации.
  for(uint32_t row_i=RESULT_MATRIX_SIZE, col_i; row_i<simplified.size(); ++row_i) {
    // Ищем колонку, которую будем минимизировать.
    // Колонка ищется такая, которая будет соответствовать
    // тику.
    for(col_i=0; col_i<simplified[row_i].values.size() &&
        -simplified[row_i].values[col_i] != simplified[row_i].ticks[0];
      ++col_i);
    // Если не смогли найти колонку - то это ошибка.
    if(col_i == simplified[row_i].values.size()) {
      std::cerr << "Couldn't find column\n";
      return Matrix();
    }

    // Ищем позицию, в которую можно подставить найденный тик.
    uint32_t valid_row_pos = 0;
    for(; valid_row_pos<RESULT_MATRIX_SIZE && // Ищем только в пределах минимизированных тиков.
        !(result[(valid_row_pos+1)%RESULT_MATRIX_SIZE].values[col_i] == simplified[row_i].ticks[0] && // Останавливаемся если
        (result[valid_row_pos].values[col_i] == simplified[row_i].ticks[0] || // Нашли такую позицию, где следующий и ИЛИ предыдущий
        result[(valid_row_pos-1 + RESULT_MATRIX_SIZE)%RESULT_MATRIX_SIZE].values[col_i] == simplified[row_i].ticks[0])); // ИЛИ текущий
      ++valid_row_pos); // Совпадает с тиком, который мы будем присоединять.
    // Если такая позиция не была найдена в пределах минимизированных тиков - выдаём ошибку.
    if(valid_row_pos == RESULT_MATRIX_SIZE) {
      std::cerr << "Couldn't find optimal row position\n";
      return Matrix();
    }

    // Добавляем тик к минизированной строке.
    result[valid_row_pos].ticks.push_back(simplified[row_i].ticks[0]);
    result[valid_row_pos].values[col_i] = -simplified[row_i].ticks[0];
  }


  return result;
}

Matrix simplify(const Matrix& in) {
  Matrix result;

  // Будем искать повторы
  std::unordered_map<uint16_t, uint16_t> repeats;

  // Повторы ищем в пределах целей для минимизированных строк
  for(Matrix::const_iterator i=in.begin(); i != in.begin()+RESULT_MATRIX_SIZE; ++i) {
    for(std::deque<int16_t>::const_iterator j = i->values.begin(); j != i->values.end()-FUNCTION_Z_OUTPUT_SIZE; ++j) {
      if(repeats[*j])
        ++repeats[*j];
      else
        repeats[*j] = 1;
    }
  }

  Matrix::Row temp;
  // Проходим по матрице и соединяем единственные ссылки с значением, если возможно.
  for(Matrix::const_iterator i=in.begin(); i != in.end(); ++i) {
    // Исключаем уже присоединённые.
    if(i->ticks[0] > RESULT_MATRIX_SIZE && repeats[i->ticks[0]] == 1)
      continue;

    // Проходим по строке и строим результат.
    for(std::deque<int16_t>::const_iterator j = i->values.begin(); j != i->values.end()-FUNCTION_Z_OUTPUT_SIZE; ++j) {
      // Выделяем устройчивые позиции и присоединяем единственные ссылочные позиции.
      if(*j == i->ticks[0] || repeats[*j] == 1) {
        temp.values.push_back(- *j);
        temp.ticks.push_back(*j);
      } else
        temp.values.push_back(*j);
    }
    result.push_back(temp);
    temp.clear();
  }
  
  // Получили упрощённую матрицу с выделенными устройчивыми позициями.
  return result;
}
