#include "Moon.h"


Moon::Moon()
{
    //ctor
}

Moon::~Moon()
{
    //dtor
}

void Moon::createMoon(int ord, double K, float previousDistance, constants::PlanetSize pSize)
{
    order = ord;
    switch(pSize) {
        case constants::PlanetSize::Psmall: mass = (rand() % 50) / 400.f + 0.001;
                    radius = (float)(rand() % 5) / 400.f + 0.0001;
                    break;
        case constants::PlanetSize::Pnormal: mass = (rand() % 50) / 100.f + 0.001;
                    radius = (float)(rand() % 5) / 100.f + 0.001;
                    break;
        case constants::PlanetSize::Plarge: mass = (rand() % 50) / 50.f + 0.01;
                    radius = (float)(rand() % 5) / 50.f + 0.01;
                    break;
    }
    // mass = mass * EARTHMASS;
    // radius = radius * EARTHRADIUS;

    color = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);
    distance = 25 * (order + 1) + previousDistance + 10;
    float realDistance = (distance / 150) * constants::EARTHDISTANCE;
    T = sqrt(pow(realDistance, 3) / K);
    angularVelocity = constants::FULLANGLE / T;

    if (angularVelocity == 0)
    {
        angularVelocity = 1;
    }
    angle = 0;
}
