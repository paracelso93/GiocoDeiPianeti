#include "GridNode.h"

void GridNode::setup(int x, int y, int w, int h) {
    this->shape.setPosition(x, y);
    this->shape.setSize(sf::Vector2f(w, h));
    this->shape.setFillColor(sf::Color::Transparent);
    this->shape.setOutlineThickness(1);
    this->shape.setOutlineColor(sf::Color::White);
}

void GridNode::setupAStar(bool isObstacle, int privateGoal, int publicGoal) {
    this->isObstacle = isObstacle;
    this->privateGoal = privateGoal;
    this->publicGoal = publicGoal;
    this->isSearched = false;
    this->parent = nullptr;
    this->isPath = false;
}

void GridNode::render(sf::RenderWindow *window) {
    window->draw(shape);
}
