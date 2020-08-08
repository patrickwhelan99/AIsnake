#ifndef NEURON_H
#define NEURON_H

#include <vector>

class neuron
{
    public:
        neuron(std::vector<double> &weights);
        void calcOutput();

        std::vector<double> &getWeights() { return weights; }
        void setWeights(std::vector<double> val) { weights = val; }

        std::vector<double> getInputs() { return inputs; }
        void setInputs(std::vector<double> val) { inputs = val; }
        void addInput(double val) { inputs.push_back(val); }

        double getOutput() { return output; }
        void setOutput(double val) { output = val; }

    protected:

    private:
        std::vector<double> weights;
        std::vector<double> inputs;
        double output;
};

#endif // NEURON_H
