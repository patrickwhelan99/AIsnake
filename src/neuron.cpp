#include "neuron.h"
#include <cmath>
#include <iostream>

neuron::neuron(std::vector<double> &weights)
{
    this->weights = weights;
    this->output = 0;
}

double inline sigmoid(double output)
{
    const double EulerConstant = std::exp(1.0);
    return 1 / (1+std::pow(EulerConstant, -output));
}

void neuron::calcOutput()
{
    double cumulativeScore = 0;

    for(int i=0;i<inputs.size()-1;i++)
    {

        cumulativeScore += inputs.at(i) * weights.at(i);
    }

    this->output = sigmoid(cumulativeScore);

}
