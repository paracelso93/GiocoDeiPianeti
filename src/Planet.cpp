#include "Planet.h"


Planet::Planet()
{
    //ctor
}

Planet::~Planet()
{
    //dtor
}

void Planet::createPlanet(int ord, double K, float previousDistance){
    order = ord;

    this->occupierID = 0;

    bool choice = rand()%2 == 0;
    if(choice) {
        mass = (float)(rand() % 50) / 50 + 0.1f;
    } else {
        mass = (float)(rand() % 500) / 10.f;
    }
    if(mass < 1) {
        size = constants::PlanetSize::Psmall;
        radius = pow(mass, 0.3);
    } else if(mass <= 200) {
        size = constants::PlanetSize::Pnormal;
        radius = pow(mass, 0.5);
    } else {
        size = constants::PlanetSize::Plarge;
        radius = pow(mass, -0.0886) * 22.6;
    }

    //mass = mass * EARTHMASS;
    //radius = radius * EARTHRADIUS;

    //std::cout << "mass: " << mass << std::endl;

    distance = previousDistance + 50 + (radius * 10);
    //std::cout << "radius: " << radius << std::endl;

    color = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);
    numn = rand() % 8;
    float realDistance = (distance / 150) * constants::EARTHDISTANCE;
    T = sqrt(pow(realDistance, 3) / K);
    angularVelocity = constants::FULLANGLE / T;
    //std::cout << "periodo: " << T << std::endl;
    angle = 0;
    this->K = (constants::G * (mass * constants::EARTHMASS)) / (4 * constants::PI * constants::PI);
    for (int i = 0; i < numn; i++)
    {
        moons[i].createMoon(i, this->K, i == 0 ? radius : moons[i - 1].distance, size);
        /*while(true) {
            if(moons[i].radius >= radius) {
                moons[i].radius /= 10;
            } else {
            break;
            }
        }*/
    }

    int len = rand() % 5 + 3;
    name = "";

    for(int p = 0; p < len; p ++) {
        name += (char)(rand()%21 + 65);
    }
}
