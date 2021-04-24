#include "SpaceshipPart.h"

void SpaceshipPart::setup(SpaceshipPartType type, std::string filePath, int cost, int weight, std::string name) {
    this->mType = type;
    this->mCost = cost;
    this->mWeight = weight;
    this->mTex.loadFromFile(filePath);
    this->mSpr.setTexture(this->mTex);
    this->mName = name;
}