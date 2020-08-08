#include <SFML/Graphics.hpp>
#include <ctime>

#include "snake.h"
#include "population.h"
#include "neuralNet.h"



void tick(sf::RenderWindow &app, sf::RectangleShape &bg, population &p, sf::Text &generationText, sf::Font &font)
{

    bool allDead = true;
    for(snake &s : p.members)
    {
        if(!s.isDead())
        {
            direction d = s.brain.tick(s.getNeuralInputs(), s.getDirection());
            if(d != none && d != s.getDirection())
            {
                if(std::abs((int)d - (int)s.getDirection()) != 2)
                   s.setDirection(d);
            }

            s.tick();
            allDead = false;
        }
    }

    if(allDead)
        p.nextGen();


    app.clear();



    app.draw(bg);

    generationText.setString(std::to_string(p.generation));
    app.draw(generationText);


    int alive = 0;

    for(snake &s : p.members)
    {
        if(!s.isDead())
        {
            for(auto &r : s.getbodies())
            {
                app.draw(r);
            }

            app.draw(s.getCurrentPowerup());
            alive++;
        }

    }

    app.display();
}



int main()
{

    sf::Vector2f windowSize(800, 800);
    sf::RenderWindow app(sf::VideoMode(windowSize.x, windowSize.y), "No step on snek!");


    sf::RectangleShape bg(windowSize);
    bg.setFillColor(sf::Color(100, 100, 100));



    population p;
    for(int i=0;i<1000;i++)
    {
        snake s;
        p.members.push_back(s);
    }

    sf::Text generationText;
    generationText.setCharacterSize(512);
    generationText.setPosition(sf::Vector2f(150, 100));
    generationText.setString(std::to_string(p.generation));
    generationText.setColor(sf::Color(110, 110, 110));

    sf::Font font;
    font.loadFromFile("regular.otf");
    generationText.setFont(font);


    std::clock_t start;
    double duration;

    start = std::clock();

    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyReleased)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Return:
                        for(snake &s : p.members)
                            if(!s.isDead())
                                s.setdead(true);
                        break;

                    default:
                        break;


                    case sf::Keyboard::Up:
                        p.members.front().setDirection(up);
                        break;

                    case sf::Keyboard::Right:
                        p.members.front().setDirection(right);
                        break;

                    case sf::Keyboard::Down:
                        p.members.front().setDirection(down);
                        break;

                    case sf::Keyboard::Left:
                       p.members.front().setDirection(left);
                        break;

                }
            }

        }

        tick(app, bg, p, generationText, font);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        if(duration >= 0.1)
        {
            tick(app, bg, p, generationText, font);
            duration = 0;
            start = std::clock();
        }

    }

    return EXIT_SUCCESS;
}
