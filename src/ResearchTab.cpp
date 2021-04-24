#include "ResearchTab.h"

sf::Font ResearchTab::mFont = sf::Font();
GUI_Panel ResearchTab::mPanel = GUI_Panel();
GUI_Label ResearchTab::mTitle = GUI_Label();
GUI_LoadingBar ResearchTab::mBar = GUI_LoadingBar();
GUI_Label ResearchTab::mCurrentResearchLabel = GUI_Label();
PlayerEmpire *ResearchTab::mEmpire = nullptr;
std::vector<Research *> ResearchTab::mResearches = std::vector<Research *>();
std::vector<GUI_Button *> ResearchTab::mButtons = std::vector<GUI_Button *>();
std::vector<GUI_Label *> ResearchTab::mLabels = std::vector<GUI_Label *>();
Research *ResearchTab::mCurrentResearch = nullptr;
bool ResearchTab::mResearching = false;
int ResearchTab::mTimer = 0;
int ResearchTab::mTime = 0;

void ResearchTab::setup(sf::Font f, void (*close)()) {
    mFont = f;
    mPanel.setup({5, constants::UPPERGUIHEIGHT}, {400, 600}, sf::Color::Blue, sf::Color::Yellow, mFont, close);
    mTitle.setup("RESEARCH", sf::Color::White, mFont, 50, {15, constants::UPPERGUIHEIGHT + 15});
    mCurrentResearchLabel.setup("Current Research Progress: ", sf::Color::White, mFont, 20, {5, 550});
}

void ResearchTab::update(float dt) {
    if(mResearching) {
        mBar.update(dt);
        if(mBar.mCompleted) {
            // dood
        }
    }
}

void ResearchTab::getInput(sf::Vector2i mousePos) {
    int i = 0;
    for(auto b : mButtons) {
        if(b->checkForClick(mousePos)) {
            mCurrentResearch = mResearches[i];
            sf::Color colors[2] = {sf::Color::Green, sf::Color::Red};
            std::string strings[2] = {"YES", "NO"};
            //currentBuilding = buildings[k];
            void (*buttonFunctions[2])() = {[] (){
                //buildings[k]->buildSignal = true;
                research();
                GUI_Alert::mVisible = false;
                //std::cout << "Close!" << std::endl;
                
            }, [] (){ GUI_Alert::mVisible = false; openTab = Tabs::none;}};
            GUI_Alert::setup(sf::Color::Blue, mResearches[i]->getName(), "Are you sure you want\n to research this research, it will take you " + std::to_string(mResearches[i]->getDifficulty()) + " Ticks to complete." , sf::Color::White, 2, colors, strings, mFont, buttonFunctions);
            GUI_Alert::show();
        }
        i++;
    }

    mPanel.getExit(mousePos);
}

void ResearchTab::render(sf::RenderWindow& window) {
    mPanel.render(window);
    mTitle.render(window);
    mCurrentResearchLabel.render(window);
    mBar.render(window);
    int index = 0;
    for(auto e : mResearches) {
        e->mSpr.setPosition((index % 3) * 100 + 30, index / 3 * 150 + 200);
        window.draw(e->mSpr);
        index++;
    }

    for(auto e : mLabels) {
        e->render(window);
    }
}