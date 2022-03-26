#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cmath>
#include <ctime>
#include <fstream>

#ifndef funcs_hpp
#define funcs_hpp

#include <stdio.h>

float const ETA = 0.5;
void readfile(std::string file_name, int input_shape, int output_shape, std::vector<std::vector<long double>> &inRef, std::vector<std::vector<long double>> &outRef);

void minmax(std::vector<std::vector<long double>> &inp, long double &maximum, long double &minimum);
void minmax(std::vector<long double> &in);
long double maxElem(std::vector<std::vector<long double>> const &inp);
long double maxElem(std::vector<long double> const &inp);
long double minElem(std::vector<std::vector<long double>> const &inp);
long double minElem(std::vector<long double> const &inp);

std::vector<long double> errorCalc(std::vector<std::vector<long double>> &res, std::vector<std::vector<long double>> const &true_val);
#endif /* funcs_hpp */
