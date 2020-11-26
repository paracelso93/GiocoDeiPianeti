#include "Star.h"


Star::Star()
{
    //ctor
}

Star::~Star()
{
    //dtor
}

void Star::createStar(int x, int y)
    {
        this->x = x;
        this->y = y;
        exists = rand() % 20 < 2;

        
        if (!exists)
            return;
        radius = ((float)(rand() % 10000) / 1000 + 0.001);
        mass = sqrt(sqrt(pow(radius, 5)));

        hasDysonSphere = false;

        //mass = mass * SOLARMASS;
        //radius = radius * SOLARRADIUS;
        this->x = this->x + (constants::GRIDSIDELENGTH / 2 - (this->radius * 2));
        this->y = this->y + (constants::GRIDSIDELENGTH / 2 - (this->radius * 2));
        color = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);

        K = (constants::G * mass * constants::SOLARMASS) / (4 * constants::PI * constants::PI);


        int len = rand() % 5 + 5;
        name = "";

        for(int p = 0; p < len; p ++) {
            name += (char)(rand()%21 + 65);
        }

        shape.setPosition(this->x, this->y);
        shape.setFillColor(this->color);
        shape.setRadius(this->radius * 2);
        guiShape.setPosition(300, constants::STARGUIY + constants::UPPERGUIHEIGHT);
        guiShape.setFillColor(this->color);
        guiShape.setRadius(this->radius * 8);
        nump = rand() % 9;
        for (int i = 0; i < nump; i++)
        {
            planets[i].createPlanet(i, K, i == 0 ? 50 : planets[i - 1].distance);
            orbits[i].setFillColor(sf::Color::Transparent);
            orbits[i].setOutlineColor(sf::Color(255, 255, 255, 100));
            orbits[i].setOutlineThickness (4);

            orbits[i].setRadius(planets[i].distance);
            orbits[i].setPosition(300 - planets[i].distance + this->radius * 8, 885 - planets[i].distance + this->radius * 8);
        }
    }
