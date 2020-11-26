#include "SpaceshipBuildTab.h"

GUI_Panel SpaceshipBuildTab::panel = GUI_Panel();
GUI_Label SpaceshipBuildTab::title = GUI_Label();
std::vector<Spaceship *> SpaceshipBuildTab::ships = std::vector<Spaceship *>();
std::vector<GUI_Label *> SpaceshipBuildTab::shipLabels = std::vector<GUI_Label *>();
std::vector<GUI_Button *> SpaceshipBuildTab::shipButtons = std::vector<GUI_Button *>();
sf::Font SpaceshipBuildTab::font = sf::Font();
Spaceship *SpaceshipBuildTab::currentShip = nullptr;
PlayerEmpire *SpaceshipBuildTab::empire = nullptr;
int SpaceshipBuildTab::offset = 0;

void SpaceshipBuildTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("BUILD SHIPS", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void SpaceshipBuildTab::render(sf::RenderWindow *window) {
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

void SpaceshipBuildTab::empty() {
    ships.clear();

    for(auto l : shipLabels) {
        delete l;
    }
    shipLabels.clear();

    for(auto s : shipButtons) {
        delete s;
    }
    shipButtons.clear();
}
void SpaceshipBuildTab::addSpaceship(Spaceship *s, Star *t, Planet *p, int off) {
    s->position(t, p, 0, 0, off);
    
    ships.push_back(s);
    //std::cout << s->getOffset() << std::endl;
    GUI_Label *l = new GUI_Label();
    l->setup(s->getName(), sf::Color::White, font, 12, {static_cast<float>((((int)(ships.size()) - 1) % 3) * 100 + 5), static_cast<float>(((int)ships.size() - 1) / 3) * 150.f + 260.f});
    shipLabels.push_back(l);
    GUI_Button *b = new GUI_Button();
    sf::RectangleShape o;
    o.setSize({70, 70});
    o.setPosition(((((int)ships.size()) - 1) % 3) * 100 + 30, (((int)(ships.size()) - 1) / 3) * 150 + 200);
    b->setup(font, o, sf::Color::Transparent, sf::Color::Transparent, " ", 1);
    shipButtons.push_back(b);
}

void SpaceshipBuildTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto e : shipButtons) {
        if(e->checkForClick(mousePos)) {
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            currentShip = ships[i];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                build();
                GUI_Alert::visible = false;
                //std::cout << "Close!" << std::endl;
            }, [] (){ GUI_Alert::visible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, ships[i]->getName(), "Are you shure you want\n to create this ship?", sf::Color::White, 2, colors, strings, font, buttonFunctions);
            GUI_Alert::show();
        }
        i++;
    }
    panel.getExit(mousePos);
}
