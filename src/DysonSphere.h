#ifndef DYSON_SPHERE_H
#define DYSON_SPHERE_H


#include "Star.h"

class DysonSphere {
    public:  
        DysonSphere() {}
        ~DysonSphere() {} 
        int getProduction() { return mEnergyProduction; }
        void setup(Star *star, int energy);
        void setTexture(const std::string& filePath);
        static void render(sf::RenderWindow& window);
        
    private:   
        Star *mStar;
        static sf::Texture mSphereTexture;
        static sf::Sprite mSprite;
        int mEnergyProduction;
};



#endif