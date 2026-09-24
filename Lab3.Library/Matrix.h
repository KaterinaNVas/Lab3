#pragma once
#include "Generator.h"
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace miit::algebra {

template<typename T>
class Matrix {
public:
    using Row = std::vector<T>;

    Matrix() = default;
    Matrix(std::size_t rows, std::size_t columns, const T& value = T{})
        : data_(rows, Row(columns, value)), columns_(columns) {}
    Matrix(std::initializer_list<Row> rows) : data_(rows) {
        columns_ = data_.empty() ? 0 : data_.front().size();
        for (const auto& row : data_)
            if (row.size() != columns_) throw std::invalid_argument("Rows have different sizes");
    }
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) noexcept = default;
    ~Matrix() = default;

    std::size_t rows() const noexcept { return data_.size(); }
    std::size_t columns() const noexcept { return columns_; }
    bool empty() const noexcept { return data_.empty() || columns_ == 0; }

    Row& operator[](std::size_t row) { return data_.at(row); }
    const Row& operator[](std::size_t row) const { return data_.at(row); }
    T& at(std::size_t row, std::size_t column) { return data_.at(row).at(column); }
    const T& at(std::size_t row, std::size_t column) const { return data_.at(row).at(column); }

    void fill(Generator& generator) {
        for (auto& row : data_)
            for (auto& value : row) value = static_cast<T>(generator.generate());
    }

    void insertRow(std::size_t position, const Row& row) {
        if (position > rows()) throw std::out_of_range("Invalid row position");
        if (row.size() != columns_) throw std::invalid_argument("Invalid row size");
        data_.insert(data_.begin() + static_cast<std::ptrdiff_t>(position), row);
    }

    std::string toString() const {
        std::ostringstream out;
        for (std::size_t i = 0; i < rows(); ++i) {
            for (std::size_t j = 0; j < columns_; ++j) {
                if (j != 0) out << ' ';
                out << data_[i][j];
            }
            if (i + 1 != rows()) out << '\n';
        }
        return out.str();
    }

    Matrix& operator<<(std::size_t positions) {
        if (columns_ == 0) return *this;
        positions %= columns_;
        for (auto& row : data_)
            std::rotate(row.begin(), row.begin() + static_cast<std::ptrdiff_t>(positions), row.end());
        return *this;
    }

    Matrix& operator>>(std::size_t positions) {
        if (columns_ == 0) return *this;
        positions %= columns_;
        for (auto& row : data_)
            std::rotate(row.begin(), row.end() - static_cast<std::ptrdiff_t>(positions), row.end());
        return *this;
    }

    bool operator==(const Matrix& other) const noexcept {
        return columns_ == other.columns_ && data_ == other.data_;
    }

private:
    std::vector<Row> data_;
    std::size_t columns_{};
};
}
