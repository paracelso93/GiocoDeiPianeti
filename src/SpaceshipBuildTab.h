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
        static void setup(sf::Font f, void (*close)());
        static void empty();
        static void addSpaceship(Spaceship *s, Star *t, Planet *p, int off);
        static void render(sf::RenderWindow *window);
        static void getInput(sf::Vector2i mousePos);
        static void setEmpire(PlayerEmpire *e) { empire = e; }

    private: 
        static void build() {
            //std::cout << empire->getFunds() << std::endl;
            if(empire->getFunds() >= currentShip->getCost()) {
                currentShip->setOffset(offset);
                offset += 40;
                empire->buildShip(currentShip);
                //std::cout << currentShip->getOffset() << std::endl;
                SpaceshipTab::addSpaceship(currentShip);
                //std::cout << currentShip->getName() << std::endl;

                auto it = std::find(empire->availbleShips.begin(), empire->availbleShips.end(), currentShip);
                empire->availbleShips.erase(it);
                //std::cout << "JOEMAMA" << std::endl;
                /*for(Building * b : currentPlanet->buildings) {
                    std::cout << b->name << ";";
                }

                std::cout << std::endl;*/
                empty();
                int i = 0;
                for(Spaceship * b : empire->availbleShips) {
                    addSpaceship(b, b->getStar(), b->getPlanet(), i * 40);
                    // TODO: fix i * 40 because spaceships change index
                    i++;
                }
                
                empire->setFunds(empire->getFunds() - currentShip->getCost());
            }
        }
        
        static GUI_Panel panel;
        static GUI_Label title;
        static std::vector<Spaceship *> ships;
        static std::vector<GUI_Label *> shipLabels;
        static std::vector<GUI_Button *> shipButtons;
        static sf::Font font;
        static Spaceship *currentShip;
        static PlayerEmpire *empire;
        static int offset;
};

#endif