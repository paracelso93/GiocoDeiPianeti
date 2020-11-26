#ifndef STAR_H
#define STAR_H

#include "Planet.h"

class Star
{
    private:
        double K;
        
    public:
        int x, y;
        bool exists;
        float radius;
        float mass;
        std::string name;
        sf::CircleShape orbits[8];
        sf::Color color;
        sf::CircleShape shape;
        sf::CircleShape guiShape;
        Planet planets[8];
        int nump;
        bool hasDysonSphere;
        
        Star();
        virtual ~Star();

        void createStar(int x, int y);
};

#endif // STAR_H
