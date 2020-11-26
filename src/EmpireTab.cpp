#include "EmpireTab.h"

GUI_Panel EmpireTab::panel = GUI_Panel();
GUI_Label EmpireTab::title = GUI_Label();
Empire *EmpireTab::currentEmpire = nullptr;
sf::RectangleShape EmpireTab::empireColor = sf::RectangleShape();
sf::Texture EmpireTab::raceTex = sf::Texture();
sf::Texture EmpireTab::flagTex = sf::Texture();
sf::Sprite EmpireTab::raceSprite = sf::Sprite();
sf::Sprite EmpireTab::flagSprite = sf::Sprite();
sf::Font EmpireTab::font = sf::Font();
GUI_Label EmpireTab::leaderLabel = GUI_Label();


void EmpireTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("EMPIRE", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
    empireColor.setPosition({15, constants::UPPERGUIHEIGHT + 70});
    empireColor.setSize({50, 50});
    empireColor.setFillColor(sf::Color::White);
    raceSprite.setPosition({80, constants::UPPERGUIHEIGHT + 70});
    leaderLabel.setup("LEADER", sf::Color::White, font, 20, {40, constants::UPPERGUIHEIGHT + 280});
    flagSprite.setPosition({15, constants::UPPERGUIHEIGHT + 350});
}

void EmpireTab::setEmpire(Empire *e) {
    currentEmpire = e;
    title.setString(e->getName());
    empireColor.setFillColor(e->getEmpireColor());
    raceTex.loadFromFile(e->getRace());
    flagTex.loadFromFile(e->getFlag());
    raceSprite.setTexture(raceTex);
    flagSprite.setTexture(flagTex);
    leaderLabel.setString(e->getLeaderName());
}

void EmpireTab::getInput(sf::Vector2i mousePos) {
    panel.getExit(mousePos);
}

void EmpireTab::render(sf::RenderWindow *window) {
    panel.render(window);
    title.render(window);
    window->draw(flagSprite);
    window->draw(raceSprite);
    window->draw(empireColor);
    leaderLabel.render(window);
}