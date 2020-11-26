#include "SpaceshipTab.h"

GUI_Panel SpaceshipTab::panel = GUI_Panel();
GUI_Label SpaceshipTab::title = GUI_Label();
std::vector<Spaceship *> SpaceshipTab::ships = std::vector<Spaceship *>();
std::vector<GUI_Label *> SpaceshipTab::shipLabels = std::vector<GUI_Label *>();
std::vector<GUI_Button *> SpaceshipTab::shipButtons = std::vector<GUI_Button *>();
sf::Font SpaceshipTab::font;

void SpaceshipTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("SPACESHIPS", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void SpaceshipTab::render(sf::RenderWindow *window) {
    panel.render(window);
    title.render(window);
    for(auto e : shipLabels) {
        e->render(window);
    }
    int i = 0;
    for(auto e : ships) {
        sf::Sprite s = e->spaceSprite;
        s.setPosition((i % 3) * 100 + 30, i / 3 * 150 + 200);
        window->draw(s);
        i++;
    }
}

void SpaceshipTab::empty() {
    ships.clear();

    for(auto l : shipLabels) {
        delete l;
    }
    shipLabels.clear();

    for(auto b : shipButtons) {
        delete b;
    }
    shipButtons.clear();
}
void SpaceshipTab::addSpaceship(Spaceship *s) {
    ships.push_back(s);
    GUI_Label *l = new GUI_Label();
    l->setup(s->getName(), sf::Color::White, font, 12, {static_cast<float>((((int)(ships.size()) - 1) % 3) * 100 + 5), static_cast<float>(((int)ships.size() - 1) / 3) * 150.f + 260.f});
    shipLabels.push_back(l);
    GUI_Button *b = new GUI_Button();
    sf::RectangleShape t;
    t.setSize({70, 70});
    t.setPosition(((((int)ships.size()) - 1) % 3) * 100 + 30, (((int)(ships.size()) - 1) / 3) * 150 + 200);
    b->setup(font, t, sf::Color::Transparent, sf::Color::Transparent, " ", 1);
    shipButtons.push_back(b);
}

void SpaceshipTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto e : shipButtons) {
        if(e->checkForClick(mousePos)) {
            std::cout << "Selected: " << ships[i]->getName() << std::endl;
        }
        i++;
    }
    panel.getExit(mousePos);
}
