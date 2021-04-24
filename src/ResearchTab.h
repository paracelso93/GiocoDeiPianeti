#ifndef RESEARCHTAB_H
#define RESEARCHTAB_H

#include <vector>

#include "GUI_Panel.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "GUI_LoadingBar.h"
#include "GUI_Alert.h"
#include "Constants.h"
#include "Research.h"


class ResearchTab {
    public:   
        static void setup(sf::Font f, void (*close)());
        static void render(sf::RenderWindow& window);
        static void getInput(sf::Vector2i mousePos);
        static void update(float dt);

        static void removeResearch(Research *r) {
            int i = 0;
            for(auto a : mResearches) {
                if(r->getName() == a->getName()) {
                    auto it = std::find(mResearches.begin(), mResearches.end(), a);
                    mResearches.erase(it);
                    auto it2 = std::find(mLabels.begin(), mLabels.end(), mLabels[i]);
                    mLabels.erase(it2);
                    auto it3 = std::find(mButtons.begin(), mButtons.end(), mButtons[i]);
                    mButtons.erase(it3);
                }
                i++;
            }
        }

        static void setEmpire(PlayerEmpire *e) {
            mEmpire = e;
        }
        static void addResearch(Research *r) {
            mResearches.push_back(r);
            GUI_Label *l = new GUI_Label();
            l->setup(r->getName(), sf::Color::White, mFont, 20, {static_cast<float>((((int)(mResearches.size()) - 1) % 3) * 100 + 30), static_cast<float>(((int)mResearches.size() - 1) / 3) * 150.f + 260.f});
            mLabels.push_back(l);
            GUI_Button *d = new GUI_Button();
            //currentPlanet = p;
            sf::RectangleShape s;
            //empire = o;
            s.setSize({70, 70});
            s.setPosition(((((int)mResearches.size()) - 1) % 3) * 100 + 30, (((int)(mResearches.size()) - 1) / 3) * 150 + 200);
            d->setup(mFont, s,  sf::Color::Transparent, sf::Color::Transparent, " ", 1);
            mButtons.push_back(d);
        }

        static void research() {
            mResearching = true;
            mTimer = mCurrentResearch->getDifficulty();
            mTime = 0;
            //empty();
            removeResearch(mCurrentResearch);
            mBar.setup(20, 600, 360, 75, sf::Color::Black, sf::Color::Green, mCurrentResearch->getDifficulty(), 0);
        }

        static void empty() {
            mResearches.clear();

            for(auto b : mButtons) {
                delete b;
            }
            mButtons.clear();

            for(auto l : mLabels) {
                delete l;
            }
            mLabels.clear();
        }

    private:   
        static std::vector<Research *> mResearches;
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static GUI_Label mCurrentResearchLabel;
        static GUI_LoadingBar mBar;
        static std::vector<GUI_Button *> mButtons;
        static std::vector<GUI_Label *> mLabels;
        static Research *mCurrentResearch;
        static bool mResearching;
        static int mTimer;
        static int mTime;

        static sf::Font mFont;
        static PlayerEmpire *mEmpire;
};

#endif