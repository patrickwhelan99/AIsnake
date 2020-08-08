#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "neuralNet.h"
#include <math.h>



class snake
{
    public:
        snake();
        void tick();
        neuralNet brain = neuralNet(3, std::vector<int>{10, 24, 4}, -1);
        int score = 1;
        std::vector<double> getNeuralInputs();
        double timeSincePowerup = 0;
        std::clock_t timePowerupReceived = std::clock();
        double movesMade = 0;
        double getFitness(){return std::pow(2, this->score)*(this->movesMade/12);};


        std::vector<sf::RectangleShape> getbodies() { return bodies; }
        void setbodies(std::vector<sf::RectangleShape> val) { bodies = val; }
        void addbody(sf::Vector2f offset = sf::Vector2f(0, 0));
        bool isDead() { return dead; }
        void setdead(bool val) { dead = val; }
        void setDirection(direction d){ currentDirection = d; }
        direction getDirection(){ return currentDirection; }
        std::vector<sf::Vector2f> getMovements() { return movements; }
        void addMovement(sf::Vector2f val) { movements.push_back(val); }
        void setMovements(std::vector<sf::Vector2f> m) { movements = m; }
        sf::CircleShape getCurrentPowerup() { return currentPowerup; }
        void spawnPowerup();

    protected:

    private:
        std::vector<sf::RectangleShape> bodies = std::vector<sf::RectangleShape>();
        bool dead;
        direction currentDirection = right;
        std::vector<sf::Vector2f> movements;
        sf::Vector2f lastTail;
        sf::CircleShape currentPowerup = sf::CircleShape(5, 10);
};

#endif // SNAKE_H
