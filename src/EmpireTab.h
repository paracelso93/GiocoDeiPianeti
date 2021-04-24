#ifndef EMPIRETAB_H
#define EMPIRETAB_H

#include "Empire.h"
#include "GUI_Panel.h"
#include "GUI_Label.h"

class EmpireTab {
    public:  
        static void setup(sf::Font f, void (*close)());
        static void render(sf::RenderWindow& window);
        static void getInput(sf::Vector2i mousePos);
        static void setEmpire(Empire *e);

    protected:   
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static Empire *mCurrentEmpire;
        static sf::Font mFont;
        static sf::RectangleShape mEmpireColor;
        static sf::Texture mRaceTex;
        static sf::Texture mFlagTex;
        static sf::Sprite mRaceSprite;
        static sf::Sprite mFlagSprite;
        static GUI_Label mLeaderLabel;
};

#endif