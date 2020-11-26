#include "PlayerEmpire.h"

void PlayerEmpire::setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name, void (*economyClick)(), void (*shipsClick)(), void (*researchClick)(), void (*playerEmpireClick)()) {
    this->ID = ID;
    size = 0;
    this->empireColor = empireColor;
    this->name = name;
    if(startingPlanet != nullptr && startingStar != nullptr) {
        startingPlanet->setOccupierID(ID);
        stars.push_back(startingStar);
        planets.push_back(startingPlanet);
        size++;
        empireSquares[(int)planets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
        empireSquares[(int)planets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
        empireSquares[(int)planets.size() - 1].setFillColor(this->empireColor);
    }

    this->funds = 1000;

    this->font = font;
    this->fundsLabel.setup(std::to_string(this->funds),
		sf::Color::White,
		this->font,
		40,
		{1250, 15});

    this->bizTex.loadFromFile("../Assets/economicSprites/bizcoin.png");
    this->bizSpr.setTexture(this->bizTex);
    this->bizSpr.setPosition(Helper::findMagnitudeOfNumber(this->funds) * 40 + 1120, 15);

    sf::RectangleShape bs;
    bs.setSize({50, 50});
    bs.setPosition(1190, 15);

    this->economyTabButton.setup(this->font, bs,  sf::Color(255, 200, 5, 255), sf::Color(250, 185, 7, 255), "$", 30);
    this->economyTabButton.setFunction(economyClick);

    bs.setPosition(1070, 15);
    this->shipsButton.setup(this->font, bs, sf::Color(200, 10, 50, 255), sf::Color(255, 10, 60, 255), "", 30);
    this->shipsButton.addImage("../Assets/spaceshipSprites/ship2.png");
    this->shipsButton.setFunction(shipsClick);

    bs.setPosition(1130, 15);
    this->researchButton.setup(this->font, bs, sf::Color(10, 50, 120, 255), sf::Color(10, 50, 120, 255), "", 30);
    this->researchButton.setFunction(researchClick);
    this->researchButton.addImage("../Assets/gui/research.png");

    bs.setPosition(1010, 15);
    this->playerEmpireButton.setup(this->font, bs, sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), "", 30);
    this->playerEmpireButton.setFunction(playerEmpireClick);
    this->playerEmpireButton.addImage("../Assets/playerEmpire.png");
}

void PlayerEmpire::update(sf::Vector2i mousePos) {
    if(economyTabButton.checkForClick(mousePos)) {
        economyTabButton.click();
    }
    if(shipsButton.checkForClick(mousePos)) {
        shipsButton.click();
    }
    if(researchButton.checkForClick(mousePos)) {
        researchButton.click();
    }
    if(playerEmpireButton.checkForClick(mousePos)) {
        playerEmpireButton.click();
    }
}

void PlayerEmpire::render(sf::RenderWindow *window) {
    for(int i = 0; i < size; i++) {
        //std::cout << empireSquares[i].getPosition().x << std::endl;
        //std::cout << empireSquares[i].getPosition().y << std::endl;
        window->draw(empireSquares[i]);
    }
}

void PlayerEmpire::renderGUI(sf::RenderWindow *window) {
    this->fundsLabel.render(window);
    this->economyTabButton.render(window);
    this->shipsButton.render(window);
    this->researchButton.render(window);
    this->playerEmpireButton.render(window);
    this->bizSpr.setPosition(Helper::findMagnitudeOfNumber(this->funds) * 40 + 1250, 15);
    window->draw(this->bizSpr);
}