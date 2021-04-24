#ifndef BUILDTAB_H
#define BUILDTAB_H

#include "GUI_Alert.h"
#include "Planet.h"
#include "PlayerEmpire.h"

class BuildTab {
    public:  
        static void setup(sf::Font f, void (*close)());
        
        static std::vector<Building* > mBuildings;
        static std::vector<GUI_Label* > mBuildingLabels;
        static std::vector<GUI_Button* > mBuildingButtons;
        static void addBuilding(Building *b, Planet *p, PlayerEmpire *o) {
            mBuildings.push_back(b);
            GUI_Label *l = new GUI_Label();
            l->setup(b->mName, sf::Color::White, mFont, 20, {static_cast<float>((((int)(mBuildings.size()) - 1) % 3) * 100 + 30), static_cast<float>(((int)mBuildings.size() - 1) / 3) * 150.f + 260.f});
            mBuildingLabels.push_back(l);
            GUI_Button *d = new GUI_Button();
            mCurrentPlanet = p;
            sf::RectangleShape s;
            mEmpire = o;
            s.setSize({70, 70});
            s.setPosition(((((int)mBuildings.size()) - 1) % 3) * 100 + 30, (((int)(mBuildings.size()) - 1) / 3) * 150 + 200);
            d->setup(mFont, s,  sf::Color::Transparent, sf::Color::Transparent, " ", 1);
            mBuildingButtons.push_back(d);
        }

        static void build() {
            if(mEmpire->getFunds() >= mCurrentBuilding->mCost) {
                mCurrentPlanet->mBuildings.push_back(mCurrentBuilding);
                auto it = std::find(mCurrentPlanet->mAvailableBuildings.begin(), mCurrentPlanet->mAvailableBuildings.end(), mCurrentBuilding);
                mCurrentPlanet->mAvailableBuildings.erase(it);
                /*for(Building * b : currentPlanet->buildings) {
                    std::cout << b->name << ";";
                }

                std::cout << std::endl;*/

                empty();
                for(Building * b : mCurrentPlanet->mAvailableBuildings) {
                    addBuilding(b, mCurrentPlanet, mEmpire);
                }
                mEmpire->setFunds(mEmpire->getFunds() - mCurrentBuilding->mCost);
            }
        }

        static void empty() {
            mBuildings.clear();

            for(auto l : mBuildingLabels) {
                delete l;
            }
            mBuildingLabels.clear();

            for(auto b : mBuildingButtons) {
                delete b;
            }
            mBuildingButtons.clear();
        }

        static void render(sf::RenderWindow& window);
        static void getInput(sf::Vector2i mousePos);

    private:   
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static Planet *mCurrentPlanet;
        static Building *mCurrentBuilding;
        static PlayerEmpire *mEmpire;
        static sf::Font mFont;

};

#endif