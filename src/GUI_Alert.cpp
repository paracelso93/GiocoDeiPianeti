#include "GUI_Alert.h"

bool GUI_Alert::mVisible = false;

GUI_Panel GUI_Alert::mBackground = GUI_Panel();
GUI_Label GUI_Alert::mTitleLabel = GUI_Label();
GUI_Label GUI_Alert::mTextLabel = GUI_Label();
sf::Font GUI_Alert::mFont = sf::Font();
int GUI_Alert::mButtonNumber = 0;
std::vector<GUI_Button *> GUI_Alert::mButtons = std::vector<GUI_Button *>();

void GUI_Alert::setup(sf::Color bgcolor, std::string title, std::string text, sf::Color textColor, int bNumber, sf::Color *buttonColors, std::string *buttonStrings, sf::Font f, void (*buttonFunctions[])()) {
    mFont = f;
    
    mBackground.setup({710, 390}, {500, 300}, bgcolor, sf::Color::Yellow, mFont, close);
    mTitleLabel.setup(title, textColor, mFont, 50, {static_cast<float>(710 + 250 - (title.length() / 2 - 1) * 50), 400});
    int len = 0;
    while(text[len] != '\n') {
        len++;
    }
    mTextLabel.setup(text, textColor, mFont, 20, {static_cast<float>(710 + 250 - (len / 2) * 15), 460});
    
    mVisible = false;
    mButtonNumber = bNumber;
    mButtons.clear();
    for(int i = 0; i < mButtonNumber; i++) {
        
        sf::RectangleShape s;
        GUI_Button* button = new GUI_Button();
        if(mButtonNumber % 2 == 0) {
            if(i < mButtonNumber / 2) {
                s.setPosition(710 + 250 - (mButtonNumber / 2 - i) * 100, 600);
            } else {
                s.setPosition(710 + 250 + (mButtonNumber / 2 - i) * 100, 600);
            }
        } else {
            if(i < (mButtonNumber - 1) / 2) {
                s.setPosition(710 + 250 - (mButtonNumber / 2 - i) * 100 - 40, 600);
            } else if(i > (mButtonNumber - 1) / 2) {
                s.setPosition(710 + 250 + (mButtonNumber / 2 - i) * 100 + 40, 600);
            } else {
                s.setPosition(710 + 250 - 40, 600);
            }
        }
        s.setSize({80, 50});
        button->setup(mFont, s, buttonColors[i], buttonColors[i], buttonStrings[i], 20);
        button->setFunction(buttonFunctions[i]);
        mButtons.push_back(button);
    }
}

void GUI_Alert::render(sf::RenderWindow& window) {
    if(mVisible) {
        mBackground.render(window);
        mTitleLabel.render(window);
        mTextLabel.render(window);
        for(auto b : mButtons) {
            b->render(window);
        }
    }
}

void GUI_Alert::getInput(sf::Vector2i mousePos) {
    mBackground.getExit(mousePos);
    for(int i = 0; i < mButtonNumber; i++) {
        if(mButtons[i]->checkForClick(mousePos)) {
            //std::cout << "click!" << std::endl;
            mButtons[i]->click();
            //std::cout << ((openTab == Tabs::none) ? "none" : "oops!") << std::endl;
        }
    }
}