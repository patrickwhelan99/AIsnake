#include "snake.h"

#include <random>

#define speed 35
#define snekSize 30

snake::snake()
{
    sf::RectangleShape head(sf::Vector2f(snekSize, snekSize));
    head.setPosition(sf::Vector2f(400, 400));
    head.setFillColor(sf::Color::Green);
    bodies.push_back(head);

    addbody(sf::Vector2f(-35, 0));
    //addbody(sf::Vector2f(-35, 0));
    //addbody(sf::Vector2f(-35, 0));


    spawnPowerup();
}

void snake::tick()
{
    sf::Vector2f upMovement(0, -speed);
    sf::Vector2f rightMovement(speed, 0);
    sf::Vector2f downMovement(0, speed);
    sf::Vector2f leftMovement(-speed, 0);

    this->movesMade++;

    this->lastTail = this->bodies.back().getPosition(); // The current end before moving, where a new block will be added

    for(int i=bodies.size()-1;i>0;i--)
    {
        this->bodies.at(i).setPosition(this->bodies.at(i-1).getPosition()); // Reverse iterate moving each block into the one above
    }

    switch(currentDirection) // Move the head according to direction
        {
            case up:
                this->bodies.at(0).setPosition(this->bodies.at(0).getPosition() + upMovement);
                this->movements.push_back(upMovement);
                break;


            case right:
                this->bodies.at(0).setPosition(this->bodies.at(0).getPosition() + rightMovement);
                this->movements.push_back(rightMovement);
                break;

            case down:
                this->bodies.at(0).setPosition(this->bodies.at(0).getPosition() + downMovement);
                this->movements.push_back(downMovement);
                break;


            case left:
                this->bodies.at(0).setPosition(this->bodies.at(0).getPosition() + leftMovement);
                this->movements.push_back(leftMovement);
                break;


            default:
                break;
        }


    this->timeSincePowerup = ( std::clock() - timePowerupReceived ) / (double) CLOCKS_PER_SEC;

    if(this->timeSincePowerup > 20)
        this->dead = true;

    for(sf::RectangleShape &r : this->bodies) // Check for collisions with self and "walls"
    {
        for(sf::RectangleShape &q : this->bodies)
        {
            if((&q != &r && q.getGlobalBounds().intersects(r.getGlobalBounds())) || q.getPosition().x > 800 || q.getPosition().x < 0 || q.getPosition().y > 800 || q.getPosition().y < 0)
                this->dead = true;
        }
    }

    if(this->bodies.front().getGlobalBounds().intersects(this->currentPowerup.getGlobalBounds())) // Check for collisions with powerup
    {
        this->addbody();
        spawnPowerup();
        this->timeSincePowerup = 0;
        this->timePowerupReceived = std::clock();
        this->score++;
    }

}

void snake::addbody(sf::Vector2f offset)
{
    this->lastTail = bodies.back().getPosition();
    sf::RectangleShape newBod(sf::Vector2f(snekSize, snekSize));
    newBod.setPosition(this->lastTail + offset);
    newBod.setFillColor(sf::Color::Magenta);
    bodies.push_back(newBod);
}

void snake::spawnPowerup()
{

    this->currentPowerup.setFillColor(sf::Color::Red);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(20.0, 780.0);

    while(true)
    {
        this->currentPowerup.setPosition(sf::Vector2f(dis(gen), dis(gen)));

        bool flag = false;

        for(sf::RectangleShape &b : bodies)
        {
            if(b.getGlobalBounds().intersects(this->currentPowerup.getGlobalBounds()))
                flag = true;
        }

        if(!flag)
            break;
    }
}

double clamp(double x, double minimum, double maximum)
{
    return (std::min(maximum, std::max(x, minimum)))/maximum;
}

double inline calcDist(const sf::Vector2f &p1, const sf::Vector2f &p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}


std::vector<double> snake::getNeuralInputs()
{
    std::vector<double> inputs;

    const sf::Vector2f headPosition = bodies.at(0).getPosition();

    // Set the shortest distances to the edges of the area

    double shortestUp = calcDist(headPosition, sf::Vector2f(headPosition.x, 0));
    double shortestRight = calcDist(headPosition, sf::Vector2f(800, headPosition.y));;
    double shortestDown = calcDist(headPosition, sf::Vector2f(headPosition.x, 800));;
    double shortestLeft = calcDist(headPosition, sf::Vector2f(0, headPosition.y));;

    double closestBodyUp = 1000;
    double closestBodyRight = 1000;
    double closestBodyDown = 1000;
    double closestBodyLeft = 1000;

    for(sf::RectangleShape &b : bodies)
    {
        if(b.getPosition() != headPosition)
        {
            if(b.getPosition().x == headPosition.x && b.getPosition().y < headPosition.y)
            {
                double dist = calcDist(headPosition, b.getPosition());
                if(dist < closestBodyUp)
                    closestBodyUp = dist;
            }

            if(b.getPosition().y == headPosition.y && b.getPosition().x > headPosition.x)
            {
                double dist = calcDist(headPosition, b.getPosition());
                if(dist < closestBodyRight)
                    closestBodyRight = dist;
            }

            if(b.getPosition().x == headPosition.x && b.getPosition().y > headPosition.y)
            {
                double dist = calcDist(headPosition, b.getPosition());
                if(dist < closestBodyDown)
                    closestBodyDown = dist;
            }

            if(b.getPosition().y == headPosition.y && b.getPosition().x < headPosition.x)
            {
                double dist = calcDist(headPosition, b.getPosition());
                if(dist < closestBodyLeft)
                    closestBodyLeft = dist;
            }

        }

    }

    double powerupUp, powerupRight, powerupDown, powerupLeft;

    double xdist = 1000;

    if(this->currentPowerup.getPosition().y == headPosition.y)
        xdist = this->currentPowerup.getPosition().x - headPosition.x;

    double ydist = 1000;

    if(this->currentPowerup.getPosition().x == headPosition.x)
       ydist = this->currentPowerup.getPosition().y - headPosition.y;



    inputs.push_back(shortestUp);
    inputs.push_back(shortestRight);
    inputs.push_back(shortestDown);
    inputs.push_back(shortestLeft);

    inputs.push_back(closestBodyUp);
    inputs.push_back(closestBodyRight);
    inputs.push_back(closestBodyDown);
    inputs.push_back(closestBodyLeft);

    inputs.push_back(xdist);
    inputs.push_back(ydist);

    return inputs;
}


