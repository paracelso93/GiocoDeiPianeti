#ifndef ASTAR_H
#define ASTAR_H

#include "GridNode.h"
#include "Helper.h"
#include "Constants.h"
#include <list>

inline void setupNodes(GridNode *grid, int height, int width) {
    sf::Vector2f sideSize = sf::Vector2f(constants::SCREENX / width, constants::SCREENY / height);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            grid[i * height + j].isSearched = false;
            grid[i * height + j].isObstacle = false;
            grid[i * height + j].parent = nullptr;
            grid[i * height + j].isPath = false;
            //grid[i * height + j].shape.setFillColor(sf::Color::Blue);
            grid[i * height + j].shape.setPosition(i * (sideSize.x + 2), j * (sideSize.y + 2));
            grid[i * height + j].shape.setSize({sideSize.x, sideSize.y});
            //grid[i * height + j].x = i * (sideSize + sideSize / 5 * 2);
            //grid[i * height + j].y = j * (sideSize + sideSize / 5 * 2);
            grid[i * height + j].privateGoal = 1000000;
            grid[i * height + j].publicGoal = 1000000;
        }
    }
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(j > 0) {
                grid[i * height + j].adjacentNodes.push_back(&grid[i * height + j - 1]);
            }
            if(j < width - 1) {
                grid[i * height + j].adjacentNodes.push_back(&grid[i * height + j + 1]);
            }
            if(i > 0) {
                grid[i * height + j].adjacentNodes.push_back(&grid[(i - 1) * height + j]);
            }
            if(i < height - 1) {
                grid[i * height + j].adjacentNodes.push_back(&grid[(i + 1) * height + j]);
            }
        }
    }
}

inline void executeAlgorithm(GridNode *grid, GridNode *startingNode, GridNode *endNode, int height, int width) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            grid[i * height + j].privateGoal = 1000000;
            grid[i * height + j].publicGoal = 1000000;
            grid[i * height + j].parent = nullptr;
            grid[i * height + j].isSearched = false;
            grid[i * height + j].isPath = false;
        }
    }
    std::list<GridNode *> currentNodes;
    GridNode *node = startingNode;
    //std::cout << endNode->publicGoal << std::endl;
    startingNode->privateGoal = 0;
    startingNode->publicGoal = Helper::getDistance(startingNode->shape.getPosition().x, startingNode->shape.getPosition().y, endNode->shape.getPosition().x, endNode->shape.getPosition().y);

    currentNodes.push_back(startingNode);
    
    while(!currentNodes.empty()) {

        currentNodes.sort([](const GridNode *lhs, const GridNode *rhs) { return lhs->publicGoal < rhs->publicGoal; });
        
        while(!currentNodes.empty() && currentNodes.front()->isSearched) {
            currentNodes.pop_front();
        }

        if(currentNodes.empty()) {
            break;
        }

        node = currentNodes.front();
        node->isSearched = true;
        //std::cout << node->x << ":" << node->y << std::endl;
        
        for(auto neighbour : node->adjacentNodes) {
            if(!neighbour->isSearched && !neighbour->isObstacle) {
                currentNodes.push_back(neighbour);
            }

            float possibleNewPrivate = node->privateGoal + Helper::getDistance(node->shape.getPosition().x, node->shape.getPosition().y, neighbour->shape.getPosition().x, neighbour->shape.getPosition().y);
            
            //std::cout << getDistance(node, neighbour) << std::endl;
            if(possibleNewPrivate < neighbour->privateGoal) {
                //if(neighbour == endNode) {
                //    std::cout << "OBAMA" << std::endl;
                //}
                neighbour->parent = node;
                neighbour->privateGoal = possibleNewPrivate;

                neighbour->publicGoal = neighbour->privateGoal + Helper::getDistance(neighbour->shape.getPosition().x, neighbour->shape.getPosition().y, endNode->shape.getPosition().x, endNode->shape.getPosition().y);
            } 
        }
    }
    //std::cout << endNode->parent->x << std::endl;
}

#endif