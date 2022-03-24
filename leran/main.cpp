#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cmath>
#include <ctime>
#include <fstream>


// Прототипы
void readfile(std::string file_name, int input_shape, int output_shape, std::vector<long double>);
std::vector<long double> minmax(std::vector<long double> in);
long double maxElem(std::vector<long double> inp);
template <typename T>
void print(T a, std::string end = "\n");
long double errorCalc(std::vector<long double> res, std::vector<long double> true_val);

// Классы
class Neuron{
protected:
    std::vector<long double> in_weights;
    std::vector<long double> inp;
    long double value;

public:
    Neuron(std::vector<long double> input_weights){
        in_weights = input_weights;
//        for (int i = 0; i < in_weights.size(); i++) {
//        }
//        std::cout << "\n\n";
    }
    
    long double countValue(std::vector<long double> in){
        inp = in;
        value = 0;
        for (int i = 0; i < inp.size(); i++){
            value += inp[i] * in_weights[i];
        }
        value = actFunction(value);
        return value;
    }
    
    inline long double actFunction(long double x){
        return (1 / (1 + exp(-x)));
    }
};


class OutputNeurons{
    long double value;
    std::vector<long double> in_weights;
    std::vector<long double> inp;
    
public:
    OutputNeurons(std::vector<long double> input_weights){
        in_weights = input_weights;
    }
    
    long double countValue(std::vector<long double> in){
        inp = in;
        value = 0;
        for (int i = 0; i < inp.size(); i++){
            value += inp[i] * in_weights[i];
        }
        return value;
    }
};
 

class Model{
private:
    std::vector<std::vector<Neuron>> layers_vect;
    std::vector<OutputNeurons> output_layer;
    int in_shape, out_shape, curr_in;

public:
    Model(int size_input, int size_output){
        in_shape = size_input;
        out_shape = size_output;
        curr_in = size_input;
    }
    
    void addLayer(int neuron_amount, std::string activation_func = "logistic"){
        std::vector<Neuron> neurons;
        std::vector<long double> weights;
        for (int j = 0; j < neuron_amount; j++){
            for (int i = 0; i < curr_in; i++) {
                weights.push_back(2 * (static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - 1);
//                weights.push_back(static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX));
            }

            neurons.push_back(Neuron(weights));
            weights.clear();
        }
        layers_vect.push_back(neurons);
        curr_in = neuron_amount;
//        std::cout << "Added " << neuron_amount << " Neurons as layer " << layers_vect.size() << "!" << std::endl;
    }

    void buildModel(){
        std::vector<long double> weights;
        for (int j = 0; j < out_shape; j++) {
            for (int i = 0; i < curr_in; i++){
                weights.push_back(2 * (static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - 1);
            }
            output_layer.push_back(OutputNeurons(weights));
            weights.clear();
        }
    }
    
    long double trainModel(std::vector <std::vector<long double>> &input_vectors, std::vector <std::vector<long double>> &output_vectors, int epochs, bool show_progress = false){
        long double error;
        for(int epoch = 0; epoch < epochs; epoch++){
            std::vector<long double> errors;
            for (int i = 0; i < output_vectors.size(); i++){
                std::vector<long double> res = forwardPass(input_vectors[i]);
                error = errorCalc(res, output_vectors[i]);
                errors.push_back(error);
                std::cout << res[0] << "\t" << output_vectors[i][0] << "\n";
            }
            std::cout << "\n";
        }
        return 992.23;
    }
    
    std::vector<long double> forwardPass(std::vector<long double> input_values){
        std::vector<long double> input = minmax(input_values);
        std::vector<long double> curr_input = input;
        for (int layer = 0; layer < layers_vect.size(); layer++) {
            std::vector<long double> new_input;
            for (int n = 0; n < layers_vect[layer].size(); n++) {
                new_input.push_back(layers_vect[layer][n].countValue(curr_input));
            }
            curr_input = new_input;
            new_input.clear();
        }
        std::vector<long double> result;
        for (int n = 0; n < out_shape; n++) {
            result.push_back(output_layer[n].countValue(curr_input));
        }
        return result;
    }
    
    void getShape(){
        std::cout << "Input: " << in_shape << "\nOutput: " << out_shape << "\n";
    }
};

// Функции

long double maxElem(std::vector<long double> inp){
    long double m = inp[0];
    for (int i = 1; i < (inp.size()); i++){
        if (inp[i] > m){
            m = inp[i];
        }
    }
    return m;
}

long double minElem(std::vector<long double> inp){
    long double m = inp[0];
    for (int i = 1; i < (inp.size()); i++){
        if (inp[i] < m){
            m = inp[i];
        }
    }
    return m;
}

// НОРМАЛИЗАЦИЯ ДАННЫХ
std::vector<long double> minmax(std::vector<long double> in){
    std::vector<long double> inp = in;
    long double maximum = maxElem(inp);
    long double minimum = minElem(inp);
    for (int i = 0; i < inp.size(); i++){
        inp[i] = (inp[i] - minimum) / (maximum - minimum);
    }
    return inp;
}

// ФУНКЦИЯ ДЛЯ ЧТЕНИЯ ФАЙЛОВ И ПРЕОБРАЗОВАНИЯ В МАТРИЦУ
void readfile(std::string file_name, int input_shape, int output_shape, std::vector<std::vector<long double>> &inRef, std::vector<std::vector<long double>> &outRef){
    std::ifstream file;
    long double curr;
    file.open(file_name);
    if(!file){
        print("ERRor");
        std::exit(200);
    }
    while (!file.eof()){
        std::vector<long double> vect;
        for (int i = 0; i < input_shape; i++) {
            file >> curr;
            vect.push_back(curr);
            long double curr;
        }
        
        inRef.push_back(vect);
        vect.clear();
        for (int i = 0; i < output_shape; i++) {
            file >> curr;
            vect.push_back(curr);
            long double curr = 0;
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

// ШАБЛОН ФУНКЦИИ ДЛЯ УДОБНОГО ВЫВОДА В КОНСОЛЬ
template <typename T>
void print(T a, std::string end){
    std::cout << a << end;
}

// main

int main()
{
    // ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
    std::string p = __FILE__;
    std::string path = "";
    std::string filename;
    std::vector<std::vector<long double>> input_matrix;
    std::vector<std::vector<long double>> output_matrix;
    int input_shape, output_shape;

    // ВВОД ДАННЫХ ИЗ КОНСОЛИ
    std::cin >> input_shape;
    std::cin >> output_shape;
    std::cin >> filename;
    
    // АБСОЛЮТНЫЙ ПУТЬ ДО ДИРЕКТОРИИ ИСПОЛНЕМОГО ФАЙЛА
    for (int i = 0; i < p.size() - 8; i++) {
        path += p[i];
    }
    
    // ПРЕОБРАЗОВАНИЕ TXT ФАЙЛА В МАТРИЦЫ ВХОДНЫХ ДАННЫХ И ОТВЕТОВ
    readfile(path + "data/" + filename, input_shape, output_shape, input_matrix, output_matrix);
    
    Model model(input_shape, output_shape);
    model.addLayer(5);
    model.addLayer(1);
    model.buildModel();
    long double a = model.trainModel(input_matrix, output_matrix, 2);
    print(a);
    return 0;
}
