#include "SpaceshipBuildTab.h"

GUI_Panel SpaceshipBuildTab::mPanel = GUI_Panel();
GUI_Label SpaceshipBuildTab::mTitle = GUI_Label();
std::vector<Spaceship *> SpaceshipBuildTab::mShips = std::vector<Spaceship *>();
std::vector<GUI_Label *> SpaceshipBuildTab::mShipLabels = std::vector<GUI_Label *>();
std::vector<GUI_Button *> SpaceshipBuildTab::mShipButtons = std::vector<GUI_Button *>();
sf::Font SpaceshipBuildTab::mFont = sf::Font();
Spaceship *SpaceshipBuildTab::mCurrentShip = nullptr;
PlayerEmpire *SpaceshipBuildTab::mEmpire = nullptr;
int SpaceshipBuildTab::mOffset = 0;

void SpaceshipBuildTab::setup(sf::Font& f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("BUILD SHIPS", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void SpaceshipBuildTab::render(sf::RenderWindow& window) {
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

void SpaceshipBuildTab::empty() {
    mShips.clear();

    for(auto l : mShipLabels) {
        delete l;
    }
    mShipLabels.clear();

    for(auto s : mShipButtons) {
        delete s;
    }
    mShipButtons.clear();
}
void SpaceshipBuildTab::addSpaceship(Spaceship *s, Star *t, Planet *p, int off) {
    s->position(t, p, 0, 0, off);

    mShips.push_back(s);
    //std::cout << s->getOffset() << std::endl;
    GUI_Label *l = new GUI_Label();
    l->setup(s->getName(), sf::Color::White, mFont, 12, {static_cast<float>((((int)(mShips.size()) - 1) % 3) * 100 + 5), static_cast<float>(((int)mShips.size() - 1) / 3) * 150.f + 260.f});
    mShipLabels.push_back(l);
    GUI_Button *b = new GUI_Button();
    sf::RectangleShape o;
    o.setSize({70, 70});
    o.setPosition(((((int)mShips.size()) - 1) % 3) * 100 + 30, (((int)(mShips.size()) - 1) / 3) * 150 + 200);
    b->setup(mFont, o, sf::Color::Transparent, sf::Color::Transparent, " ", 1);
    mShipButtons.push_back(b);
}

void SpaceshipBuildTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto e : mShipButtons) {
        if(e->checkForClick(mousePos)) {
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            mCurrentShip = mShips[i];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                build();
                GUI_Alert::mVisible = false;
                //std::cout << "Close!" << std::endl;
            }, [] (){ GUI_Alert::mVisible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, mShips[i]->getName(), "Are you shure you want\n to create this ship?", sf::Color::White, 2, colors, strings, mFont, buttonFunctions);
            GUI_Alert::show();
        }
        i++;
    }
    mPanel.getExit(mousePos);
}
