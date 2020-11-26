#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <SFML/Graphics.hpp>

#include <cstring>


class GUI_Button
{
    private:
        sf::RectangleShape shape;
        sf::Color onClickColor;
        sf::Color color;
        std::string content;
        sf::Font font;
        bool isClicked;
        sf::Text text;
        bool hasSprite;
        sf::Sprite sprite;
        sf::Texture tex;
        void (*f)();

    public:
        GUI_Button();
        virtual ~GUI_Button();


        void addImage(std::string path);
        void setup(sf::Font f, sf::RectangleShape shape = sf::RectangleShape({200, 80}),  sf::Color color = sf::Color(128, 137, 150), sf::Color onClick = sf::Color(93, 99, 107), std::string content = "", int charSize = 40);
        void deselect();
        bool checkForClick(sf::Vector2i mousePos);
        bool isClick();
        void setFunction(void (*function)());
        void click();
        void render(sf::RenderWindow *window);
};

#endif // GUI_BUTTON_H
