#ifndef EMPIRETAB_H
#define EMPIRETAB_H

#include "Empire.h"
#include "GUI_Panel.h"
#include "GUI_Label.h"

class EmpireTab {
    public:  
        static void setup(sf::Font f, void (*close)());
        static void render(sf::RenderWindow *window);
        static void getInput(sf::Vector2i mousePos);
        static void setEmpire(Empire *e);

    protected:   
        static GUI_Panel panel;
        static GUI_Label title;
        static Empire *currentEmpire;
        static sf::Font font;
        static sf::RectangleShape empireColor;
        static sf::Texture raceTex;
        static sf::Texture flagTex;
        static sf::Sprite raceSprite;
        static sf::Sprite flagSprite;
        static GUI_Label leaderLabel;
};

#endif