/**
 * @file Exercise.h
 * @brief Объявления Exercise.
 */
#pragma once
#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra {
/**
 * @brief Абстрактное задание, работающее с копией исходной матрицы.
 */
class Exercise {
protected:
    /**
     * @brief Копия исходной матрицы задания.
     */
    Matrix<int> matrix_;
    /**
     * @brief Ссылка на генератор; он должен существовать дольше задания.
     */
    const Generator& generator_;
public:
    /**
     * @brief Создаёт задание с копией готовой матрицы.
     * @param matrix Исходная матрица.
     * @param generator Генератор, который должен существовать дольше задания.
     */
    Exercise(const Matrix<int>& matrix, const Generator& generator);
    /**
     * @brief Обеспечивает корректное уничтожение объекта через базовый класс.
     */
    virtual ~Exercise() = default;
    /**
     * @brief Выполняет задание и возвращает новую матрицу.
     * @return Матрица результата; исходная матрица не изменяется.
     */
    virtual Matrix<int> solve() const = 0;
    /**
     * @brief Предоставляет доступ к исходной матрице задания.
     * @return Константная ссылка на сохранённую матрицу.
     */
    const Matrix<int>& matrix() const noexcept;
};
}
