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
        static void render(sf::RenderWindow *window);
        static void getInput(sf::Vector2i mousePos);
        static void update(float dt);

        static void removeResearch(Research *r) {
            int i = 0;
            for(auto a : researches) {
                if(r->getName() == a->getName()) {
                    auto it = std::find(researches.begin(), researches.end(), a);
                    researches.erase(it);
                    auto it2 = std::find(labels.begin(), labels.end(), labels[i]);
                    labels.erase(it2);
                    auto it3 = std::find(buttons.begin(), buttons.end(), buttons[i]);
                    buttons.erase(it3);
                }
                i++;
            }
        }

        static void setEmpire(PlayerEmpire *e) {
            empire = e;
        }
        static void addResearch(Research *r) {
            researches.push_back(r);
            GUI_Label *l = new GUI_Label();
            l->setup(r->getName(), sf::Color::White, font, 20, {static_cast<float>((((int)(researches.size()) - 1) % 3) * 100 + 30), static_cast<float>(((int)researches.size() - 1) / 3) * 150.f + 260.f});
            labels.push_back(l);
            GUI_Button *d = new GUI_Button();
            //currentPlanet = p;
            sf::RectangleShape s;
            //empire = o;
            s.setSize({70, 70});
            s.setPosition(((((int)researches.size()) - 1) % 3) * 100 + 30, (((int)(researches.size()) - 1) / 3) * 150 + 200);
            d->setup(font, s,  sf::Color::Transparent, sf::Color::Transparent, " ", 1);
            buttons.push_back(d);
        }

        static void research() {
            researching = true;
            timer = currentResearch->getDifficulty();
            time = 0;
            //empty();
            removeResearch(currentResearch);
            bar.setup(20, 600, 360, 75, sf::Color::Black, sf::Color::Green, currentResearch->getDifficulty(), 0);
        }

        static void empty() {
            researches.clear();

            for(auto b : buttons) {
                delete b;
            }
            buttons.clear();

            for(auto l : labels) {
                delete l;
            }
            labels.clear();
        }

    private:   
        static std::vector<Research *> researches;
        static GUI_Panel panel;
        static GUI_Label title;
        static GUI_Label currentResearchLabel;
        static GUI_LoadingBar bar;
        static std::vector<GUI_Button *> buttons;
        static std::vector<GUI_Label *> labels;
        static Research *currentResearch;
        static bool researching;
        static int timer;
        static int time;

        static sf::Font font;
        static PlayerEmpire *empire;
};

#endif