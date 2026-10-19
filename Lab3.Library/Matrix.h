/**
 * @file Matrix.h
 * @brief Объявление и реализация шаблонной матрицы Matrix<T>.
 */
#pragma once

#include "Generator.h"
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

namespace miit::algebra {

/**
 * @brief Матрица с хранением каждой строки в отдельном векторе.
 * @tparam T Тип элементов матрицы.
 */
template<typename T>
class Matrix {
public:
    /**
     * @brief Создаёт пустую матрицу размером 0 × 0.
     */
    Matrix() = default;

    /**
     * @brief Создаёт матрицу с элементами, инициализированными значением T{}.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @throws std::length_error Если количество элементов превышает допустимый размер.
     */
    Matrix(const std::size_t rows, const std::size_t columns)
        : data_(makeData(rows, columns)), columns_(columns), rows_(rows) {
    }

    /**
     * @brief Создаёт матрицу и заполняет её генератором.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @param generator Генератор значений элементов.
     * @throws std::length_error Если количество элементов превышает допустимый размер.
     */
    Matrix(const std::size_t rows,
           const std::size_t columns,
           const Generator& generator)
        : Matrix(rows, columns) {
        fill(generator);
    }

    /**
     * @brief Создаёт матрицу из списка строк одинаковой длины.
     * @param list Строки матрицы.
     * @throws std::invalid_argument Если длины строк различаются.
     * @throws std::length_error Если матрица слишком велика.
     */
    Matrix(const std::initializer_list<std::vector<T>> list)
        : columns_(list.size() == 0 ? 0 : list.begin()->size()),
          rows_(list.size()) {
        for (const auto& row : list) {
            if (row.size() != columns_)
                throw std::invalid_argument("Rows have different sizes");
        }

        checkedSize(rows_, columns_);
        data_.assign(list.begin(), list.end());
    }

    /**
     * @brief Создаёт независимую копию матрицы.
     * @param other Копируемая матрица.
     */
    Matrix(const Matrix& other) = default;
    /**
     * @brief Перемещает данные матрицы, обнуляя размеры исходного объекта.
     * @param other Исходная матрица.
     */
    Matrix(Matrix&& other) noexcept
        : data_(std::move(other.data_)),
          columns_(std::exchange(other.columns_, 0)),
          rows_(std::exchange(other.rows_, 0)) {
        other.data_.clear();
    }
    /**
     * @brief Копирует матрицу при присваивании.
     * @param other Копируемая матрица.
     * @return Ссылка на текущую матрицу.
     */
    Matrix& operator=(const Matrix& other) = default;
    /**
     * @brief Перемещает матрицу при присваивании.
     * @param other Исходная матрица.
     * @return Ссылка на текущую матрицу.
     */
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            columns_ = std::exchange(other.columns_, 0);
            rows_ = std::exchange(other.rows_, 0);
            other.data_.clear();
        }
        return *this;
    }
    /**
     * @brief Освобождает ресурсы матрицы.
     */
    ~Matrix() = default;

    /**
     * @brief Возвращает количество строк.
     * @return Количество строк матрицы.
     */
    std::size_t rows() const noexcept {
        return rows_;
    }

    /**
     * @brief Возвращает количество столбцов.
     * @return Количество столбцов матрицы.
     */
    std::size_t columns() const noexcept {
        return columns_;
    }

    /**
     * @brief Проверяет, отсутствуют ли элементы матрицы.
     * @return true, если хотя бы один размер равен нулю.
     */
    bool empty() const noexcept {
        return rows_ == 0 || columns_ == 0;
    }

    /**
     * @brief Возвращает изменяемую строку матрицы.
     * @param row Индекс строки, начиная с нуля.
     * @return Ссылка на строку.
     * @warning Изменять длину возвращённой строки нельзя: это нарушает размеры матрицы.
     * @throws std::out_of_range Если индекс строки недопустим.
     * @note Индекс столбца при следующем [] не проверяется.
     */
    std::vector<T>& operator[](const std::size_t row) {
        if (row >= data_.size())
            throw std::out_of_range("Invalid row index");
        return data_[row];
    }

    /**
     * @brief Возвращает строку матрицы только для чтения.
     * @param row Индекс строки, начиная с нуля.
     * @return Константная ссылка на строку.
     * @throws std::out_of_range Если индекс строки недопустим.
     * @note Индекс столбца при следующем [] не проверяется.
     */
    const std::vector<T>& operator[](const std::size_t row) const {
        if (row >= data_.size())
            throw std::out_of_range("Invalid row index");
        return data_[row];
    }

    /**
     * @brief Заполняет элементы матрицы значениями генератора по строкам.
     * @param generator Генератор значений.
     * @note Исключения генератора передаются вызывающему коду; матрица может быть заполнена частично.
     */
    void fill(const Generator& generator) {
        for (auto& row : data_)
            for (auto& value : row)
                value = static_cast<T>(generator.generate());
    }

    /**
     * @brief Вставляет строку перед указанной позицией.
     * @param position Позиция вставки от нуля до rows() включительно.
     * @param row Вставляемая строка.
     * @throws std::out_of_range Если позиция недопустима.
     * @throws std::invalid_argument Если длина строки не равна columns().
     * @throws std::length_error Если добавление строки превышает допустимый размер.
     * @throws std::bad_alloc Если не удалось выделить память.
     */
    void insertRow(const std::size_t position,
                   const std::vector<T>& row) {
        if (position > rows_)
            throw std::out_of_range("Invalid row position");

        if (row.size() != columns_)
            throw std::invalid_argument("Invalid row size");

        if (rows_ == data_.max_size())
            throw std::length_error("Matrix is too large");
        checkedSize(rows_ + 1, columns_);
        data_.insert(
            data_.begin() + static_cast<std::ptrdiff_t>(position),
            row
        );

        ++rows_;
    }

    /**
     * @brief Формирует текстовое представление матрицы.
     * @return Строка с пробелами между элементами и переносами между строками.
     */
    std::string toString() const {
        std::ostringstream out;

        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < columns_; ++j) {
                if (j != 0)
                    out << ' ';

                out << (*this)[i][j];
            }

            if (i + 1 != rows_)
                out << '\n';
        }

        return out.str();
    }

    /**
     * @brief Циклически сдвигает элементы каждой строки влево.
     * @param positions Количество позиций сдвига.
     * @return Ссылка на текущую матрицу.
     */
    Matrix& operator<<(const std::size_t positions) {
        if (columns_ == 0)
            return *this;

        const std::size_t shift = positions % columns_;

        for (auto& row : data_) {
            std::rotate(row.begin(),
                        row.begin() + static_cast<std::ptrdiff_t>(shift),
                        row.end());
        }

        return *this;
    }

    /**
     * @brief Циклически сдвигает элементы каждой строки вправо.
     * @param positions Количество позиций сдвига.
     * @return Ссылка на текущую матрицу.
     */
    Matrix& operator>>(const std::size_t positions) {
        if (columns_ == 0)
            return *this;

        const std::size_t shift = positions % columns_;

        for (auto& row : data_) {
            std::rotate(row.begin(),
                        row.end() - static_cast<std::ptrdiff_t>(shift),
                        row.end());
        }

        return *this;
    }

    /**
     * @brief Сравнивает размеры и элементы двух матриц.
     * @param other Матрица для сравнения.
     * @return true, если размеры и все элементы совпадают.
     */
    bool equals(const Matrix& other) const {
        return rows_ == other.rows_
            && columns_ == other.columns_
            && data_ == other.data_;
    }

private:
    /**
     * @brief Проверяет размеры и создаёт хранилище строк.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @return Вектор строк с элементами, инициализированными значением T{}.
     * @throws std::length_error Если размеры превышают допустимые.
     * @throws std::bad_alloc Если не удалось выделить память.
     */
    static std::vector<std::vector<T>> makeData(
        const std::size_t rows, const std::size_t columns) {
        checkedSize(rows, columns);
        std::vector<std::vector<T>> data(rows);
        for (auto& row : data)
            row.resize(columns);
        return data;
    }

    /**
     * @brief Проверяет допустимость размеров и вычисляет количество элементов.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @return Произведение количества строк и столбцов.
     * @throws std::length_error Если размер превышает допустимый.
     */
    static std::size_t checkedSize(const std::size_t rows,
                                   const std::size_t columns) {
        if (rows > std::vector<std::vector<T>>{}.max_size()
            || columns > std::vector<T>{}.max_size())
            throw std::length_error("Matrix is too large");

        if (columns != 0
            && rows > std::vector<T>{}.max_size() / columns)
            throw std::length_error("Matrix is too large");

        return rows * columns;
    }

    /**
     * @brief Строки матрицы, каждая из которых хранится в отдельном векторе.
     */
    std::vector<std::vector<T>> data_;
    /**
     * @brief Количество столбцов матрицы.
     */
    std::size_t columns_{};
    /**
     * @brief Количество строк матрицы.
     */
    std::size_t rows_{};
};

}
