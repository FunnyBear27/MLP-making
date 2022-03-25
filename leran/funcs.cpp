//
//  funcs.cpp
//  leran
//
//  Created by Руслан Закиров on 25/03/2022.
//

#include "funcs.hpp"

void readfile(std::string file_name, int input_shape, int output_shape, std::vector<std::vector<long double>> &inRef, std::vector<std::vector<long double>> &outRef);

void minmax(std::vector<std::vector<long double>> &inp, long double &maximum, long double &minimum);
void minmax(std::vector<long double> &in);
long double maxElem(std::vector<std::vector<long double>> const &inp);
long double maxElem(std::vector<long double> const &inp);
long double minElem(std::vector<std::vector<long double>> const &inp);
long double minElem(std::vector<long double> const &inp);
long double errorCalc(std::vector<long double> res, std::vector<long double> true_val);



// Функции
// ФУНКЦИЯ МАКСИМУМА
long double maxElem(std::vector<long double> const &inp){
    long double m = inp[0];
    for (int i = 1; i < (inp.size()); i++){
        if (inp[i] > m){
            m = inp[i];
        }
    }
    return m;
}

// ФУНКЦИЯ МИНИМУМА
long double minElem(std::vector<long double> const &inp){
    long double m = inp[0];
    for (int i = 1; i < (inp.size()); i++){
        if (inp[i] < m){
            m = inp[i];
        }
    }
    return m;
}

// НОРМАЛИЗАЦИЯ ДАННЫХ
void minmax(std::vector<long double> &inp){
    long double maximum = maxElem(inp);
    long double minimum = minElem(inp);
    for (int i = 0; i < inp.size(); i++){
        inp[i] = (inp[i] - minimum) / (maximum - minimum);
    }
}

long double maxElem(std::vector<std::vector<long double>> const &inp){
    long double m = inp[0][0];
    for (int i = 0; i < (inp.size()); i++){
        for (int j = 0; j < inp[0].size(); j++){
            if (inp[i][j] > m){
                m = inp[i][j];
            }
        }
    }
    return m;
}

// ФУНКЦИЯ МИНИМУМА
long double minElem(std::vector<std::vector<long double>> const &inp){
    long double m = inp[0][0];
    for (int i = 0; i < (inp.size()); i++){
        for (int j = 0; j < inp[0].size(); j++){
            if (inp[i][j] < m){
                m = inp[i][j];
            }
        }
    }
    return m;
}

void minmax(std::vector<std::vector<long double>> &inp, long double &maximum, long double &minimum){
    maximum = maxElem(inp);
    minimum = minElem(inp);
    for (int i = 0; i < inp.size(); i++){
        for (int j = 0; j < inp[0].size(); j++){
            inp[i][j] = (inp[i][j] - minimum) / (maximum - minimum);
        }
    }
}

// ФУНКЦИЯ ДЛЯ ЧТЕНИЯ ФАЙЛОВ И ПРЕОБРАЗОВАНИЯ В МАТРИЦУ
void readfile(std::string file_name, int input_shape, int output_shape, std::vector<std::vector<long double>> &inRef, std::vector<std::vector<long double>> &outRef){
    std::ifstream file;
    long double curr;
    file.open(file_name);
    if(!file){
        std::cout << "ERRor READing FIle" << "\n";
        std::exit(200);
    }
    while (!file.eof()){
        std::vector<long double> vect;
        for (int i = 0; i < input_shape; i++) {
            file >> curr;
            vect.push_back(curr);
            curr = NULL;
        }
        minmax(vect);
        inRef.push_back(vect);
        vect.clear();
        for (int i = 0; i < output_shape; i++) {
            file >> curr;
            vect.push_back(curr);
            curr = NULL;
        }
        outRef.push_back(vect);
        vect.clear();
    }
}

// ВЫСЧИТЫВАНИЕ ОШИБКИ ПО ОДНОМУ ОБУЧАЮЩЕМУ ПРИМЕРУ
long double errorCalc(std::vector<long double> res, std::vector<long double> true_val){
    long double error = 0;
    for (int i = 0; i < res.size(); i++){
        error += pow((res[i] - true_val[i]), 2);
    }
    return 0.5 * error;
}
