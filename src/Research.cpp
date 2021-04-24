#include "Research.h"

void Research::setup(std::string name, int cost, ResearchTypes type, ResearchField field, std::string filePath, int difficulty) {
    this->mName = name;
    this->mCost = cost;
    this->mType = type;
    this->mField = field;
    this->mTex.loadFromFile(filePath);
    this->mSpr.setTexture(this->mTex);
    this->mDifficulty = difficulty;
}

void Research::finishResearch(PlayerEmpire *e) {
    switch (this->mType)
    {
        case ResearchTypes::UnlockShipPart: e->mParts.push_back(this->mPart);
            break;
        case ResearchTypes::UnlockBuilding: e->mAvailableBuildings.push_back(this->mBuilding);
            break;
        case ResearchTypes::UnlockShip: e->mAvailableShips.push_back(this->mSpaceship);
            break;
        case ResearchTypes::Buff: std::cout << "owo" << std::endl;
            break;
        default: std::cout << "Missing research type!" << std::endl;
    }
}