#ifndef DYSON_SPHERE_H
#define DYSON_SPHERE_H


#include "Star.h"

class DysonSphere {
    public:  
        DysonSphere() {}
        ~DysonSphere() {} 
        int getProduction() { return energyProduction; }
        void setup(Star *star, int energy);
        void setTexture(const std::string& filePath);
        static void render(sf::RenderWindow *window);
        
    private:   
        Star *star;
        static sf::Texture sphereTexture;
        static sf::Sprite sprite;
        int energyProduction;
};



#endif