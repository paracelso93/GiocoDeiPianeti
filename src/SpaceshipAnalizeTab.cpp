//
// Created by edoardo biasio on 2021-04-24.
//

#include "SpaceshipAnalizeTab.h"

Spaceship* SpaceshipAnalizeTab::mShip = nullptr;
GUI_Panel SpaceshipAnalizeTab::mPanel = GUI_Panel();
GUI_Label SpaceshipAnalizeTab::mTitle = GUI_Label();
sf::Font SpaceshipAnalizeTab::mFont = sf::Font();
sf::Sprite SpaceshipAnalizeTab::mShipSprite = sf::Sprite();

void SpaceshipAnalizeTab::setup(sf::Font& f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {800, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("ANALISE SHIPS", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
    mShipSprite.setPosition(100, 100);
}

void SpaceshipAnalizeTab::setShip(Spaceship* ship) {
    mShip = ship;
    mShipSprite.setTexture(mShip->getTexture());
}

void SpaceshipAnalizeTab::getInput(sf::Vector2i mousePos) {
    mPanel.getExit(mousePos);
}

void SpaceshipAnalizeTab::render(sf::RenderWindow& window) {

    mPanel.render(window);
    mTitle.render(window);
    if (mShip != nullptr)
        window.draw(mShipSprite);
}