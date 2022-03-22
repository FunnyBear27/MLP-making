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


std::vector<long double> normalize(std::vector<long double> in){
    std::vector<long double> inp = in;
    long double maximum = maxElem(inp);
    for (int i = 0; i < inp.size(); i++){
        inp[i] = inp[i] / maximum;
    }
    return inp;
}


class Neuron{
protected:
    std::vector<long double> in_weights;
    std::vector<long double> inp;
    long double value;

public:
    Neuron(std::vector<long double> input_weights){
        in_weights = input_weights;
//        for (int i = 0; i < in_weights.size(); i++) {
//            std::cout << in_weights[i] << std::endl;
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
    
    void forwardPass(std::vector<long double> input_values){
        std::vector<long double> input = normalize(input_values);
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
        std::cout << "                 RESULTS" << "\n\n";
        for (int n = 0; n < out_shape; n++) {
            result.push_back(output_layer[n].countValue(curr_input));
            std::cout << output_layer[n].countValue(curr_input) << std::endl;
        }
    }
    
    void getShape(){
        std::cout << "Input: " << in_shape << "\nOutput: " << out_shape << "\n";
    }
};


int main()
{
    Model h(10, 5);
    h.addLayer(5);
    h.addLayer(13);
    h.addLayer(100);
    h.addLayer(2);
//    h.getShape();
    h.buildModel();
    h.forwardPass({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    return 0;
}
