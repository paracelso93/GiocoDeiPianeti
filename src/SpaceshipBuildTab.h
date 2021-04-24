#ifndef SPACESHIPBUILDTAB_H
#define SPACESHIPBUILDTAB_H

#include "Spaceship.h"
#include "GUI_Panel.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "GUI_Alert.h"
#include "PlayerEmpire.h"
#include "SpaceshipTab.h"

class SpaceshipBuildTab {
    public:   
        static void setup(sf::Font& f, void (*close)());
        static void empty();
        static void addSpaceship(Spaceship *s, Star *t, Planet *p, int off);
        static void render(sf::RenderWindow& window);
        static void getInput(sf::Vector2i mousePos);
        static void setEmpire(PlayerEmpire *e) { mEmpire = e; }

    private: 
        static void build() {
            //std::cout << empire->getFunds() << std::endl;
            if(mEmpire->getFunds() >= mCurrentShip->getCost()) {
                mCurrentShip->setOffset(mOffset);
                mOffset += 40;
                mEmpire->buildShip(mCurrentShip);
                //std::cout << currentShip->getOffset() << std::endl;
                SpaceshipTab::addSpaceship(mCurrentShip);
                //std::cout << currentShip->getName() << std::endl;

                auto it = std::find(mEmpire->mAvailableShips.begin(), mEmpire->mAvailableShips.end(), mCurrentShip);
                mEmpire->mAvailableShips.erase(it);
                //std::cout << "JOEMAMA" << std::endl;
                /*for(Building * b : currentPlanet->buildings) {
                    std::cout << b->name << ";";
                }

                std::cout << std::endl;*/
                empty();
                int i = 0;
                for(Spaceship * b : mEmpire->mAvailableShips) {
                    addSpaceship(b, b->getStar(), b->getPlanet(), i * 40);
                    // TODO: fix i * 40 because spaceships change index
                    i++;
                }
                
                mEmpire->setFunds(mEmpire->getFunds() - mCurrentShip->getCost());
            }
        }
        
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static std::vector<Spaceship *> mShips;
        static std::vector<GUI_Label *> mShipLabels;
        static std::vector<GUI_Button *> mShipButtons;
        static sf::Font mFont;
        static Spaceship *mCurrentShip;
        static PlayerEmpire *mEmpire;
        static int mOffset;
};

#endif