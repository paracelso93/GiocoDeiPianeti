#include "SpaceshipTab.h"

GUI_Panel SpaceshipTab::mPanel = GUI_Panel();
GUI_Label SpaceshipTab::mTitle = GUI_Label();
std::vector<Spaceship *> SpaceshipTab::mShips = std::vector<Spaceship *>();
std::vector<GUI_Label *> SpaceshipTab::mShipLabels = std::vector<GUI_Label *>();
std::vector<GUI_Button *> SpaceshipTab::mShipButtons = std::vector<GUI_Button *>();
sf::Font SpaceshipTab::mFont;

void SpaceshipTab::setup(sf::Font f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("SPACESHIPS", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void SpaceshipTab::render(sf::RenderWindow& window) {
    mPanel.render(window);
    mTitle.render(window);
    for(auto e : mShipLabels) {
        e->render(window);
    }
    int i = 0;
    for(auto e : mShips) {
        sf::Sprite s = e->mSpaceSprite;
        s.setPosition((i % 3) * 100 + 30, i / 3 * 150 + 200);
        window.draw(s);
        i++;
    }
}

void SpaceshipTab::empty() {
    mShips.clear();

    for(auto l : mShipLabels) {
        delete l;
    }
    mShipLabels.clear();

    for(auto b : mShipButtons) {
        delete b;
    }
    mShipButtons.clear();
}
void SpaceshipTab::addSpaceship(Spaceship *s) {
    mShips.push_back(s);
    GUI_Label *l = new GUI_Label();
    l->setup(s->getName(), sf::Color::White, mFont, 12, {static_cast<float>((((int)(mShips.size()) - 1) % 3) * 100 + 5), static_cast<float>(((int)mShips.size() - 1) / 3) * 150.f + 260.f});
    mShipLabels.push_back(l);
    GUI_Button *b = new GUI_Button();
    sf::RectangleShape t;
    t.setSize({70, 70});
    t.setPosition(((((int)mShips.size()) - 1) % 3) * 100 + 30, (((int)(mShips.size()) - 1) / 3) * 150 + 200);
    b->setup(mFont, t, sf::Color::Transparent, sf::Color::Transparent, " ", 1);
    mShipButtons.push_back(b);
}

void SpaceshipTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto e : mShipButtons) {
        if(e->checkForClick(mousePos)) {
            std::cout << "Selected: " << mShips[i]->getName() << std::endl;
        }
        i++;
    }
    mPanel.getExit(mousePos);
}
