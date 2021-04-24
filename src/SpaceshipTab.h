#ifndef SPACESHIP_TAB_H
#define SPACESHIP_TAB_H

#include "GUI_Button.h"
#include "GUI_Panel.h"
#include "GUI_Label.h"
#include "Spaceship.h"
#include "Constants.h"

class SpaceshipTab {
    public:   
        static void setup(sf::Font f, void (*close)());
        static void empty();
        static void addSpaceship(Spaceship *s);
        static void render(sf::RenderWindow& window);
        static void getInput(sf::Vector2i mousePos);

    private: 
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static std::vector<Spaceship *> mShips;
        static std::vector<GUI_Label *> mShipLabels;
        static std::vector<GUI_Button *> mShipButtons;
        static sf::Font mFont;
};

#endif