/**
 * @file ExerciseTests.cpp
 * @brief Проверки заданий и точка входа в программу тестирования.
 */
#include "../Lab3.Library/ConstantGenerator.h"
#include "../Lab3.Library/Matrix.h"
#include "../Lab3.Library/Task1.h"
#include "../Lab3.Library/Task2.h"

#include <cassert>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace miit::algebra;

/** @brief Запускает проверки матрицы. */
void runMatrixTests();
/** @brief Запускает проверки генераторов. */
void runGeneratorTests();

/**
 * @brief Проверки заданий и точка входа в программу тестирования.
 * @note Проверки используют assert и должны выполняться без определения NDEBUG.
 */
void runExerciseTests() {
    const ConstantGenerator generator(0);

    const Matrix<int> source{
        {1, 9, 3},
        {-2, -7, -1},
        {6, 5, 4}
    };

    const Task1 task1(source, generator);

    const Matrix<int> expectedTask1{
        {1, 0, 3},
        {-2, -7, 0},
        {0, 5, 4}
    };

    assert(task1.solve().equals(expectedTask1));

    const Matrix<int> repeated{{9, 9, 2}};
    const Matrix<int> firstMaximumOnly{{0, 9, 2}};
    assert(Task1(repeated, generator).solve().equals(firstMaximumOnly));
    assert(task1.matrix().equals(source));

    const Task2 task2(source, generator);

    const Matrix<int> expectedTask2{
        {1, 9, 3},
        {-2, -7, -1},
        {0, 0, 0},
        {6, 5, 4}
    };

    assert(task2.solve().equals(expectedTask2));

    const Matrix<int> zeroFirstSource{
        {0, 1},
        {2, 3}
    };

    const Task2 zeroFirstTask(zeroFirstSource, generator);

    const Matrix<int> expectedZeroFirst{
        {0, 0},
        {0, 1},
        {2, 3}
    };

    assert(zeroFirstTask.solve().equals(expectedZeroFirst));

    std::cout << "Тесты заданий пройдены.\n";
}

/**
 * @brief Запускает все группы тестов библиотеки.
 * @return 0 после успешного прохождения всех проверок.
 */
int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    runMatrixTests();
    runGeneratorTests();
    runExerciseTests();

    std::cout << "Все тесты успешно пройдены.\n";

    return 0;
}