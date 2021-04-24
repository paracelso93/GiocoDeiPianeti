#ifndef BATTLE_H
#define BATTLE_H

#include "Spaceship.h"
#include "AStar.h"
#include <vector>
#include "BattleMap.h"

class Battle {
    private:  
        BattleMap *mMap;
        int mSide1ID, mSide2ID;
        std::vector<Spaceship *> mSide1Spaceships, mSide2Spaceships;
        //sf::Shader outline;
        int mSelectedShipIndex;
        bool mSelected;
    public:  
        void setup(int ID1, int ID2);
        void setSpaceship(int ID, Spaceship *spaceship);
        void render(sf::RenderWindow& window);
        void setMap(BattleMap *map);
        void getInput(sf::Vector2i mousePos);
        void generateBattlePositions(int ID1, int ID2);
};

#endif