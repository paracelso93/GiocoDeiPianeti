#include "Empire.h"


void Empire::setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name) {
    this->ID = ID;
    this->size = 0;
    this->empireColor = empireColor;
    this->name = name;
    if(startingPlanet != nullptr && startingStar != nullptr) {
        startingPlanet->setOccupierID(ID);
        this->stars.push_back(startingStar);
        this->planets.push_back(startingPlanet);
        this->size++;
        this->empireSquares[(int)planets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
        this->empireSquares[(int)planets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
        this->empireSquares[(int)planets.size() - 1].setFillColor(this->empireColor);
    }

    this->funds = 100;

    this->font = font;
}

void Empire::conquerPlanet(Planet *p, Star *s, sf::Vector2i pos)  {
    this->planets.push_back(p);
    p->setOccupierID(ID);
    this->stars.push_back(s);
    this->size++;
    this->empireSquares[(int)planets.size() - 1].setPosition(pos.x * constants::GRIDSIDELENGTH, pos.y * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
    this->empireSquares[(int)planets.size() - 1].setSize({static_cast<float>(constants::GRIDSIDELENGTH), static_cast<float>(constants::GRIDSIDELENGTH)});
    this->empireSquares[(int)planets.size() - 1].setFillColor(this->empireColor);
}

void Empire::render(sf::RenderWindow *window) {
    for(int i = 0; i < size; i++) {
        //std::cout << empireSquares[i].getPosition().x << std::endl;
        //std::cout << empireSquares[i].getPosition().y << std::endl;
        window->draw(empireSquares[i]);
    }
}
