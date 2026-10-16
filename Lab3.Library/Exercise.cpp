/**
 * @file Exercise.cpp
 * @brief Реализация Exercise. Подробные описания методов находятся в заголовочном файле.
 */
#include "Exercise.h"

miit::algebra::Exercise::Exercise(const Matrix<int>& matrix, const Generator& generator)
    : matrix_(matrix), generator_(generator) {}

const miit::algebra::Matrix<int>& miit::algebra::Exercise::matrix() const noexcept { return matrix_; }
