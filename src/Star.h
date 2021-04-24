#ifndef STAR_H
#define STAR_H

#include "Planet.h"

class Star
{
    private:
        double mK;
        
    public:
        int mX, mY;
        bool mExists;
        float mRadius;
        float mMass;
        std::string mName;
        sf::CircleShape mOrbits[8];
        sf::Color mColor;
        sf::CircleShape mShape;
        sf::CircleShape mGuiShape;
        Planet mPlanets[8];
        int mNumP;
        bool mHasDysonSphere;
        
        Star();
        virtual ~Star();

        void createStar(int x, int y);
};

#endif // STAR_H
