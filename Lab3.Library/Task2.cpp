#include "Task2.h"

miit::algebra::Matrix<int> miit::algebra::Task2::solve() const {
    Matrix<int> result;
    if (matrix_.columns() == 0) return result;
    result = Matrix<int>(0, matrix_.columns());
    const Matrix<int>::Row zeroRow(matrix_.columns(), 0);
    for (std::size_t i = 0; i < matrix_.rows(); ++i) {
        if (matrix_[i][0] % 3 == 0) result.insertRow(result.rows(), zeroRow);
        result.insertRow(result.rows(), matrix_[i]);
    }
    return result;
}
