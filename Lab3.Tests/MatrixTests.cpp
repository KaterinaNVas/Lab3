/**
 * @file MatrixTests.cpp
 * @brief Проверки шаблонной матрицы и её операций.
 */
#include "../Lab3.Library/Matrix.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

using miit::algebra::Matrix;

static_assert(std::is_same_v<
    decltype(std::declval<Matrix<int>&>()[0]), std::vector<int>&>);
static_assert(std::is_same_v<
    decltype(std::declval<const Matrix<int>&>()[0]), const std::vector<int>&>);

/**
 * @brief Проверки шаблонной матрицы и её операций.
 * @details Целые значения сравниваются через std::equal_to; размеры — через
 * std::equal_to<std::size_t>, элементы и результаты генераторов — через std::equal_to<int>.
 * @note Проверки используют assert и должны выполняться без определения NDEBUG.
 */
void runMatrixTests() {
    const Matrix<double> fractional{{1.5, 2.5}, {3.5, 4.5}};
    assert(fractional[1][0] == 3.5);

    Matrix<int> original{{1, 2}, {3, 4}};
    const Matrix<int> moved(std::move(original));
    assert(std::equal_to<std::size_t>{}(original.rows(), 0) && std::equal_to<std::size_t>{}(original.columns(), 0));
    assert(std::equal_to<int>{}(moved[1][1], 4));

    Matrix<int> noColumns(2, 0);
    assert(noColumns[0].empty());
    noColumns.insertRow(1, {});
    assert(std::equal_to<std::size_t>{}(noColumns.rows(), 3));

    Matrix<int> matrix{
        {1, 2, 3},
        {4, 5, 6}
    };

    assert(std::equal_to<std::size_t>{}(matrix.rows(), 2));
    assert(std::equal_to<std::size_t>{}(matrix.columns(), 3));

    assert(std::equal_to<int>{}(matrix[0][0], 1));
    assert(std::equal_to<int>{}(matrix[1][2], 6));

    assert(
        matrix.toString() ==
        "1 2 3\n4 5 6"
    );

    Matrix<int> copy = matrix;

    assert(copy.equals(matrix));

    copy << 1;

    const Matrix<int> shiftedLeft{
        {2, 3, 1},
        {5, 6, 4}
    };

    assert(copy.equals(shiftedLeft));

    copy >> 1;

    assert(copy.equals(matrix));

    matrix.insertRow(1, {7, 8, 9});

    assert(std::equal_to<std::size_t>{}(matrix.rows(), 3));
    assert(std::equal_to<int>{}(matrix[1][0], 7));
    assert(std::equal_to<int>{}(matrix[1][1], 8));
    assert(std::equal_to<int>{}(matrix[1][2], 9));

    bool exceptionCaught = false;

    try {
        matrix.insertRow(1, {1, 2});
    } catch (const std::invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    std::cout << "Тесты Matrix пройдены.\n";
}