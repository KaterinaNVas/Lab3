#include "../Lab3.Library/ConstantGenerator.h"
#include "../Lab3.Library/Generator.h"
#include "../Lab3.Library/IStreamGenerator.h"
#include "../Lab3.Library/Matrix.h"
#include "../Lab3.Library/RandomGenerator.h"
#include "../Lab3.Library/Task1.h"
#include "../Lab3.Library/Task2.h"
#include "../Lab3.Library/ZeroGenerator.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace miit::algebra;

/**
 * @brief Способы заполнения матрицы.
 */
enum GeneratorChoice {
    randomFill = 1,
    constantFill = 2,
    inputFill = 3,
    zeroFill = 4
};

/**
 * @brief Варианты задания.
 */
enum TaskChoice {
    task1Choice = 1,
    task2Choice = 2
};

/**
 * @brief Получает положительное целое число.
 * @param message Сообщение для пользователя.
 * @return Введённое положительное число.
 */
std::size_t getPositive(const char* message);

/**
 * @brief Получает целое число.
 * @param message Сообщение для пользователя.
 * @return Введённое целое число.
 */
int getInteger(const char* message);

/**
 * @brief Позволяет выбрать способ заполнения матрицы.
 * @param message Сообщение для пользователя.
 * @return Указатель на созданный генератор.
 */
std::unique_ptr<Generator> chooseGenerator(
    const char* message
);

/**
 * @brief Запускает выбранное задание.
 * @param matrix Исходная матрица.
 * @param generator Используемый генератор.
 */
void runTask(
    const Matrix<int>& matrix,
    Generator& generator
);

/**
 * @brief Точка входа в программу.
 * @return 0 при успешном завершении.
 */
int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "Лабораторная работа 3. Вариант 6\n";

    const std::size_t rows =
        getPositive("Введите количество строк:");

    const std::size_t columns =
        getPositive("Введите количество столбцов:");

    Matrix<int> matrix(rows, columns);

    std::unique_ptr<Generator> generator =
        chooseGenerator(
            "Выберите способ заполнения матрицы:"
        );

    matrix.fill(*generator);

    std::cout
        << "\nПолученная матрица:\n"
        << matrix.toString()
        << '\n';

    runTask(matrix, *generator);

    return 0;
}

std::size_t getPositive(const char* message) {
    std::cout << message << '\n';

    long long value{};

    if (std::cin >> value && value > 0) {
        return static_cast<std::size_t>(value);
    }

    std::cerr
        << "Некорректный ввод: ожидалось "
        << "положительное целое число.\n";

    std::exit(EXIT_FAILURE);
}

int getInteger(const char* message) {
    if (message[0] != '\0') {
        std::cout << message << '\n';
    }

    int value{};

    if (std::cin >> value) {
        return value;
    }

    std::cerr
        << "Некорректный ввод: ожидалось целое число.\n";

    std::exit(EXIT_FAILURE);
}

std::unique_ptr<Generator> chooseGenerator(
    const char* message
) {
    std::cout
        << message << '\n'
        << randomFill
        << " - случайные числа\n"
        << constantFill
        << " - константное значение\n"
        << inputFill
        << " - ввод с клавиатуры\n"
        << zeroFill
        << " - заполнение нулями\n";

    const int choice = getInteger("");

    switch (choice) {
        case randomFill: {
            const int minValue =
                getInteger("Введите минимум диапазона:");

            const int maxValue =
                getInteger("Введите максимум диапазона:");

            return std::make_unique<RandomGenerator>(
                minValue,
                maxValue
            );
        }

        case constantFill: {
            const int value =
                getInteger("Введите значение константы:");

            return std::make_unique<ConstantGenerator>(
                value
            );
        }

        case inputFill:
            std::cout << "Введите значения матрицы:\n";

            return std::make_unique<IStreamGenerator>(
                std::cin
            );

        case zeroFill:
            return std::make_unique<ZeroGenerator>();

        default:
            std::cerr << "Некорректный выбор.\n";
            std::exit(EXIT_FAILURE);
    }
}

void runTask(
    const Matrix<int>& matrix,
    Generator& generator
) {
    std::cout
        << "\nВыберите задание:\n"
        << task1Choice
        << " - заменить максимальный элемент "
        << "каждой строки нулём\n"
        << task2Choice
        << " - вставить нулевые строки перед строками, "
        << "первый элемент которых делится на 3\n";

    const int choice = getInteger("");

    switch (choice) {
        case task1Choice: {
            Task1 task(matrix, generator);
            const Matrix<int> result = task.solve();

            std::cout
                << "\nРезультат задания 1:\n"
                << result.toString()
                << '\n';

            break;
        }

        case task2Choice: {
            Task2 task(matrix, generator);
            const Matrix<int> result = task.solve();

            std::cout
                << "\nРезультат задания 2:\n"
                << result.toString()
                << '\n';

            break;
        }

        default:
            std::cerr << "Некорректный выбор.\n";
            std::exit(EXIT_FAILURE);
    }
}