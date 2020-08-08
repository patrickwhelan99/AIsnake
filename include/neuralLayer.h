#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <vector>
#include "neuron.h"

class neuralLayer
{
    public:
        neuralLayer();

        std::vector<neuron> &getNeurons() { return neurons; }
        void setNeurons(std::vector<neuron> val) { neurons = val; }
        void addNeuron(neuron &val) { neurons.push_back(val); }

        std::vector<double> &getOutputs() { return outputs; }
        void setOutput(std::vector<double> val) { outputs = val; }
        void addOutput(double val) { outputs.push_back(val); }

        std::vector<double> &getInputs() { return inputs; }
        void setInputs(std::vector<double> val) { inputs = val; }
        void addInputs(double val) { inputs.push_back(val); }

    protected:

    private:
        std::vector<neuron> neurons;
        std::vector<double> outputs;
        std::vector<double> inputs;
};

#endif // NEURALLAYER_H
