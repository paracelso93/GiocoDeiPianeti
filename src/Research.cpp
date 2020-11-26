#include "Research.h"

void Research::setup(std::string name, int cost, ResearchTypes type, ResearchField field, std::string filePath, int difficulty) {
    this->name = name;
    this->cost = cost;
    this->type = type;
    this->field = field;
    this->tex.loadFromFile(filePath);
    this->spr.setTexture(this->tex);
    this->difficulty = difficulty;
}

void Research::finishResearch(PlayerEmpire *e) {
    switch (this->type)
    {
        case ResearchTypes::UnlockShipPart: e->parts.push_back(this->part);
            break;
        case ResearchTypes::UnlockBuilding: e->availbleBuildings.push_back(this->building);
            break;
        case ResearchTypes::UnlockShip: e->availbleShips.push_back(this->spaceship);
            break;
        case ResearchTypes::Buff: std::cout << "owo" << std::endl;
            break;
        default: std::cout << "Missing research type!" << std::endl;
    }
}