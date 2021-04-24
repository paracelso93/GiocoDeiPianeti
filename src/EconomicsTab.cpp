#include "EconomicsTab.h"

GUI_Panel EconomicsTab::mPanel = GUI_Panel();
GUI_Label EconomicsTab::mTitle = GUI_Label();
GUI_Label EconomicsTab::mCashLabel = GUI_Label();
GUI_Label EconomicsTab::mIncomeLabel = GUI_Label();
GUI_Label EconomicsTab::mExpensesLabel = GUI_Label();
sf::Font EconomicsTab::mFont = sf::Font();

void EconomicsTab::setup(sf::Font f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("ECONOMY", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
    mCashLabel.setup("Bizcoin: 0", sf::Color::Yellow, mFont, 40, {10, 550});
    mIncomeLabel.setup("Income: 0", sf::Color::Green, mFont, 40, {10, 500});
    mExpensesLabel.setup("Expenses: 0", sf::Color::Red, mFont, 40, {10, 450});
}

void EconomicsTab::render(sf::RenderWindow& window) {
    mPanel.render(window);
    mTitle.render(window);
    mCashLabel.render(window);
    mIncomeLabel.render(window);
    mExpensesLabel.render(window);
}

void EconomicsTab::getInput(sf::Vector2i mousePos) {
    mPanel.getExit(mousePos);
}

void EconomicsTab::update(int cash, int income, int expenses) {
    mCashLabel.setString("Bizcoin: " + std::to_string(cash));
    mIncomeLabel.setString("Income: " + std::to_string(income));
    mExpensesLabel.setString("Expenses: " + std::to_string(expenses));
}