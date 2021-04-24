//
// Created by edoardo biasio on 2021-04-24.
//

#ifndef GIOCODEIPIANETI_SPACESHIPANALIZETAB_H
#define GIOCODEIPIANETI_SPACESHIPANALIZETAB_H

#include "Spaceship.h"
#include "GUI_Panel.h"
#include "GUI_Label.h"

class SpaceshipAnalizeTab {
private:
    static Spaceship* mShip;
    static sf::Font mFont;
    static GUI_Panel mPanel;
    static GUI_Label mTitle;
    static sf::Sprite mShipSprite;

public:
    static void setup(sf::Font& f, void (*close)());
    static void setShip(Spaceship* ship);
    static void render(sf::RenderWindow& window);
    static void getInput(sf::Vector2i mousePos);
};


#endif //GIOCODEIPIANETI_SPACESHIPANALIZETAB_H
