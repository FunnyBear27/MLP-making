#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <ctime>

long double maxElem(std::vector<long double> inp){
    long double m = inp[0];
    for (int i = 1; i < (inp.size()); i++){
        if (inp[i] > m){
            m = inp[i];
        }
    }
    return m;
}


std::vector<long double> normalization(std::vector<long double> in){
    std::vector<long double> inp = in;
    long double maximum = maxElem(inp);
    for (int i = 0; i < inp.size(); i++){
        inp[i] = inp[i] / maximum;
    }
    return inp;
}


class Neuron{
    long double value;
    std::vector<long double> in_weights;

public:
    Neuron(std::vector<long double> input_weights){
        in_weights = input_weights;
    }
    
    long double countValue(std::vector<long double> in, std::vector<long double> weights){
        std::vector<long double> inp = in;
        for (int i = 0; i < inp.size(); i++){
            value += inp[i] * weights[i];
        }
        value = actFunction(value);
        return value;
    }
    
    inline long double actFunction(long double x){
        return (1 / (1 + exp(-x)));
    }
};
 

class Model{
private:
    std::vector<std::vector<Neuron>> layers_vect;
    int in_shape, out_shape, curr_in;

public:
    Model(int size_input, int size_output){
        in_shape = size_input;
        out_shape = size_output;
        curr_in = size_input;
    }
    
    void addLayer(std::string activation_func, int neuron_amount){
        std::vector<Neuron> neurons;
        std::vector<long double> weights;
        for (int j = 0; j < neuron_amount; j++){
            for (int i = 0; i < curr_in; i++) {
                weights.push_back(2 * (static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - 1);
            }
            neurons.push_back(Neuron(weights));
        }
        layers_vect.push_back(neurons);
        curr_in = neuron_amount;
    }
    
    void getShape(){
        std::cout << "Input: " << in_shape << "\nOutput: " << out_shape << "\n";
    }
};


int main()
{
    Model h(5, 8);
    h.getShape();
    return 0;
}
