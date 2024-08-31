#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <cstdlib>
using namespace std;

int Z_1() {
    const int N = 7; // Размерность матрицы (задаем N = 7)
    cout << "Задание 1______________________________________________________________________\n\n";
    // Создаем и инициализируем исходную матрицу размерности N случайными числами
    vector<vector<int>> matrix(N, vector<int>(N));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-10, 10); // диапазон случайных чисел от -10 до 10

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = dist(gen);
        }
    }

    // Создаем новую матрицу размерности 2xN для хранения копий элементов диагоналей
    vector<vector<int>> newMatrix(2, vector<int>(N));

    // Заполняем новую матрицу копиями элементов диагоналей исходной матрицы
    for (int i = 0; i < N; ++i) {
        newMatrix[0][i] = matrix[i][i]; // Копируем элементы главной диагонали
        newMatrix[1][i] = matrix[N - 1 - i][i]; // Копируем элементы побочной диагонали
    }

    // Выводим исходную матрицу
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "\t| ";
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\t|" << endl;
    }

    // Выводим новую матрицу
    cout << endl << endl << "Новая матрица:" << endl;
    for (int i = 0; i < 2; ++i) { // выводим две строки новой матрицы
        cout << "\t| ";
        for (int j = 0; j < N; ++j) {
            cout << newMatrix[i][j] << " ";
        }
        cout << "\t|" << endl;
    }
    cout << endl << endl;
    return 0;
}


int Z_2() {
    cout << "Задание 2______________________________________________________________________\n\n";
    srand(time(NULL)); // Инициализация генератора псевдослучайных чисел

    int M = 5; // Количество строк матрицы
    int N = 5; // Количество столбцов матрицы

    vector<vector<int>> matrix(M, vector<int>(N)); // Объявление матрицы размерности M x N

    // Инициализация матрицы случайными целыми числами
    cout << "Матрица:\n";
    for (int i = 0; i < M; ++i) {
        cout << "\t| ";
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 201 - 100; // Генерация случайного числа от -100 до 100
            cout << matrix[i][j] << " ";
        }
        cout << "\t|" << endl;
        
    }

    // Нахождение наибольшего и второго наименьшего элементов в матрице
    int maxElement = INT_MIN;
    int secondMinElement = INT_MAX;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] > maxElement) {
                secondMinElement = maxElement;
                maxElement = matrix[i][j];
            }
            else if (matrix[i][j] > secondMinElement && matrix[i][j] < maxElement) {
                secondMinElement = matrix[i][j];
            }
        }
    }

    // Замена диагональных элементов разностью наибольшего и второго наименьшего элементов
    for (int i = 0; i < min(M, N); ++i) {
        matrix[i][i] = maxElement - secondMinElement;
        matrix[i][N - i - 1] = maxElement - secondMinElement;
    }

    // Печать преобразованной матрицы
    cout << "\nПреобразованная матрица:\n";
    for (int i = 0; i < M; ++i) {
        cout << "\t| ";
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\t| ";
        cout << endl;
    }

    return 0;
}

const int N = 9;

bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grid[i][j] == num)
                return false;
        }
    }
    return true;
}

bool isValidSudoku(vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 0) {
                int num = grid[i][j];
                grid[i][j] = 0; // временно очищаем клетку для проверки
                if (!isSafe(grid, i, j, num)) {
                    return false;
                }
                grid[i][j] = num; // восстанавливаем значение клетки
            }
        }
    }
    return true;
}




int main() {
    setlocale(LC_ALL, "ru");
    Z_1(); 
    Z_2(); 
    cout << endl;
    cout << "задание 3______________________________________________________________________" << endl;
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (isValidSudoku(grid)) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }

    return 0;

   
}

