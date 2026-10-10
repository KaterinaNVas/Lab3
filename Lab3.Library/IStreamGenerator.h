/**
 * @file IStreamGenerator.h
 * @brief Объявления IStreamGenerator.
 */
#pragma once
#include "Generator.h"
#include <iosfwd>

namespace miit::algebra {
/**
 * @brief Генератор, читающий целые числа из входного потока.
 */
class IStreamGenerator final : public Generator {
    /**
     * @brief Входной поток; он должен существовать дольше генератора.
     */
    std::istream& in_;
public:
    /**
     * @brief Связывает генератор с входным потоком.
     * @param in Поток для чтения целых чисел.
     */
    explicit IStreamGenerator(std::istream& in);
    /**
     * @brief Читает следующее целое число из потока.
     * @return Сгенерированное целое число.
     * @throws std::runtime_error Если число не удалось прочитать.
     */
    int generate() const override;
};
}
