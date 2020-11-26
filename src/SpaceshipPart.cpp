#include "SpaceshipPart.h"

void SpaceshipPart::setup(SpaceshipPartType type, std::string filePath, int cost, int weight, std::string name) {
    this->type = type;
    this->cost = cost;
    this->weight = weight;
    this->tex.loadFromFile(filePath);
    this->spr.setTexture(this->tex);
    this->name = name;
}