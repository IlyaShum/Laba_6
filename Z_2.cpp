#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;
#pragma once

using namespace std;
// Функция выполняет подстановку байтов в соответствии с предопределенной таблицей подстановки (S-box)
void SubBytes(vector<unsigned char>& state) {
    vector<unsigned char> Sbox = {  // содержит 256 элементов, представляющих собой однобайтовые значения
       0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
       0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
       0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
       0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
       0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
       0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
       0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
       0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
       0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
       0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
       0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
       0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
       0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
       0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
       0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
       0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };

    vector<unsigned char> temp;
    for (auto i : state) {
        temp.push_back(Sbox[i]);
    }
    state = temp;
}

// Функция выполняет обратную подстановку байтов в соответствии с другой предопределенной таблицей подстановки (Inverse S-box)
void InversionSubBytes(vector<unsigned char>& state) {
    vector<unsigned char> InvSbox = {   // содержит 256 элементов, представляющих собой однобайтовые значения
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };

    vector<unsigned char> temp;
    for (auto i : state) { // пройдемся по каждому элементу строки и заменим его на табличное значение
        temp.push_back(InvSbox[i]);
    }
    state = temp;
}


// Функция генерирует случайный ключ из 16 символов, где каждый символ - цифра от 0 до 9
void  keyGeneration(vector<unsigned char>& key) {   // функция, которая принимает вектор по ссылке и не возвращает никакого значения
    mt19937_64 gen(random_device{}());  // создание генератора случайных чисел для получения начального значения
    uniform_int_distribution<int> numbers(0, 9);    // создание равномерного распределения случайных чисел от 0 до 9
    for (int i = 1; i <= 16; i++) { // цикл (16 раз)
        key.push_back('0' + numbers(gen));  // генерируется случайное число от 0 до 9, прибавляется к символу '0', и результат добавляется в конец вектора
    }
}

// Функция операции XOR для добавления ключа к данным
vector<unsigned char> AddRoundKey(vector<unsigned char>& first, vector<unsigned char>& second) {    // функция, которая принимает два вектора по ссылке и возвращает новый вектор
    vector<unsigned char> temp; // создание временного вектора, в который будут помещены результаты операций XOR
    for (int i = 0; i < 4; ++i) {   // цикл (4 раза (по размеру векторов))
        temp.push_back(first[i] ^ second[i]);   // операция XOR для i-го элемента в first и i-го элемента в second, результат добавляется в конец вектора temp
    }
    return temp;    // возвращение вектора temp
}

// Функция сдвигает все элементы в векторе влево (первый элемент становится последним)
void ShiftElmnts(vector<unsigned char>& state) {    // функция, которая принимает вектор по ссылке и не возвращает никакого значения
    vector<unsigned char> temp(state.size());   // создание временного вектора той же длины, что и state
    for (int i = 1; i < state.size(); i++) {    // цикл, который проходит по всем элементам вектора (кроме первого)
        temp[i - 1] = state[i]; // каждый элемент вектора state сдвигается влево на одну позицию в векторе temp
    }
    temp[state.size() - 1] = state[0];  // первый элемент вектора state становится последним элементом в векторе temp

    state = temp;   // временный вектор присваивается исходному вектору
}

// Функция выполняет умножение в поле Галуа с использованием полинома (для реализации операций над многочленами в поле Галуа)
unsigned char galuaMn(unsigned char a, unsigned char b) {   // объявление функции, которая принимает два unsigned char и возвращает unsigned char
    unsigned char result = 0;   // переменная для хранения результата умножения
    unsigned char hi_bit_set;   // переменная для проверки, установлен ли самый старший бит в a
    for (unsigned char i = 0; i < 8; i++) { // цикл (8 раз (поля Галуа размером 8 бит))
        if (b & 1) {    // если младший бит в b равен 1
            result ^= a;    // то a прибавляется к result с помощью операции XOR
        }
        hi_bit_set = a & 0x80;  // проверка, установлен ли самый старший бит в a
        a <<= 1;    // сдвиг a влево на один бит
        if (hi_bit_set) {   // если самый старший бит в a был установлен до сдвига
            a ^= 0x1b;  // то к a применяется операция XOR
        }
        b >>= 1;    // сдвиг b вправо на один бит
    }
    return result;  // возвращение результата умножения
}

// Функция создает и возвращает таблицу умножения в поле Галуа для числа 2 для ускорения последующих операций умножения (результаты вычислены и хранятся в таблице)
vector<unsigned char> tabl_2() {    // объявление функции, которая не принимает никаких аргументов и возвращает вектор
    vector<unsigned char> tabl_with_2(256); // создание вектора размером 256 элементов
    for (int i = 0; i < 256; ++i) { // цикл (256 раз)
        tabl_with_2[i] = galuaMn(i, 2); // для каждого значения i в диапазоне от 0 до 255 вызывается функция, которая выполняет умножение в поле Галуа для числа i на 2
    }
    return tabl_with_2; // возвращение заполненной таблицы умножения для числа 2
}

// Функция создает и возвращает таблицу умножения в поле Галуа для числа 3
vector<unsigned char> tabl_3() {
    vector<unsigned char> tabl_with_3(256);
    for (int i = 0; i < 256; ++i) {
        tabl_with_3[i] = galuaMn(i, 3);
    }
    return tabl_with_3;
}

// Функция создает и возвращает таблицу умножения в поле Галуа для числа 14
vector<unsigned char> tabl_14() {
    vector<unsigned char> tabl_with_14(256);
    for (int i = 0; i < 256; ++i) {
        tabl_with_14[i] = galuaMn(i, 14);
    }
    return tabl_with_14;
}

// Функция создает и возвращает таблицу умножения в поле Галуа для числа 9
vector<unsigned char> tabl_9() {
    vector<unsigned char> tabl_with_9(256);
    for (int i = 0; i < 256; ++i) {
        tabl_with_9[i] = galuaMn(i, 9);
    }
    return tabl_with_9;
}

// Функция создает и возвращает таблицу умножения в поле Галуа для числа 13
vector<unsigned char> tabl_13() {
    vector<unsigned char> tabl_with_13(256);
    for (int i = 0; i < 256; ++i) {
        tabl_with_13[i] = galuaMn(i, 13);
    }
    return tabl_with_13;
}
// Функция создает и возвращает таблицу умножения в поле Галуа для числа 11
vector<unsigned char> tabl_11() {
    vector<unsigned char> tabl_with_11(256);
    for (int i = 0; i < 256; ++i) {
        tabl_with_11[i] = galuaMn(i, 11);
    }
    return tabl_with_11;
}

// Функция выполняет операции умножения на 2 и 3 над столбцами матрицы данных (вектор state)
void MnMatrix(vector<unsigned char>& state) {   // объявление функции, которая принимает вектор по ссылке и не возвращает никакого значения
    vector<unsigned char> tabl_with_2 = tabl_2();   // вектор содержит таблицу умножения в поле Галуа для числа 2

    vector<unsigned char> tabl_with_3 = tabl_3();   // вектор содержит таблицу умножения в поле Галуа для числа 3

    vector<unsigned char> temp; // временный вектор для хранения результатов операций
    temp.push_back(tabl_with_2[state[0]] ^ tabl_with_3[state[1]] ^ state[2] ^ state[3]);    // операции умножения на 2 и 3 над столбцами матрицы данных, вычисление новых значений для каждого столбца
    temp.push_back(tabl_with_2[state[1]] ^ tabl_with_3[state[2]] ^ state[0] ^ state[3]);
    temp.push_back(tabl_with_2[state[2]] ^ tabl_with_3[state[3]] ^ state[0] ^ state[1]);
    temp.push_back(tabl_with_2[state[3]] ^ tabl_with_3[state[0]] ^ state[1] ^ state[2]);
    state = temp;   // замена исходного вектора state новым вектором temp с новыми значениями
}

// Функция выполняет расширение ключа (операция сдвига, замена байтов, применение констант для каждого раунда)
void KeyExpansion(vector<unsigned char>& key, vector<vector<unsigned char>>& roundKeys) {   // функция, которая принимает исходный ключ и вектор векторов roundKeys (где расширенные ключи для каждого раунда)
    const vector<unsigned char> Rcon = {    // вектор с константами для операции XOR с ключом в процессе расширения ключа
        0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00,
        0x80, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00,
        0x36, 0x00, 0x00, 0x00
    };

    vector<unsigned char> temp; // временный вектор для хранения промежуточных значений
    int i = 0;
    int Nk = 4; // размер ключа
    int Nb = 4; // размер блока
    int Nr = 10;    // количество раундов

    roundKeys.resize(Nb * (Nr + 1), vector<unsigned char>(4));  // изменение размера вектора для вмещения расширенных ключей для всех раундов, включая начальный

    // Заполнение первых ключей из исходного ключа
    while (i < Nk) {    // цикл (4 раза)
        temp = { key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3] };  // копирование 4-байтного блока из исходного ключа в temp
        roundKeys[i] = temp;    // копирование блока из temp в roundKeys
        i++;    // увеличение счетчика цикла
    }

    // Расширение ключей
    i = Nk;
    while (i < (Nb * (Nr + 1))) {   // цикл для расширения ключа до необходимого размера
        temp = roundKeys[i - 1];    // копирование предыдущего расширенного ключа в temp
        if (i % Nk == 4) {  // условие, которое проверяет, нужно ли применять операции SubBytes и ShiftElmnts к блоку ключа
            ShiftElmnts(temp);  // функция, которая сдвигает элементы
            SubBytes(temp); // функция, которая заменяет элементы на другие значения
            for (int k = 0; k < temp.size(); ++k) {
                temp[k] = temp[k] ^ Rcon[i / Nk];   // применение операции XOR к каждому элементу temp с соответствующей константой из Rcon
            }
        }
        else if (Nk > 6 && (i % Nk == 4)) { // доп условие, которое проверяет, нужно ли применять операцию SubBytes к блоку ключа, если Nk > 6
            SubBytes(temp);
        }
        for (int j = 0; j < temp.size(); ++j) {
            roundKeys[i][j] = roundKeys[i - Nk][j] ^ temp[j];   // применение операции XOR между предыдущим расширенным ключом и temp для получения нового расширенного ключа
        }
        i++;    // увеличение счетчика цикла
    }
}

// Функция выполняет обратный сдвиг элементов
void InversionShiftElmnts(vector<unsigned char>& state) {   // функция, которая принимает вектор по ссылке и не возвращает никакого значения
    vector<unsigned char> temp(state.size());   // создание временного вектора temp той же длины, что и state
    for (int i = 0; i < state.size(); i++) {    // цикл проходит по всем элементам вектора state
        temp[i] = state[(i - (i % 4) * (i % 4)) % state.size()];    // обратный сдвиг элементов
    }
    state = temp;   // временный вектор temp присваивается исходному вектору state
}

// Функция выполняет обратные операции умножения над столбцами матрицы данных
void InversionMnMatrix(vector<unsigned char>& state) {  // функция, которая принимает вектор по ссылке и не возвращает никакого значения
    vector<unsigned char> tabl_with_14 = tabl_14(); // вектор, который содержит таблицу умножения в поле Галуа для числа 14
    vector<unsigned char> tabl_with_9 = tabl_9();   // вектор, который содержит таблицу умножения в поле Галуа для числа 9
    vector<unsigned char> tabl_with_13 = tabl_13(); // вектор, который содержит таблицу умножения в поле Галуа для числа 13
    vector<unsigned char> tabl_with_11 = tabl_11(); // вектор, который содержит таблицу умножения в поле Галуа для числа 11

    vector<unsigned char> temp; // временный вектор для хранения результатов операций
    temp.push_back(tabl_with_14[state[0]] ^ tabl_with_9[state[1]] ^ tabl_with_13[state[2]] ^ tabl_with_11[state[3]]);   // вычисление новых значений для каждого столбца
    temp.push_back(tabl_with_14[state[1]] ^ tabl_with_9[state[2]] ^ tabl_with_13[state[3]] ^ tabl_with_11[state[0]]);
    temp.push_back(tabl_with_14[state[2]] ^ tabl_with_9[state[3]] ^ tabl_with_13[state[0]] ^ tabl_with_11[state[1]]);
    temp.push_back(tabl_with_14[state[3]] ^ tabl_with_9[state[0]] ^ tabl_with_13[state[1]] ^ tabl_with_11[state[2]]);
    state = temp;   // замена исходного вектора state новым вектором temp с новыми значениями
}

// Функция разбивает входную строку на блоки размером 16 байт
void createBlocks(string& text, vector<vector<vector<unsigned char>>>& block) { // функция, которая принимает строку по ссылке и двумерный вектор, в котором будут храниться блоки
    while (text.size() % 16 != 0) { // цикл пока размер строки не будет кратен 16
        text += ' ';    // добавление пробелов в конец строки
    }

    vector<vector<vector<unsigned char>>> temporary;    // временный вектор для хранения блоков
    vector<vector<unsigned char>> sixteen(4, vector<unsigned char>(4)); // вектор, который представляет собой матрицу 4x4, в которой будут храниться байты из строки text

    for (int i = 0; i < text.size(); ++i) { // цикл, который проходит по всем символам строки
        int a = (i % 16) % 4;   // вычисление индексов для текущего символа в матрице sixteen
        int b = (i % 16) / 4;
        sixteen[a][b] = text[i];    // присваивание текущему элементу матрицы sixteen значения текущего символа из строки text

        if ((i + 1) % 16 == 0) {    // условие, которое проверяет, достиг ли счетчик i размера блока (16)
            temporary.push_back(sixteen);   // текущий блок (матрица sixteen) добавляется в вектор temporary
            sixteen = vector<vector<unsigned char>>(4, vector<unsigned char>(4));   // матрица sixteen обнуляется для следующего блока
        }
    }

    block = temporary;  // вектор temporary, который содержит все блоки (каждый блок представляет собой матрицу 4x4 байт), присваивается вектору block
}

// Функция выполняет шифрование блока данных с использованием ключа и раундовых ключей
vector<vector<unsigned char>> Encrypt(vector<vector<unsigned char>>& block, vector<vector<unsigned char>>& roundKeys, vector<unsigned char> key) {  // принимает блок данных, вектор раундовых ключей и ключ, возвращает зашифрованный блок данных

    vector<vector<unsigned char>> temp(4, vector<unsigned char>(4, 0)); // временный вектор размером 4x4, заполненный нулями (для хранения промежуточных результатов шифрования)
    for (int i = 0; i < 4; ++i) {   // цикл выполняет начальное добавление раундового ключа к блоку данных
        temp[i] = AddRoundKey(block[i], roundKeys[i]);
    }

    for (int i = 1; i <= 9; i++) {  // основной цикл шифрования, который выполняется 9 раз для каждого из 10 раундов
        for (int j = 0; j <= 3; j++) {  // цикл, где выполняются операции шифрования для каждого столбца блока данных
            SubBytes(temp[j]);  // функция заменяет каждый байт в столбце на другой байт, используя таблицу замен для шифрования
            ShiftElmnts(temp[j]);   // функция сдвигает элементы в столбце влево на один байт
            MnMatrix(temp[j]);  // функция выполняет операции умножения над столбцом в поле Галуа
            temp[j] = AddRoundKey(temp[j], roundKeys[i]);   // функция добавляет раундовый ключ к столбцу
        }
    }

    for (int j = 0; j <= 3; j++) {  // цикл, где выполняются те же операции, что и внутри основного цикла, но для последнего раунда
        SubBytes(temp[j]);
        ShiftElmnts(temp[j]);
        temp[j] = AddRoundKey(temp[j], roundKeys[10]);
    }

    return temp;    // возвращение зашифрованного блока данных
}

// Функция выполняет дешифрование блока данных с использованием ключа и раундовых ключей
vector<vector<unsigned char>> Decrypt(vector<vector<unsigned char>>& block, vector<vector<unsigned char>>& roundKeys, vector<unsigned char> key) {  // принимает зашифрованный блок данных, вектор раундовых ключей и ключ, возвращает дешифрованный блок данных
    vector<vector<unsigned char>> roundKeysDec(44, vector<unsigned char>(4));   // вектор размером 44x4 для хранения раундовых ключей после расширения ключа
    KeyExpansion(key, roundKeysDec);    // функция расширяет ключ key и сохраняет расширенные ключи в roundKeysDec

    vector<vector<unsigned char>> temporary(4, vector<unsigned char>(4, 0));    // временный вектор размером 4x4, заполненный нулями (для хранения промежуточных результатов дешифрования)

    for (int j = 0; j <= 3; j++) {  // цикл выполняет начальное добавление последнего раундового ключа к блоку данных
        temporary[j] = AddRoundKey(block[j], roundKeys[10]);
    }

    for (int i = 9; i >= 1; i--) {  // основной цикл дешифрования, который выполняется 9 раз для каждого из 10 раундов в обратном порядке
        for (int j = 0; j <= 3; j++) {  // цикл, где выполняются обратные операции шифрования для каждого столбца блока данных
            temporary[j] = AddRoundKey(temporary[j], roundKeys[i]); // функция добавляет раундовый ключ к столбцу 
            InversionMnMatrix(temporary[j]);    // функция выполняет обратные операции умножения над столбцом в поле Галуа
            InversionShiftElmnts(temporary[j]); // функция выполняет обратный сдвиг элементов в столбце
            InversionSubBytes(temporary[j]);    // функция выполняет обратную замену байтов в столбце
        }
    }

    for (int j = 0; j <= 3; j++) {  // цикл добавляет первый раундовый ключ к каждому столбцу
        temporary[j] = AddRoundKey(temporary[j], roundKeys[0]);
    }
    for (int j = 0; j <= 3; j++) {  // цикл выполняет обратные операции шифрования для первого раунда
        InversionShiftElmnts(temporary[j]);
        InversionSubBytes(temporary[j]);
    }

    return temporary;   // возвращение дешифрованного блока данных
}

int main() {
    system("chcp 1251");
    string text;    // ввод строки текста
    cout << "Input message: ";
    getline(cin, text); // считывает строку текста, включая пробелы, и сохраняет ее в переменную text

    // Вывод блоков данных
    vector<vector<vector<unsigned char>>> block;    // трехмерный вектор (массив) внутри которого будут храниться блоки данных (генерация матрицы для работы)
    createBlocks(text, block);  // функция разбивает строку на блоки и сохраняет их в векторе
    cout << "----------------------------------------------";
    cout << "\nThe encryption block: \n";
    for (auto i : block) {  // вложенные циклы, которые проходят по всем элементам вектора и выводят их на экран
        for (auto j : i) {
            for (auto k : j) {
                cout << setw(4) << k << " ";    // вывод каждого байта k с отступом в 4 символа
            }
            cout << endl;
        }
    }
    cout << "\n----------------------------------------------" << endl;

    vector<unsigned char> key;  // вектор для записи сгенерированного ключа
    keyGeneration(key);    // функция генерирует ключ и записывает его в вектор
    cout << "128-bit key: ";
    for (auto i : key) {    // цикл проходит по каждому байту в векторе и выводит его на экран
        cout << i;
    }
    cout << "\n----------------------------------------------\n";

    vector<vector<unsigned char>> roundKeys;    // двумерный вектор для записи раундовых ключей
    KeyExpansion(key, roundKeys);   // функция расширяет ключ и записывает их в вектор 
    cout << "Generated round keys: \n";
    for (auto i : roundKeys) {  // вложенные циклы, которые проходят по всем элементам вектора и выводят их на экран
        for (auto j : i) {
            cout << hex << setw(4) << static_cast<int>(j) << " ";   // вывод каждого байта в шестнадцатеричном формате с отступом в 4 символа

        }
        cout << endl;
    }
    cout << "\n----------------------------------------------" << endl;

    // Для хранения промежуточных данных
    vector<vector<unsigned char>> PREV(4, vector<unsigned char>(4, 0)); // двумерный вектор размером 4x4, заполненный нулями
    vector<vector<unsigned char>> DEFOLT = PREV;    // те же размеры и содержимое, что и PREV
    // Для хранения ключей
    vector<vector<unsigned char>> TEK;  // двумерный вектор
    // Для хранения зашифрованных данных
    vector<vector<vector<unsigned char>>> ECRYPT;   // трехмерный вектор

    for (int i = 0; i < block.size(); i++) {    // цикл проходит по каждому блоку в векторе

        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));  // двумерный вектор размером 4x4, заполненный нулями (для хранения результата XOR-операции)
        vector<vector<unsigned char>> B = block[i]; // переменная для хранения i-го блока из вектора block
        TEK = Encrypt(PREV, roundKeys, key);

        for (int i = 0; i < 4; ++i) {   // проходит по каждому элементу в TEK и B
            for (int j = 0; j < 4; ++j) {
                res[i][j] = (TEK[i][j] ^ B[i][j]);  // выполняет XOR-операцию между ними и записывает результат в res

            }
        }
        ECRYPT.push_back(res);  // добавляет вектор res в конец вектора ECRYPT

        PREV = TEK; // обновление значения для следующей итерации цикла
    }

    cout << "The encrypted message: \n" << endl;
    for (auto t : ECRYPT) { // вложенные циклы, которые проходят по всем элементам вектора и выводят их на экран
        for (auto i : t) {
            for (auto j : i) {
                cout << setw(4) << j << " ";
            }
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------\n";

    PREV = DEFOLT;  // обновление значения обратно до исходного состояния
    // Для хранения расшифрованных данных
    vector<vector<vector<unsigned char>>> DECRYPT;  // трехмерный вектор

    for (int i = 0; i < ECRYPT.size(); ++i) {   // цикл проходит по каждому блоку в векторе, который содержит зашифрованные данные
        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));  // двумерный вектор размером 4x4, заполненный нулями (для хранения результата XOR-операции)
        vector<vector<unsigned char>> B = ECRYPT[i];    // переменная для хранения i-го блока из вектора ECRYPT
        TEK = Encrypt(PREV, roundKeys, key);

        for (int i = 0; i < 4; ++i) {   // проходит по каждому элементу в TEK и B
            for (int j = 0; j < 4; ++j) {
                res[i][j] = (B[i][j] ^ TEK[i][j]);  // выполняет XOR-операцию между ними и записывает результат в res
            }
        }
        DECRYPT.push_back(res); // добавляет вектор res в конец вектора DECRYPT
        PREV = TEK; // обновление значения для следующей итерации цикла
    }

    vector<vector<vector<unsigned char>>> DECRYPT_1;    // новый трехмерный вектор для хранения расшифрованных данных

    for (int i = 0; i < ECRYPT.size(); ++i) {   // цикл проходит по каждому блоку в векторе, который содержит зашифрованные данные
        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));  // двумерный вектор размером 4x4, заполненный нулями (для хранения результата дешифрования)
        vector<vector<unsigned char>> B = ECRYPT[i];    // переменная для хранения i-го блока из вектора ECRYPT
        TEK = Decrypt(B, roundKeys, key);

        for (int i = 0; i < 4; ++i) {   // проходит по каждому элементу в TEK
            for (int j = 0; j < 4; ++j) {
                res[i][j] = TEK[i][j];  // копирует его в res
            }
        }
        DECRYPT_1.push_back(res);   // добавляет вектор res в конец вектора DECRYPT_1
    }

    cout << "The decrypted message: \n" << endl;
    for (int i = 0; i < DECRYPT.size(); i++) {  // внешний цикл проходит по каждому блоку в векторе DECRYPT
        vector<vector<unsigned char>>& decrypt = DECRYPT[i];    // ссылка на i-й блок в DECRYPT
        for (int j = 0; j < decrypt.size(); j++) {  // внутренний цикл проходит по каждому элементу в блоке
            for (int k = 0; k < decrypt[j].size(); k++) {   // цикл проходит по каждому элементу внутри элемента блока
                cout << decrypt[k][j];  // выводит k-й элемент j-го элемента блока
            }
        }
    }
    cout << "\n----------------------------------------------\n" << endl;

    return 0;
}

