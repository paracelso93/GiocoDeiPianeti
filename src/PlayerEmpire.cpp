#include "PlayerEmpire.h"

void PlayerEmpire::setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name, void (*economyClick)(), void (*shipsClick)(), void (*researchClick)(), void (*playerEmpireClick)()) {
    this->mID = ID;
    mSize = 0;
    this->mEmpireColor = empireColor;
    this->mName = name;
    if(startingPlanet != nullptr && startingStar != nullptr) {
        startingPlanet->setOccupierID(ID);
        mStars.push_back(startingStar);
        mPlanets.push_back(startingPlanet);
        mSize++;
        mEmpireSquares[(int)mPlanets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
        mEmpireSquares[(int)mPlanets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
        mEmpireSquares[(int)mPlanets.size() - 1].setFillColor(this->mEmpireColor);
    }

    this->mFunds = 1000;

    this->mFont = font;
    this->mFundsLabel.setup(std::to_string(this->mFunds),
		sf::Color::White,
		this->mFont,
		40,
		{1250, 15});

    this->mBizTex.loadFromFile("../Assets/economicSprites/bizcoin.png");
    this->mBizSpr.setTexture(this->mBizTex);
    this->mBizSpr.setPosition(Helper::findMagnitudeOfNumber(this->mFunds) * 40 + 1120, 15);

    sf::RectangleShape bs;
    bs.setSize({50, 50});
    bs.setPosition(1190, 15);

    this->mEconomyTabButton.setup(this->mFont, bs,  sf::Color(255, 200, 5, 255), sf::Color(250, 185, 7, 255), "$", 30);
    this->mEconomyTabButton.setFunction(economyClick);

    bs.setPosition(1070, 15);
    this->mShipsButton.setup(this->mFont, bs, sf::Color(200, 10, 50, 255), sf::Color(255, 10, 60, 255), "", 30);
    this->mShipsButton.addImage("../Assets/spaceshipSprites/ship2.png");
    this->mShipsButton.setFunction(shipsClick);

    bs.setPosition(1130, 15);
    this->mResearchButton.setup(this->mFont, bs, sf::Color(10, 50, 120, 255), sf::Color(10, 50, 120, 255), "", 30);
    this->mResearchButton.setFunction(researchClick);
    this->mResearchButton.addImage("../Assets/gui/research.png");

    bs.setPosition(1010, 15);
    this->mPlayerEmpireButton.setup(this->mFont, bs, sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), "", 30);
    this->mPlayerEmpireButton.setFunction(playerEmpireClick);
    this->mPlayerEmpireButton.addImage("../Assets/playerEmpire.png");
}

void PlayerEmpire::update(sf::Vector2i mousePos) {
    if(mEconomyTabButton.checkForClick(mousePos)) {
        mEconomyTabButton.click();
    }
    if(mShipsButton.checkForClick(mousePos)) {
        mShipsButton.click();
    }
    if(mResearchButton.checkForClick(mousePos)) {
        mResearchButton.click();
    }
    if(mPlayerEmpireButton.checkForClick(mousePos)) {
        mPlayerEmpireButton.click();
    }
}

void PlayerEmpire::render(sf::RenderWindow& window) {
    for(int i = 0; i < mSize; i++) {
        //std::cout << empireSquares[i].getPosition().x << std::endl;
        //std::cout << empireSquares[i].getPosition().y << std::endl;
        window.draw(mEmpireSquares[i]);
    }
}

void PlayerEmpire::renderGUI(sf::RenderWindow &window) {
    this->mFundsLabel.render(window);
    this->mEconomyTabButton.render(window);
    this->mShipsButton.render(window);
    this->mResearchButton.render(window);
    this->mPlayerEmpireButton.render(window);
    this->mBizSpr.setPosition(Helper::findMagnitudeOfNumber(this->mFunds) * 40 + 1250, 15);
    window.draw(this->mBizSpr);
}