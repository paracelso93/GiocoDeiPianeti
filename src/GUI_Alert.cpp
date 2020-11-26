#include "GUI_Alert.h"

bool GUI_Alert::visible = false;

GUI_Panel GUI_Alert::background = GUI_Panel();
GUI_Label GUI_Alert::titleLabel = GUI_Label();
GUI_Label GUI_Alert::textLabel = GUI_Label();
sf::Font GUI_Alert::font = sf::Font();
int GUI_Alert::buttonNumber = 0;
std::vector<GUI_Button *> GUI_Alert::buttons = std::vector<GUI_Button *>();

void GUI_Alert::setup(sf::Color bgcolor, std::string title, std::string text, sf::Color textColor, int bNumber, sf::Color *buttonColors, std::string *buttonStrings, sf::Font f, void (*buttonFunctions[])()) {
    font = f;
    
    background.setup({710, 390}, {500, 300}, bgcolor, sf::Color::Yellow, font, close);
    titleLabel.setup(title, textColor, font, 50, {static_cast<float>(710 + 250 - (title.length() / 2 - 1) * 50), 400});
    int len = 0;
    while(text[len] != '\n') {
        len++;
    }
    textLabel.setup(text, textColor, font, 20, {static_cast<float>(710 + 250 - (len / 2) * 15), 460});
    
    visible = false;
    buttonNumber = bNumber;
    buttons.clear();
    for(int i = 0; i < buttonNumber; i++) {
        
        sf::RectangleShape s;
        GUI_Button* button = new GUI_Button();
        if(buttonNumber % 2 == 0) {
            if(i < buttonNumber / 2) {
                s.setPosition(710 + 250 - (buttonNumber / 2 - i) * 100, 600);
            } else {
                s.setPosition(710 + 250 + (buttonNumber / 2 - i) * 100, 600);
            }
        } else {
            if(i < (buttonNumber - 1) / 2) {
                s.setPosition(710 + 250 - (buttonNumber / 2 - i) * 100 - 40, 600);
            } else if(i > (buttonNumber - 1) / 2) {
                s.setPosition(710 + 250 + (buttonNumber / 2 - i) * 100 + 40, 600);
            } else {
                s.setPosition(710 + 250 - 40, 600);
            }
        }
        s.setSize({80, 50});
        button->setup(font, s, buttonColors[i], buttonColors[i], buttonStrings[i], 20);
        button->setFunction(buttonFunctions[i]);
        buttons.push_back(button);
    }
}

void GUI_Alert::render(sf::RenderWindow *window) {
    if(visible) {
        background.render(window);
        titleLabel.render(window);
        textLabel.render(window);
        for(auto b : buttons) {
            b->render(window);
        }
    }
}

void GUI_Alert::getInput(sf::Vector2i mousePos) {
    background.getExit(mousePos);
    for(int i = 0; i < buttonNumber; i++) {
        if(buttons[i]->checkForClick(mousePos)) {
            //std::cout << "click!" << std::endl;
            buttons[i]->click();
            //std::cout << ((openTab == Tabs::none) ? "none" : "oops!") << std::endl;
        }
    }
}