#include "Task1.h"
#include <algorithm>

miit::algebra::Matrix<int> miit::algebra::Task1::solve() const {
    Matrix<int> result = matrix_;
    for (std::size_t i = 0; i < result.rows(); ++i) {
        if (result.columns() == 0) continue;
        auto& row = result[i];
        const auto maximum = std::max_element(row.begin(), row.end());
        *maximum = 0;
    }
    return result;
}
