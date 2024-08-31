import random

def Z_1():
    N = 7
    print("Задание 1_____________________________________________________________________________________________\n\n")
    matrix = [[random.randint(-10, 10) for _ in range(N)] for _ in range(N)]
    newMatrix = [[0 for _ in range(N)] for _ in range(2)]

    for i in range(N):
        newMatrix[0][i] = matrix[i][i]
        newMatrix[1][i] = matrix[N - 1 - i][i]

    print("Исходная матрица:")
    for i in range(N):
        print("\t| ", end="")
        for j in range(N):
            print(matrix[i][j], end=" ")
        print("\t|")

    print("\n\nНовая матрица:")
    for i in range(2):
        print("\t| ", end="")
        for j in range(N):
            print(newMatrix[i][j], end=" ")
        print("\t|")

    print("\n\n")
    return 0


def Z_2():
    print("Задание 2_____________________________________________________________________________________________\n\n")
    random.seed()
    M = 5
    N = 5
    matrix = [[0 for _ in range(N)] for _ in range(M)]

    print("Матрица:")
    for i in range(M):
        print("\t| ", end="")
        for j in range(N):
            matrix[i][j] = random.randint(-100, 100)
            print(matrix[i][j], end=" ")
        print("\t|")

def find_max_and_second_min(matrix):
    max_element = float('-inf')
    second_min_element = float('inf')

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i][j] > max_element:
                second_min_element = max_element
                max_element = matrix[i][j]
            elif matrix[i][j] > second_min_element and matrix[i][j] < max_element:
                second_min_element = matrix[i][j]

    return max_element, second_min_element


def replace_diagonal_elements(matrix, max_element, second_min_element):
    for i in range(min(len(matrix), len(matrix[0]))):
        matrix[i][i] = max_element - second_min_element
        matrix[i][len(matrix[0]) - i - 1] = max_element - second_min_element

    return matrix


def print_matrix(matrix):
    print("\nПреобразованная матрица:")
    for i in range(len(matrix)):
        print("\t| ", end="")
        for j in range(len(matrix[0])):
            print(matrix[i][j], end=" ")
        print("\t|")


def is_safe(grid, row, col, num):
    for i in range(N):
        if grid[row][i] == num or grid[i][col] == num:
            return False

    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(start_row, start_row + 3):
        for j in range(start_col, start_col + 3):
            if grid[i][j] == num:
                return False

    return True


def is_valid_sudoku(grid):
    for i in range(N):
        for j in range(N):
            if grid[i][j] != 0:
                num = grid[i][j]
                grid[i][j] = 0
                if not is_safe(grid, i, j, num):
                    return False
                grid[i][j] = num

    return True


if __name__ == "__main__":
    Z_1()
    Z_2()
    matrix = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9]
    ]

    max_element, second_min_element = find_max_and_second_min(matrix)
    transformed_matrix = replace_diagonal_elements(matrix, max_element, second_min_element)
    print_matrix(transformed_matrix)

    if is_valid_sudoku(matrix):
        print("True")
    else:
        print("False")

