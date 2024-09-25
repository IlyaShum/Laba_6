#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <locale.h> //подключение библиотеки для задач связанных из локализацией

using namespace std;

const double EPS = 0.001;
const int MAX_ITERATIONS = 1000;

// Функция для вывода вектора
void printVector(const vector<double>& vec) {
    for (double val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& mat) {
    for (const auto& row : mat) {
        printVector(row);
    }
}

// Функция для решения системы методом LU-разложения
vector<double> solveLU(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0)), U(n, vector<double>(n, 0.0));

    // LU-разложение
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                U[i][j] = A[i][j];
                for (int k = 0; k < i; k++) {
                    U[i][j] -= L[i][k] * U[k][j];
                }
            }
            if (i > j) {
                L[i][j] = A[i][j];
                for (int k = 0; k < j; k++) {
                    L[i][j] -= L[i][k] * U[k][j];
                }
                L[i][j] /= U[j][j];
            }
        }
    }

    // Прямой ход
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Обратный ход
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    return x;
}

// Функция для решения системы методом Зейделя
vector<double> solveGaussSeidel(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<double> x(n, 0.0), x_new(n, 0.0);
    double sum;
    double norm_diff;
    int iteration = 0;

    do {
        x = x_new;
        for (int i = 0; i < n; i++) {
            sum = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum -= A[i][j] * x[j];
                }
            }
            x_new[i] = sum / A[i][i];
        }
        // Вычисляем норму разности векторов вручную
        norm_diff = 0.0;
        for (int i = 0; i < n; ++i) {
            norm_diff += (x_new[i] - x[i]) * (x_new[i] - x[i]);
        }
        norm_diff = sqrt(norm_diff);
        iteration++;
    } while (norm_diff > EPS && iteration < MAX_ITERATIONS);

    if (iteration == MAX_ITERATIONS) {
        cout << "Превышено максимальное количество итераций. Метод не сошелся." << endl;
    }

    return x_new;
}

// Функция для решения системы методом простых итераций
vector<double> solveSimpleIteration(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& x0) {
    int n = A.size();
    vector<double> x = x0;
    vector<double> x_new(n, 0.0);
    double norm_diff;
    int iteration = 0;

    do {
        for (int i = 0; i < n; ++i) {
            double sum = b[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum -= A[i][j] * x[j];
                }
            }
            // Проверка на ноль перед делением
            if (fabs(A[i][i]) > EPS) {
                x_new[i] = sum / A[i][i];
            }
            else {
                cout << "Ошибка: деление на ноль при итерации " << iteration << endl;
                return x; // Возвращаем текущее приближение
            }
        }

        // Вычисляем норму разности векторов вручную
        norm_diff = 0.0;
        for (int i = 0; i < n; ++i) {
            norm_diff += (x_new[i] - x[i]) * (x_new[i] - x[i]);
        }
        norm_diff = sqrt(norm_diff);

        x = x_new; // Обновление текущего приближения
        iteration++;
    } while (norm_diff > EPS && iteration < MAX_ITERATIONS);

    if (iteration == MAX_ITERATIONS) {
        cout << "Превышено максимальное количество итераций. Метод не сошелся." << endl;
    }

    return x;
}

int main() {
    setlocale(LC_ALL, "rus");   // установка русской локали

    // Инициализация системы уравнений
    vector<vector<double>> A = { {0.89, -0.04, 0.21, -18}, {0.25, -1.23, 0.08, -0.09}, {-0.21, 0.08, 0.8, -0.13}, {0.15, -1.31, 0.06, -1.21} };
    vector<double> b = { -1.24, -1.21, 2.56, 0.89 };

    // Решение системы прямым методом LU-разложения
    vector<double> x_lu = solveLU(A, b);
    cout << "Решение системы прямым методом LU-разложения:" << endl;
    printVector(x_lu);

    // Решение системы приближенным методом Зейделя
    vector<double> x_gauss = solveGaussSeidel(A, b);
    cout << "Решение системы приближенным методом Зейделя:" << endl;
    printVector(x_gauss);

    // Преобразование системы к каноническому виду
    vector<vector<double>> B(4, vector<double>(4, 0.0));
    vector<double> f(4, 0.0);
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (i == j) {
                B[i][j] = 0.0;
            }
            else {
                B[i][j] = -A[i][j] / A[i][i];
            }
        }
        f[i] = b[i] / A[i][i];
    }

    // Начальное приближение
    vector<double> x0 = { 0.0, 0.0, 0.0, 0.0 };

    // Решение системы итерационным методом
    vector<double> x_iter = solveSimpleIteration(B, f, x0);
    cout << "Решение системы итерационным методом:" << endl;
    printVector(x_iter);

    // Вывод результатов в таблицу
    cout << "N\tx1\tx2\tx3\tx4\tEPS" << endl;
    for (int i = 0; i < x_lu.size(); i++) {
        cout << i + 1 << "\t";
        for (size_t j = 0; j < x_lu.size(); ++j) {
            cout << x_lu[j] << "\t";
        }
        // Вычисляем норму разности векторов вручную
        double norm_diff = 0.0;
        for (size_t j = 0; j < x_lu.size(); ++j) {
            norm_diff += (x_lu[j] - x_gauss[j]) * (x_lu[j] - x_gauss[j]);
        }
        norm_diff = sqrt(norm_diff);
        cout << "\t" << norm_diff << endl;
    }

    // Нахождение всех корней системы уравнений
    cout << "Корни системы уравнений:" << endl;
    printVector(x_lu);

    return 0;
}

