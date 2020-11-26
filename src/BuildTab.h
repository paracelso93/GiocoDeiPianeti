#ifndef BUILDTAB_H
#define BUILDTAB_H

#include "GUI_Alert.h"
#include "Planet.h"
#include "PlayerEmpire.h"

class BuildTab {
    public:  
        static void setup(sf::Font f, void (*close)());
        
        static std::vector<Building* > buildings;
        static std::vector<GUI_Label* > buildingLabels;
        static std::vector<GUI_Button* > buildingButtons; 
        static void addBuilding(Building *b, Planet *p, PlayerEmpire *o) {
            buildings.push_back(b);
            GUI_Label *l = new GUI_Label();
            l->setup(b->name, sf::Color::White, font, 20, {static_cast<float>((((int)(buildings.size()) - 1) % 3) * 100 + 30), static_cast<float>(((int)buildings.size() - 1) / 3) * 150.f + 260.f});
            buildingLabels.push_back(l);
            GUI_Button *d = new GUI_Button();
            currentPlanet = p;
            sf::RectangleShape s;
            empire = o;
            s.setSize({70, 70});
            s.setPosition(((((int)buildings.size()) - 1) % 3) * 100 + 30, (((int)(buildings.size()) - 1) / 3) * 150 + 200);
            d->setup(font, s,  sf::Color::Transparent, sf::Color::Transparent, " ", 1);
            buildingButtons.push_back(d);
        }

        static void build() {
            if(empire->getFunds() >= currentBuilding->cost) {
                currentPlanet->buildings.push_back(currentBuilding);
                auto it = std::find(currentPlanet->availbleBuildings.begin(), currentPlanet->availbleBuildings.end(), currentBuilding);
                currentPlanet->availbleBuildings.erase(it);
                /*for(Building * b : currentPlanet->buildings) {
                    std::cout << b->name << ";";
                }

                std::cout << std::endl;*/

                empty();
                for(Building * b : currentPlanet->availbleBuildings) {
                    addBuilding(b, currentPlanet, empire);
                }
                empire->setFunds(empire->getFunds() - currentBuilding->cost);
            }
        }

        static void empty() {
            buildings.clear();

            for(auto l : buildingLabels) {
                delete l;
            }
            buildingLabels.clear();

            for(auto b : buildingButtons) {
                delete b;
            }
            buildingButtons.clear();
        }

        static void render(sf::RenderWindow *window);
        static void getInput(sf::Vector2i mousePos);

    private:   
        static GUI_Panel panel;
        static GUI_Label title;
        static Planet *currentPlanet;
        static Building *currentBuilding;
        static PlayerEmpire *empire;
        static sf::Font font;

};

#endif