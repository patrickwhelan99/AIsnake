#include "population.h"
#include <random>
#include <iostream>

struct sortByFitness
{
    inline bool operator() (const snake& s1, const snake& s2)
    {
        return (std::pow(2, s1.score)*(s1.movesMade/12) > std::pow(2, s2.score)*(s2.movesMade/12));
    }
};


population::population()
{

}

snake &population::selectParent()
{
    double runningTotal = 0;

    for(snake &s : members)
    {
        runningTotal += s.getFitness();
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dist(0, runningTotal);
    double rDouble = dist(gen);

    double finder = 0;
    for(snake &s : members)
    {
        finder += s.getFitness();
        if(finder >= rDouble)
           return s;
    }

    return members.at(0); // Should never be reached
}

snake population::splice(snake &p1, snake &p2, double highestFitness)
{
    snake childSnake;
    int i = 0, j = 0, k = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 2);
    std::uniform_real_distribution<> mutationDist(-1.0, 1.0);

    if(dist(gen) == 1)
        childSnake.brain = p1.brain;
    else
        childSnake.brain = p2.brain;

    for(neuralLayer &nl : childSnake.brain.Getlayers())
    {
        for(neuron &n : nl.getNeurons())
        {

            for(double &weight : n.getWeights())
            {

                int randNum = dist(gen);
                double randReal = mutationDist(gen);


                if(randReal > 0.98)
                {
                    /*
                    if(randNum == 1)
                        weight = p1.brain.Getlayers().at(i).getNeurons().at(j).getWeights().at(k);
                    else
                        weight = p2.brain.Getlayers().at(i).getNeurons().at(j).getWeights().at(k);
                    */
                }
                else
                    weight = mutationDist(gen);



                k++;
            }
            k = 0;
            j++;
        }
        j = 0;
        i++;
    }

    return childSnake;


}

void population::nextGen()
{
    std::vector<snake> newPop;

    std::sort(members.begin(), members.end(), sortByFitness());



    printf("Best:\t%f\n", members.front().getFitness());
    printf("Worst:\t%f\n", members.back().getFitness());

    double runningTotal = 0;

    for(snake &s : members)
        runningTotal += s.getFitness();

    printf("Avg:\t%f\n\n\n", runningTotal / (double)members.size());

    cull();


    for(int i=0;i<10;i++)
    {
        for(snake &s : members)
        {
            // Splice the two DNAs together
            snake babySnek = splice(selectParent(), selectParent(), members.front().getFitness());
            newPop.push_back(babySnek);
        }
    }


    members = newPop;

    generation++;

}
