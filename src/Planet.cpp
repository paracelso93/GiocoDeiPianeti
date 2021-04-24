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
    mOrder = ord;

    this->mOccupierID = 0;

    bool choice = rand()%2 == 0;
    if(choice) {
        mMass = (float)(rand() % 50) / 50 + 0.1f;
    } else {
        mMass = (float)(rand() % 500) / 10.f;
    }
    if(mMass < 1) {
        mSize = constants::PlanetSize::Psmall;
        mRadius = pow(mMass, 0.3);
    } else if(mMass <= 200) {
        mSize = constants::PlanetSize::Pnormal;
        mRadius = pow(mMass, 0.5);
    } else {
        mSize = constants::PlanetSize::Plarge;
        mRadius = pow(mMass, -0.0886) * 22.6;
    }

    //mass = mass * EARTHMASS;
    //radius = radius * EARTHRADIUS;

    //std::cout << "mass: " << mass << std::endl;

    mDistance = previousDistance + 50 + (mRadius * 10);
    //std::cout << "radius: " << radius << std::endl;

    mColor = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);
    mNumn = rand() % 8;
    float realDistance = (mDistance / 150) * constants::EARTHDISTANCE;
    mT = sqrt(pow(realDistance, 3) / K);
    mAngularVelocity = constants::FULLANGLE / mT;
    //std::cout << "periodo: " << T << std::endl;
    mAngle = 0;
    this->mK = (constants::G * (mMass * constants::EARTHMASS)) / (4 * constants::PI * constants::PI);
    for (int i = 0; i < mNumn; i++)
    {
        mMoons[i].createMoon(i, this->mK, i == 0 ? mRadius : mMoons[i - 1].mDistance, mSize);
        /*while(true) {
            if(moons[i].radius >= radius) {
                moons[i].radius /= 10;
            } else {
            break;
            }
        }*/
    }

    int len = rand() % 5 + 3;
    mName = "";

    for(int p = 0; p < len; p ++) {
        mName += (char)(rand()%21 + 65);
    }
}
