#include "GridNode.h"

void GridNode::setup(int x, int y, int w, int h) {
    this->mShape.setPosition(x, y);
    this->mShape.setSize(sf::Vector2f(w, h));
    this->mShape.setFillColor(sf::Color::Transparent);
    this->mShape.setOutlineThickness(1);
    this->mShape.setOutlineColor(sf::Color::White);
}

void GridNode::setupAStar(bool isObstacle, int privateGoal, int publicGoal) {
    this->mIsObstacle = isObstacle;
    this->mPrivateGoal = privateGoal;
    this->mPublicGoal = publicGoal;
    this->mIsSearched = false;
    this->mParent = nullptr;
    this->isPath = false;
}

void GridNode::render(sf::RenderWindow& window) {
    window.draw(mShape);
}
