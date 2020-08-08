#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include "neuron.h"
#include "neuralLayer.h"


enum direction{up, right, down, left, none};

class neuralNet
{
    public:
        neuralNet(const int nLayers, const std::vector<int> &neuronsPerLayer, const double bias);
        direction tick(std::vector<double> inputs, direction currentDirection);


        std::vector<neuralLayer> &Getlayers() { return layers; }
        void Setlayers(std::vector<neuralLayer> val) { layers = val; }
        void addLayers(neuralLayer val) { layers.push_back(val); }

    protected:

    private:
        std::vector<neuralLayer> layers;
};

#endif // NEURALNET_H
