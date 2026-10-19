/**
 * @file Task2.cpp
 * @brief Реализация Task2. Подробные описания методов находятся в заголовочном файле.
 */
#include "Task2.h"
#include <vector>

miit::algebra::Task2::Task2(
    Matrix<int>& matrix,
    const Generator& generator
) : Exercise(matrix, generator) {}

miit::algebra::Matrix<int> miit::algebra::Task2::solve() const {
    if (matrix_.columns() == 0)
        return Matrix<int>{};

    Matrix<int> result(0, matrix_.columns());

    const std::vector<int> zeroRow(matrix_.columns(), 0);

    for (std::size_t i = 0; i < matrix_.rows(); ++i) {
        if (matrix_[i][0] % 3 == 0)
            result.insertRow(result.rows(), zeroRow);

        std::vector<int> row;
        row.reserve(matrix_.columns());

        for (std::size_t j = 0; j < matrix_.columns(); ++j)
            row.push_back(matrix_[i][j]);

        result.insertRow(result.rows(), row);
    }

    return result;
}