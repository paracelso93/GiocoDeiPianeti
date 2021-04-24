#ifndef ECONOMICS_TAB_H
#define ECONOMICS_TAB_H

#include "GUI_Panel.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "Constants.h"


class EconomicsTab {
    private:  
        static GUI_Panel mPanel;
        static GUI_Label mTitle;
        static GUI_Label mCashLabel;
        static GUI_Label mIncomeLabel;
        static GUI_Label mExpensesLabel;
        static sf::Font mFont;

    public:   
        static void render(sf::RenderWindow& window);
        static void update(int cash, int income, int expenses);
        static void setup(sf::Font font, void (*close)());
        static void getInput(sf::Vector2i mousePos);
        
};


#endif