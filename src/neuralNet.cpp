#include "neuralNet.h"
#include <random>


std::vector<double> randomDoubles(int neuronsPerLayer)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1.0);

    std::vector<double> doubles;

    for(int i=0;i<neuronsPerLayer;i++)
    {
        doubles.push_back(dis(gen));
    }

    return doubles;
}

neuralNet::neuralNet(const int nLayers, const std::vector<int> &neuronsPerLayer, const double bias)
{
    for(int i=0;i<nLayers;i++)
    {
        neuralLayer newLayer;

        std::vector<double> weights;

        for(int j=0;j<neuronsPerLayer.at(i);j++)
        {
            if(i>0)
                weights = randomDoubles(neuronsPerLayer.at(i-1));
            else
                weights = randomDoubles(neuronsPerLayer.at(0));


            neuron newNeuron(weights);
            newLayer.addNeuron(newNeuron);
        }

        addLayers(newLayer);
    }
}





direction neuralNet::tick(std::vector<double> inputs, direction currentDirection)
{

    layers.at(0).setInputs(inputs);

    for(int i=0;i<layers.size();i++)
    {

        for(neuron &n : layers.at(i).getNeurons())
        {

            n.setInputs(layers.at(i).getInputs()); // Get forward fed data

            n.calcOutput();

            layers.at(i).addOutput(n.getOutput()); // Calculate the output for each neuron in the layer

        }

        if(i<layers.size()-1) // If not output layer
        {
            layers.at(i+1).setInputs(layers.at(i).getOutputs()); // Set the next layer's input equal to this one's output
        }
        else
        {
            direction directionToMove = none;
            double highestCurrentDirectionDesire = -2;

            for(int j=0;j<4;j++)
            {

                if(layers.back().getOutputs().at(j) > highestCurrentDirectionDesire)
                    highestCurrentDirectionDesire = layers.back().getOutputs().at(j);
            }


            for(int k=0;k<4;k++)
                if(layers.back().getOutputs().at(k) == highestCurrentDirectionDesire)
                    directionToMove = (direction)k;

            for(int l=0;l<layers.size();l++)
                layers.at(l).setOutput(std::vector<double>());


            return directionToMove;
        }


    }

}
