#include "EconomicsTab.h"

GUI_Panel EconomicsTab::panel = GUI_Panel();
GUI_Label EconomicsTab::title = GUI_Label();
GUI_Label EconomicsTab::cashLabel = GUI_Label();
GUI_Label EconomicsTab::incomeLabel = GUI_Label();
GUI_Label EconomicsTab::expensesLabel = GUI_Label();
sf::Font EconomicsTab::font = sf::Font();

void EconomicsTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("ECONOMY", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
    cashLabel.setup("Bizcoin: 0", sf::Color::Yellow, font, 40, {10, 550});
    incomeLabel.setup("Income: 0", sf::Color::Green, font, 40, {10, 500});
    expensesLabel.setup("Expenses: 0", sf::Color::Red, font, 40, {10, 450});
}

void EconomicsTab::render(sf::RenderWindow *window) {
    panel.render(window);
    title.render(window);
    cashLabel.render(window);
    incomeLabel.render(window);
    expensesLabel.render(window);
}

void EconomicsTab::getInput(sf::Vector2i mousePos) {
    panel.getExit(mousePos);
}

void EconomicsTab::update(int cash, int income, int expenses) {
    cashLabel.setString("Bizcoin: " + std::to_string(cash));
    incomeLabel.setString("Income: " + std::to_string(income));
    expensesLabel.setString("Expenses: " + std::to_string(expenses));
}