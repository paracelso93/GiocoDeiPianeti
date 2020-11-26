#ifndef ECONOMICS_TAB_H
#define ECONOMICS_TAB_H

#include "GUI_Panel.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "Constants.h"


class EconomicsTab {
    private:  
        static GUI_Panel panel;
        static GUI_Label title;
        static GUI_Label cashLabel;
        static GUI_Label incomeLabel;
        static GUI_Label expensesLabel;
        static sf::Font font;

    public:   
        static void render(sf::RenderWindow *window);
        static void update(int cash, int income, int expenses);
        static void setup(sf::Font font, void (*close)());
        static void getInput(sf::Vector2i mousePos);
        
};


#endif