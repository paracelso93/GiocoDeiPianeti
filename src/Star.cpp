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
        this->mX = x;
        this->mY = y;
        mExists = rand() % 20 < 2;

        
        if (!mExists)
            return;
        mRadius = ((float)(rand() % 10000) / 1000 + 0.001);
        mMass = sqrt(sqrt(pow(mRadius, 5)));

        mHasDysonSphere = false;

        //mass = mass * SOLARMASS;
        //radius = radius * SOLARRADIUS;
        this->mX = this->mX + (constants::GRIDSIDELENGTH / 2 - (this->mRadius * 2));
        this->mY = this->mY + (constants::GRIDSIDELENGTH / 2 - (this->mRadius * 2));
        mColor = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 156 + 100);

        mK = (constants::G * mMass * constants::SOLARMASS) / (4 * constants::PI * constants::PI);


        int len = rand() % 5 + 5;
        mName = "";

        for(int p = 0; p < len; p ++) {
            mName += (char)(rand()%21 + 65);
        }

        mShape.setPosition(this->mX, this->mY);
        mShape.setFillColor(this->mColor);
        mShape.setRadius(this->mRadius * 2);
        mGuiShape.setPosition(300, constants::STARGUIY + constants::UPPERGUIHEIGHT);
        mGuiShape.setFillColor(this->mColor);
        mGuiShape.setRadius(this->mRadius * 8);
        mNumP = rand() % 9;
        for (int i = 0; i < mNumP; i++)
        {
            mPlanets[i].createPlanet(i, mK, i == 0 ? 50 : mPlanets[i - 1].mDistance);
            mOrbits[i].setFillColor(sf::Color::Transparent);
            mOrbits[i].setOutlineColor(sf::Color(255, 255, 255, 100));
            mOrbits[i].setOutlineThickness (4);

            mOrbits[i].setRadius(mPlanets[i].mDistance);
            mOrbits[i].setPosition(300 - mPlanets[i].mDistance + this->mRadius * 8, 885 - mPlanets[i].mDistance + this->mRadius * 8);
        }
    }
