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

void runMatrixTests();
void runGeneratorTests();

void runExerciseTests() {
    ConstantGenerator generator(0);

    const Matrix<int> source{
        {1, 9, 3},
        {-2, -7, -1},
        {6, 5, 4}
    };

    Task1 task1(source, generator);

    const Matrix<int> expectedTask1{
        {1, 0, 3},
        {-2, -7, 0},
        {0, 5, 4}
    };

    assert(task1.solve() == expectedTask1);

    Task2 task2(source, generator);

    const Matrix<int> expectedTask2{
        {1, 9, 3},
        {-2, -7, -1},
        {0, 0, 0},
        {6, 5, 4}
    };

    assert(task2.solve() == expectedTask2);

    const Matrix<int> zeroFirstSource{
        {0, 1},
        {2, 3}
    };

    Task2 zeroFirstTask(zeroFirstSource, generator);

    const Matrix<int> expectedZeroFirst{
        {0, 0},
        {0, 1},
        {2, 3}
    };

    assert(zeroFirstTask.solve() == expectedZeroFirst);

    std::cout << "Тесты заданий пройдены.\n";
}

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