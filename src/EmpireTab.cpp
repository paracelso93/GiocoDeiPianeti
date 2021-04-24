#include "EmpireTab.h"

GUI_Panel EmpireTab::mPanel = GUI_Panel();
GUI_Label EmpireTab::mTitle = GUI_Label();
Empire *EmpireTab::mCurrentEmpire = nullptr;
sf::RectangleShape EmpireTab::mEmpireColor = sf::RectangleShape();
sf::Texture EmpireTab::mRaceTex = sf::Texture();
sf::Texture EmpireTab::mFlagTex = sf::Texture();
sf::Sprite EmpireTab::mRaceSprite = sf::Sprite();
sf::Sprite EmpireTab::mFlagSprite = sf::Sprite();
sf::Font EmpireTab::mFont = sf::Font();
GUI_Label EmpireTab::mLeaderLabel = GUI_Label();


void EmpireTab::setup(sf::Font f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("EMPIRE", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
    mEmpireColor.setPosition({15, constants::UPPERGUIHEIGHT + 70});
    mEmpireColor.setSize({50, 50});
    mEmpireColor.setFillColor(sf::Color::White);
    mRaceSprite.setPosition({80, constants::UPPERGUIHEIGHT + 70});
    mLeaderLabel.setup("LEADER", sf::Color::White, mFont, 20, {40, constants::UPPERGUIHEIGHT + 280});
    mFlagSprite.setPosition({15, constants::UPPERGUIHEIGHT + 350});
}

void EmpireTab::setEmpire(Empire *e) {
    mCurrentEmpire = e;
    mTitle.setString(e->getName());
    mEmpireColor.setFillColor(e->getEmpireColor());
    mRaceTex.loadFromFile(e->getRace());
    mFlagTex.loadFromFile(e->getFlag());
    mRaceSprite.setTexture(mRaceTex);
    mFlagSprite.setTexture(mFlagTex);
    mLeaderLabel.setString(e->getLeaderName());
}

void EmpireTab::getInput(sf::Vector2i mousePos) {
    mPanel.getExit(mousePos);
}

void EmpireTab::render(sf::RenderWindow& window) {
    mPanel.render(window);
    mTitle.render(window);
    window.draw(mFlagSprite);
    window.draw(mRaceSprite);
    window.draw(mEmpireColor);
    mLeaderLabel.render(window);
}