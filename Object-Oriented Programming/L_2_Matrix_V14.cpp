#include <iostream>
#include <limits>

void swapRows(int** matrix, int row1, int row2, int cols) {
    for (int j = 0; j < cols; ++j) {
        std::swap(matrix[row1][j], matrix[row2][j]);
    }
}

int main() {
    int N, M;
    std::srand(time(0)); // Инициализация генератора случайных чисел

    std::cout << "Введите количество строк (N): ";
    std::cin >> N;
    std::cout << "Введите количество столбцов (M): ";
    std::cin >> M;

    // Создаем матрицу
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[M];
    }

    // Заполняем матрицу случайными числами
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = std::rand() % 100; 
            std::cout << matrix[i][j] << " "; 
        }
        std::cout << std::endl;
    }

    // Поиск максимального и минимального элементов
    int maxRow = 0, minRow = 0;
    int maxVal = std::numeric_limits<int>::min();
    int minVal = std::numeric_limits<int>::max();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxRow = i;
            }
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
            }
        }
    }

    std::cout << "Максимальный элемент: " << maxVal << " в строке " << maxRow + 1 << std::endl;
    std::cout << "Минимальный элемент: " << minVal << " в строке " << minRow + 1 << std::endl;

    swapRows(matrix, maxRow, minRow, M);

    std::cout << "Измененная матрица: \n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождаем память
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
