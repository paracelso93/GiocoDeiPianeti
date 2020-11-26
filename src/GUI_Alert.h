#ifndef GUI_ALERT_H___
#define GUI_ALERT_H___

#include "GUI_Label.h"
#include "GUI_Panel.h"
#include "GUI_Button.h"
#include "Constants.h"

class GUI_Alert {
    public:
        static bool visible;   
        static void close() {
            visible = false;
        }

        static void setup(sf::Color bgcolor, std::string title, std::string text, sf::Color textColor, int bNumber, sf::Color *buttonColors, std::string *buttonStrings, sf::Font f, void (*buttonFunctions[])());
        static void show() {
            visible = true;
        }
        static void render(sf::RenderWindow *window);
        static void getInput(sf::Vector2i mousePos);
    private:  
        static GUI_Panel background;
        static GUI_Label titleLabel;
        static GUI_Label textLabel;
        static sf::Font font;
        static int buttonNumber;
        static std::vector<GUI_Button *> buttons;
};

#endif