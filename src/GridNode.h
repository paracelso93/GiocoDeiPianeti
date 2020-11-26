#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GridNode {
    public:  
        void setup(int x, int y, int w, int h);
        void render(sf::RenderWindow *window);
        sf::RectangleShape shape;
    private:
        
    public:  
        /// A*
        int privateGoal;
        int publicGoal;
        bool isObstacle;
        bool isPath;
        bool isSearched;
        std::vector<GridNode *> adjacentNodes;
        GridNode *parent;
        void setupAStar(bool isObstacle, int privateGoal, int publicGoal);
};

#endif