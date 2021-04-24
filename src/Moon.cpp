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
    mOrder = ord;
    switch(pSize) {
        case constants::PlanetSize::Psmall: mMass = (rand() % 50) / 400.f + 0.001;
                    mRadius = (float)(rand() % 5) / 400.f + 0.0001;
                    break;
        case constants::PlanetSize::Pnormal: mMass = (rand() % 50) / 100.f + 0.001;
                    mRadius = (float)(rand() % 5) / 100.f + 0.001;
                    break;
        case constants::PlanetSize::Plarge: mMass = (rand() % 50) / 50.f + 0.01;
                    mRadius = (float)(rand() % 5) / 50.f + 0.01;
                    break;
    }
    // mass = mass * EARTHMASS;
    // radius = radius * EARTHRADIUS;

    mColor = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);
    mDistance = 25 * (mOrder + 1) + previousDistance + 10;
    float realDistance = (mDistance / 150) * constants::EARTHDISTANCE;
    mT = sqrt(pow(realDistance, 3) / K);
    mAngularVelocity = constants::FULLANGLE / mT;

    if (mAngularVelocity == 0)
    {
        mAngularVelocity = 1;
    }
    mAngle = 0;
}
