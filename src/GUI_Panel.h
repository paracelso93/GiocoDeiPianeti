#ifndef GUI_PANEL_H
#define GUI_PANEL_H


#include "GUI_Button.h"

class GUI_Panel {
    private:  
        sf::RectangleShape mShape;
        static sf::Texture mExitTexture;
        sf::Sprite mExitSprite;
        static bool mTexLoaded;
        GUI_Button mCloseButton;
        sf::Font mFont;

    public:   
        void setup(sf::Vector2f position, sf::Vector2f size, sf::Color bgcolor, sf::Color edgeColor, sf::Font font, void (*close)());
        void render(sf::RenderWindow& window);
        void getExit(sf::Vector2i mousePos);
};

#endif