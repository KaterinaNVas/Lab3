/**
 * @file Matrix.h
 * @brief Объявления Matrix.
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
 * @brief Матрица с хранением элементов в одном векторе.
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
        : data_(checkedSize(rows, columns)), columns_(columns), rows_(rows) {
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
    Matrix(std::initializer_list<std::vector<T>> list)
        : columns_(list.size() == 0 ? 0 : list.begin()->size()),
          rows_(list.size()) {
        for (const auto& row : list) {
            if (row.size() != columns_)
                throw std::invalid_argument("Rows have different sizes");
        }

        data_.reserve(checkedSize(rows_, columns_));

        for (const auto& row : list)
            data_.insert(data_.end(), row.begin(), row.end());
    }

    /**
     * @brief Создаёт копию матрицы.
     */
    Matrix(const Matrix&) = default;
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
     * @return Ссылка на текущую матрицу.
     */
    Matrix& operator=(const Matrix&) = default;
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
        /**
         * @brief Количество строк матрицы.
         */
        return rows_;
    }

    /**
     * @brief Возвращает количество столбцов.
     * @return Количество столбцов матрицы.
     */
    std::size_t columns() const noexcept {
        /**
         * @brief Количество столбцов матрицы.
         */
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
     * @brief Возвращает указатель на начало строки.
     * @param row Индекс строки, начиная с нуля.
     * @return Указатель на начало строки.
     * @throws std::out_of_range Если индекс строки недопустим.
     * @note Индекс столбца при следующем [] не проверяется.
     */
    T* operator[](const std::size_t row) {
        if (row >= rows_)
            throw std::out_of_range("Invalid row index");

        if (columns_ == 0)
            return data_.data();

        return data_.data() + row * columns_;
    }

    /**
     * @brief Возвращает указатель на начало строки только для чтения.
     * @param row Индекс строки, начиная с нуля.
     * @return Указатель на начало строки.
     * @throws std::out_of_range Если индекс строки недопустим.
     * @note Индекс столбца при следующем [] не проверяется.
     */
    const T* operator[](const std::size_t row) const {
        if (row >= rows_)
            throw std::out_of_range("Invalid row index");

        if (columns_ == 0)
            return data_.data();

        return data_.data() + row * columns_;
    }

    /**
     * @brief Предоставляет изменяемый доступ к элементу с проверкой индексов.
     * @param row Индекс строки, начиная с нуля.
     * @param column Индекс столбца, начиная с нуля.
     * @return Ссылка на элемент матрицы.
     * @throws std::out_of_range Если любой индекс недопустим.
     */
    T& at(const std::size_t row, const std::size_t column) {
        if (row >= rows_ || column >= columns_)
            throw std::out_of_range("Invalid matrix index");

        return data_.at(row * columns_ + column);
    }

    /**
     * @brief Предоставляет доступ только для чтения к элементу с проверкой индексов.
     * @param row Индекс строки, начиная с нуля.
     * @param column Индекс столбца, начиная с нуля.
     * @return Ссылка на элемент матрицы.
     * @throws std::out_of_range Если любой индекс недопустим.
     */
    const T& at(const std::size_t row,
                const std::size_t column) const {
        if (row >= rows_ || column >= columns_)
            throw std::out_of_range("Invalid matrix index");

        return data_.at(row * columns_ + column);
    }

    /**
     * @brief Заполняет элементы матрицы значениями генератора по строкам.
     * @param generator Генератор значений.
     */
    void fill(const Generator& generator) {
        for (auto& value : data_)
            value = static_cast<T>(generator.generate());
    }

    /**
     * @brief Вставляет строку перед указанной позицией.
     * @param position Позиция вставки от нуля до rows() включительно.
     * @param row Вставляемая строка.
     * @throws std::out_of_range Если позиция недопустима.
     * @throws std::invalid_argument Если длина строки не равна columns().
     */
    void insertRow(const std::size_t position,
                   const std::vector<T>& row) {
        if (position > rows_)
            throw std::out_of_range("Invalid row position");

        if (row.size() != columns_)
            throw std::invalid_argument("Invalid row size");

        data_.insert(
            data_.begin()
                + static_cast<std::ptrdiff_t>(position * columns_),
            row.begin(),
            row.end()
        );

        /**
         * @brief Количество строк матрицы.
         */
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

                out << at(i, j);
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

        /**
         * @brief Количество столбцов матрицы.
         */
        const std::size_t shift = positions % columns_;

        for (std::size_t i = 0; i < rows_; ++i) {
            const auto first = data_.begin()
                + static_cast<std::ptrdiff_t>(i * columns_);
            const auto last = first
                + static_cast<std::ptrdiff_t>(columns_);

            std::rotate(
                first,
                first + static_cast<std::ptrdiff_t>(shift),
                last
            );
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

        /**
         * @brief Количество столбцов матрицы.
         */
        const std::size_t shift = positions % columns_;

        for (std::size_t i = 0; i < rows_; ++i) {
            const auto first = data_.begin()
                + static_cast<std::ptrdiff_t>(i * columns_);
            const auto last = first
                + static_cast<std::ptrdiff_t>(columns_);

            std::rotate(
                first,
                last - static_cast<std::ptrdiff_t>(shift),
                last
            );
        }

        return *this;
    }

    /**
     * @brief Сравнивает размеры и элементы двух матриц.
     * @param other Матрица для сравнения.
     * @return true, если размеры и все элементы совпадают.
     */
    bool operator==(const Matrix& other) const {
        return rows_ == other.rows_
            && columns_ == other.columns_
            /**
             * @brief Элементы матрицы, расположенные последовательно по строкам.
             */
            && data_ == other.data_;
    }

private:
    /**
     * @brief Проверяет допустимость размеров и вычисляет количество элементов.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @return Произведение количества строк и столбцов.
     * @throws std::length_error Если размер превышает допустимый.
     */
    static std::size_t checkedSize(const std::size_t rows,
                                   const std::size_t columns) {
        if (columns != 0
            && rows > std::vector<T>{}.max_size() / columns)
            throw std::length_error("Matrix is too large");

        return rows * columns;
    }

    /**
     * @brief Элементы матрицы, расположенные последовательно по строкам.
     */
    std::vector<T> data_;
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
