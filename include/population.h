#ifndef POPULATION_H
#define POPULATION_H
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class population
{
    public:
        population();

        std::vector<snake> members;

        void cull(){ members.erase(members.begin()+(members.size()/10), members.end()); }
        snake splice(snake &p1, snake &p2, double highestFitness);
        snake &selectParent();
        void nextGen();
        int generation = 1;


    protected:

    private:

};

#endif // POPULATION_H
