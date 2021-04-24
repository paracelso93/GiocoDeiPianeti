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
            grid[i * height + j].mIsSearched = false;
            grid[i * height + j].mIsObstacle = false;
            grid[i * height + j].mParent = nullptr;
            grid[i * height + j].isPath = false;
            //grid[i * height + j].shape.setFillColor(sf::Color::Blue);
            grid[i * height + j].mShape.setPosition(i * (sideSize.x + 2), j * (sideSize.y + 2));
            grid[i * height + j].mShape.setSize({sideSize.x, sideSize.y});
            //grid[i * height + j].x = i * (sideSize + sideSize / 5 * 2);
            //grid[i * height + j].y = j * (sideSize + sideSize / 5 * 2);
            grid[i * height + j].mPrivateGoal = 1000000;
            grid[i * height + j].mPublicGoal = 1000000;
        }
    }
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(j > 0) {
                grid[i * height + j].mAdjacentNodes.push_back(&grid[i * height + j - 1]);
            }
            if(j < width - 1) {
                grid[i * height + j].mAdjacentNodes.push_back(&grid[i * height + j + 1]);
            }
            if(i > 0) {
                grid[i * height + j].mAdjacentNodes.push_back(&grid[(i - 1) * height + j]);
            }
            if(i < height - 1) {
                grid[i * height + j].mAdjacentNodes.push_back(&grid[(i + 1) * height + j]);
            }
        }
    }
}

inline void executeAlgorithm(GridNode *grid, GridNode *startingNode, GridNode *endNode, int height, int width) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            grid[i * height + j].mPrivateGoal = 1000000;
            grid[i * height + j].mPublicGoal = 1000000;
            grid[i * height + j].mParent = nullptr;
            grid[i * height + j].mIsSearched = false;
            grid[i * height + j].isPath = false;
        }
    }
    std::list<GridNode *> currentNodes;
    GridNode *node = startingNode;
    //std::cout << endNode->publicGoal << std::endl;
    startingNode->mPrivateGoal = 0;
    startingNode->mPublicGoal = Helper::getDistance(startingNode->mShape.getPosition().x, startingNode->mShape.getPosition().y, endNode->mShape.getPosition().x, endNode->mShape.getPosition().y);

    currentNodes.push_back(startingNode);
    
    while(!currentNodes.empty()) {

        currentNodes.sort([](const GridNode *lhs, const GridNode *rhs) { return lhs->mPublicGoal < rhs->mPublicGoal; });
        
        while(!currentNodes.empty() && currentNodes.front()->mIsSearched) {
            currentNodes.pop_front();
        }

        if(currentNodes.empty()) {
            break;
        }

        node = currentNodes.front();
        node->mIsSearched = true;
        //std::cout << node->x << ":" << node->y << std::endl;
        
        for(auto neighbour : node->mAdjacentNodes) {
            if(!neighbour->mIsSearched && !neighbour->mIsObstacle) {
                currentNodes.push_back(neighbour);
            }

            float possibleNewPrivate = node->mPrivateGoal + Helper::getDistance(node->mShape.getPosition().x, node->mShape.getPosition().y, neighbour->mShape.getPosition().x, neighbour->mShape.getPosition().y);
            
            //std::cout << getDistance(node, neighbour) << std::endl;
            if(possibleNewPrivate < neighbour->mPrivateGoal) {
                //if(neighbour == endNode) {
                //    std::cout << "OBAMA" << std::endl;
                //}
                neighbour->mParent = node;
                neighbour->mPrivateGoal = possibleNewPrivate;

                neighbour->mPublicGoal = neighbour->mPrivateGoal + Helper::getDistance(neighbour->mShape.getPosition().x, neighbour->mShape.getPosition().y, endNode->mShape.getPosition().x, endNode->mShape.getPosition().y);
            } 
        }
    }
    //std::cout << endNode->parent->x << std::endl;
}

#endif