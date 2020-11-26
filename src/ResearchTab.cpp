#include "ResearchTab.h"

sf::Font ResearchTab::font = sf::Font();
GUI_Panel ResearchTab::panel = GUI_Panel();
GUI_Label ResearchTab::title = GUI_Label();
GUI_LoadingBar ResearchTab::bar = GUI_LoadingBar();
GUI_Label ResearchTab::currentResearchLabel = GUI_Label();
PlayerEmpire *ResearchTab::empire = nullptr;
std::vector<Research *> ResearchTab::researches = std::vector<Research *>();
std::vector<GUI_Button *> ResearchTab::buttons = std::vector<GUI_Button *>();
std::vector<GUI_Label *> ResearchTab::labels = std::vector<GUI_Label *>();
Research *ResearchTab::currentResearch = nullptr;
bool ResearchTab::researching = false;
int ResearchTab::timer = 0;
int ResearchTab::time = 0;

void ResearchTab::setup(sf::Font f, void (*close)()) {
    font = f;
    panel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, font, close);
    title.setup("RESEARCH", sf::Color::White, font, 50, {15, constants::UPPERGUIHEIGHT + 15});
    currentResearchLabel.setup("Current Research Progress: ", sf::Color::White, font, 20, {5, 550});
}

void ResearchTab::update(float dt) {
    if(researching) {
        bar.update(dt);
        if(bar.completed) {
            // dood
        }
    }
}

void ResearchTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto b : buttons) {
        if(b->checkForClick(mousePos)) {
            currentResearch = researches[i];
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            //currentBuilding = buildings[k];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                research();
                GUI_Alert::visible = false;
                //std::cout << "Close!" << std::endl;
                
            }, [] (){ GUI_Alert::visible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, researches[i]->getName(), "Are you shure you want\n to research this research, it will take you " + std::to_string(researches[i]->getDifficulty()) + " Ticks to complete." , sf::Color::White, 2, colors, strings, font, buttonFunctions);
            GUI_Alert::show();
        }
        i++;
    }

    panel.getExit(mousePos);
}

void ResearchTab::render(sf::RenderWindow *window) {
    panel.render(window);
    title.render(window);
    currentResearchLabel.render(window);
    bar.render(window);
    int index = 0;
    for(auto e : researches) {
        e->spr.setPosition((index % 3) * 100 + 30, index / 3 * 150 + 200);
        window->draw(e->spr);
        index++;
    }

    for(auto e : labels) {
        e->render(window);
    }
}