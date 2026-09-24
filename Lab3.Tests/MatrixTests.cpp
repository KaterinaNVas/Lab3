#include "../Lab3.Library/Matrix.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using miit::algebra::Matrix;

void runMatrixTests() {
    Matrix<int> matrix{
        {1, 2, 3},
        {4, 5, 6}
    };

    assert(matrix.rows() == 2);
    assert(matrix.columns() == 3);

    assert(matrix[0][0] == 1);
    assert(matrix[1][2] == 6);

    assert(
        matrix.toString() ==
        "1 2 3\n4 5 6"
    );

    Matrix<int> copy = matrix;

    assert(copy == matrix);

    copy << 1;

    const Matrix<int> shiftedLeft{
        {2, 3, 1},
        {5, 6, 4}
    };

    assert(copy == shiftedLeft);

    copy >> 1;

    assert(copy == matrix);

    matrix.insertRow(1, {7, 8, 9});

    assert(matrix.rows() == 3);
    assert(matrix[1][0] == 7);
    assert(matrix[1][1] == 8);
    assert(matrix[1][2] == 9);

    bool exceptionCaught = false;

    try {
        matrix.insertRow(1, {1, 2});
    } catch (const std::invalid_argument&) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    std::cout << "Тесты Matrix пройдены.\n";
}