/**
 * @file ZeroGenerator.h
 * @brief Объявления ZeroGenerator.
 */
#pragma once
#include "Generator.h"

namespace miit::algebra {
/**
 * @brief Генератор, возвращающий ноль.
 */
class ZeroGenerator final : public Generator {
public:
    /**
     * @brief Возвращает ноль.
     * @return Сгенерированное целое число.
     */
    int generate() const override;
};
}
