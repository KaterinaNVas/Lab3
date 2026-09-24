#include "Exercise.h"

miit::algebra::Exercise::Exercise(std::size_t rows, std::size_t columns, Generator& generator)
    : matrix_(rows, columns), generator_(generator) { matrix_.fill(generator_); }

miit::algebra::Exercise::Exercise(const Matrix<int>& matrix, Generator& generator)
    : matrix_(matrix), generator_(generator) {}

const miit::algebra::Matrix<int>& miit::algebra::Exercise::matrix() const noexcept { return matrix_; }
