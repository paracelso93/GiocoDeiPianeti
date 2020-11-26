#include "BuildTab.h"

Planet *BuildTab::currentPlanet = nullptr;
Building *BuildTab::currentBuilding = nullptr;
PlayerEmpire *BuildTab::empire = nullptr;
std::vector<Building* > BuildTab::buildings = std::vector<Building* >();
std::vector<GUI_Label* > BuildTab::buildingLabels = std::vector<GUI_Label* >();
std::vector<GUI_Button* > BuildTab::buildingButtons = std::vector<GUI_Button* >(); 
GUI_Panel BuildTab::panel = GUI_Panel();
GUI_Label BuildTab::title = GUI_Label();
sf::Font BuildTab::font = sf::Font();


void BuildTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("BUILDINGS", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
}

void BuildTab::render(sf::RenderWindow *window) {
    panel.render(window);
    title.render(window);

    for(auto e : buildingLabels) {
        e->render(window);
    }
    int i = 0;
    for(auto e : buildings) {
        e->render(window, (i % 3) * 100 + 30, i / 3 * 150 + 200);
        i++;
    }
}

void BuildTab::getInput(sf::Vector2i mousePos) {
    panel.getExit(mousePos);

    int k = 0;
    for(auto e : buildingButtons) {
        if(e->checkForClick(mousePos)) {
            
            //this->empty();
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            currentBuilding = buildings[k];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                build();
                GUI_Alert::visible = false;
                //std::cout << "Close!" << std::endl;
                
            }, [] (){ GUI_Alert::visible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, buildings[k]->name, "Are you shure you want\n to build this building?", sf::Color::White, 2, colors, strings, font, buttonFunctions);
            GUI_Alert::show();
            
        }
        k++;
    }
}