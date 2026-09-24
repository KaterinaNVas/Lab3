#pragma once
#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra {
class Exercise {
protected:
    Matrix<int> matrix_;
    Generator& generator_;
public:
    Exercise(std::size_t rows, std::size_t columns, Generator& generator);
    Exercise(const Matrix<int>& matrix, Generator& generator);
    virtual ~Exercise() = default;
    virtual Matrix<int> solve() const = 0;
    const Matrix<int>& matrix() const noexcept;
};
}
