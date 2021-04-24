#include "BuildTab.h"

Planet *BuildTab::mCurrentPlanet = nullptr;
Building *BuildTab::mCurrentBuilding = nullptr;
PlayerEmpire *BuildTab::mEmpire = nullptr;
std::vector<Building* > BuildTab::mBuildings = std::vector<Building* >();
std::vector<GUI_Label* > BuildTab::mBuildingLabels = std::vector<GUI_Label* >();
std::vector<GUI_Button* > BuildTab::mBuildingButtons = std::vector<GUI_Button* >();
GUI_Panel BuildTab::mPanel = GUI_Panel();
GUI_Label BuildTab::mTitle = GUI_Label();
sf::Font BuildTab::mFont = sf::Font();


void BuildTab::setup(sf::Font f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("BUILDINGS", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void BuildTab::render(sf::RenderWindow& window) {
    mPanel.render(window);
    mTitle.render(window);

    for(auto e : mBuildingLabels) {
        e->render(window);
    }
    int i = 0;
    for(auto e : mBuildings) {
        e->render(window, (i % 3) * 100 + 30, i / 3 * 150 + 200);
        i++;
    }
}

void BuildTab::getInput(sf::Vector2i mousePos) {
    mPanel.getExit(mousePos);

    int k = 0;
    for(auto e : mBuildingButtons) {
        if(e->checkForClick(mousePos)) {
            
            //this->empty();
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            mCurrentBuilding = mBuildings[k];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                build();
                GUI_Alert::mVisible = false;
                //std::cout << "Close!" << std::endl;
                
            }, [] (){ GUI_Alert::mVisible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, mBuildings[k]->mName, "Are you shure you want\n to build this building?", sf::Color::White, 2, colors, strings, mFont, buttonFunctions);
            GUI_Alert::show();
            
        }
        k++;
    }
}