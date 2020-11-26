#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Star.h"
#include "TimeController.h"
#include "Helper.h"

enum class SpaceShipTypes {
    Scout, Researcher, War, Colonisation
};

class Spaceship {

    private:
        Star *currentStar;
        Planet *currentPlanet;
        int fuel;
        SpaceShipTypes type;
        int maxFuel;
        std::string name;
        bool travelling;
        float x, y;
        float worldx, worldy;
        float vx, vy;
        int cost;
        sf::Texture texture;
        sf::Texture borderTexture;
        sf::Sprite shipSprite;
        sf::Sprite borderShipSprite;
        
        
        int offset;
        sf::Vector2f target;
        sf::Vector2f battlePosition;
        float speed;

    public:  
        void setup(Star *startingStar, Planet *startingPlanet, int maxFuel, std::string name, float x, float y, std::string texturePath, SpaceShipTypes type, int offset, float speed, int cost);
        void render(sf::RenderWindow *window, Star *currentStar, bool isGUIVisible, sf::View view);
        void update();
        sf::Vector2f getBattlePosition() { return this->battlePosition; }
        void setBattlePosition(float x, float y) { this->battlePosition.x = x; this->battlePosition.y = y; this->battleSprite.setPosition(this->battlePosition); }
        void setupBattle(float x, float y);
        void renderBattle(sf::RenderWindow *window, bool border);
        //void renderBattle(sf::RenderWindow *window, sf::Shader *shader);
        void create(int maxFuel, std::string name, std::string texturePath, SpaceShipTypes type, float speed, int cost);
        void position(Star *star, Planet *planet, float x, float y, int offset);
        int getCost() { return this->cost; }
        int getOffset() { return this->offset; }
        void setOffset(int off) { this->offset = off; }
        SpaceShipTypes getType() { return this->type; }
        void setTarget(sf::Vector2f position);
        std::string getName() { return this->name; }
        Star *getStar() { return currentStar; }
        Planet *getPlanet() { return currentPlanet; }

        sf::Texture getTexture() { return this->texture; }
        sf::Sprite spaceSprite;
        sf::Sprite battleSprite;
        Spaceship() {}
        ~Spaceship() {}
};

#endif