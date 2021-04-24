#include "Empire.h"


void Empire::setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name) {
    this->mID = ID;
    this->mSize = 0;
    this->mEmpireColor = empireColor;
    this->mName = name;
    if(startingPlanet != nullptr && startingStar != nullptr) {
        startingPlanet->setOccupierID(ID);
        this->mStars.push_back(startingStar);
        this->mPlanets.push_back(startingPlanet);
        this->mSize++;
        this->mEmpireSquares[(int)mPlanets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
        this->mEmpireSquares[(int)mPlanets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
        this->mEmpireSquares[(int)mPlanets.size() - 1].setFillColor(this->mEmpireColor);
    }

    this->mFunds = 100;
    mFont = font;
}

void Empire::conquerPlanet(Planet *p, Star *s, sf::Vector2i pos)  {
    this->mPlanets.push_back(p);
    p->setOccupierID(mID);
    this->mStars.push_back(s);
    this->mSize++;
    this->mEmpireSquares[(int)mPlanets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
    this->mEmpireSquares[(int)mPlanets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
    this->mEmpireSquares[(int)mPlanets.size() - 1].setFillColor(this->mEmpireColor);
}

void Empire::render(sf::RenderWindow& window) {
    for(int i = 0; i < mSize; i++) {
        //std::cout << empireSquares[i].getPosition().x << std::endl;
        //std::cout << empireSquares[i].getPosition().y << std::endl;
        window.draw(mEmpireSquares[i]);
    }
}
