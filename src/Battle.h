#ifndef BATTLE_H
#define BATTLE_H

#include "Spaceship.h"
#include "AStar.h"
#include <vector>
#include "BattleMap.h"

class Battle {
    private:  
        BattleMap *map;
        int side1ID, side2ID;
        std::vector<Spaceship *> side1Spaceships, side2Spaceships;
        //sf::Shader outline;
        int selectedShipIndex;
        bool selected;
    public:  
        void setup(int ID1, int ID2);
        void setSpaceship(int ID, Spaceship *spaceship);
        void render(sf::RenderWindow *window);
        void setMap(BattleMap *map);
        void getInput(sf::Vector2i mousePos);
        void generateBattlePositions(int ID1, int ID2);
};

#endif