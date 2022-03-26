#include "funcs.hpp"

// Классы
class Neuron{
protected:
    std::vector<long double> in_weights;
    std::vector<long double> inp;
    long double value;

public:

    // КОНСТРУКТОР КЛАССА
    Neuron(std::vector<long double> input_weights){
        in_weights = input_weights;
    }
    
    // ВЗВЕШЕННАЯ СУММА
    long double countValue(std::vector<long double> in){
        inp = in;
        value = 0;
        for (int i = 0; i < inp.size(); i++){
            value += inp[i] * in_weights[i];
        }
        value = actFunction(value);
        return value;
    }
    
    // ЛОГИСТИЧЕСКАЯ ФУНКЦИЯ АКТИВАЦИИ
    inline long double actFunction(long double x){
        return (1 / (1 + exp(-x)));
    }
};


class OutputNeurons{
    long double value;
    std::vector<long double> in_weights;
    std::vector<long double> inp;
    
public:

    // КОНСТРУКТОР КЛАССА
    OutputNeurons(std::vector<long double> input_weights){
        in_weights = input_weights;
    }
    
    // ВЗВЕШЕННАЯ СУММА
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

    // КОНСТРУКТОР КЛАССА
    Model(int size_input, int size_output){
        in_shape = size_input;
        out_shape = size_output;
        curr_in = size_input;
    }
    
    // ДОБАВЛЕНИЕ СЛОЯ НЕЙРОНОВ
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
        std::cout << "Added " << neuron_amount << " Neurons as layer " << layers_vect.size() << "!" << std::endl;
    }

    // ОКОНЧАТЕЛЬНАЯ СБОРКА МОДЕЛИ
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
    
    // ОСНОВНОЙ МЕТОД КЛАССА
    void trainModel(std::vector <std::vector<long double>> &input_vectors, std::vector <std::vector<long double>> &output_vectors, int epochs, bool show_progress = false){
        std::vector<long double> errors;
        std::vector<std::vector<long double>> res;
        for(int epoch = 0; epoch < epochs; epoch++){
            for (int i = 0; i < output_vectors.size(); i++){
                 res.push_back(forwardPass(input_vectors[i]));
            }
            errors = errorCalc(res, output_vectors);
            std::cout << errors[0] << "\t" << errors.size() << "\n";
        }
    }
    
    // FORWARD PROPOGATION
    std::vector<long double> forwardPass(std::vector<long double> input){

        std::vector<long double> curr_input = input;
        std::vector<long double> new_input;

        for (int layer = 0; layer < layers_vect.size(); layer++) {
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
};

// ГЛАВНАЯ ФУНКЦИЯ

int main()
{
    // ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
    std::string p = __FILE__;
    std::string path = "";
    std::string filename;
    std::vector<std::vector<long double>> input_matrix;
    std::vector<std::vector<long double>> output_matrix;
    long double out_max, out_min;
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
    minmax(output_matrix, out_max, out_min);
    // СОЗДАНИЕ МОДЕЛИ
    Model model(input_shape, output_shape);
    model.addLayer(5);
    model.addLayer(5);
    model.buildModel();

    // ОБУЧЕНИЕ МОДЕЛИ
    model.trainModel(input_matrix, output_matrix, 2);
    return 0;
}
