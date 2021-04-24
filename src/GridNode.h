#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GridNode {
    public:  
        void setup(int x, int y, int w, int h);
        void render(sf::RenderWindow& window);
        sf::RectangleShape mShape;
    private:
        
    public:  
        /// A*
        int mPrivateGoal;
        int mPublicGoal;
        bool mIsObstacle;
        bool isPath;
        bool mIsSearched;
        std::vector<GridNode *> mAdjacentNodes;
        GridNode *mParent;
        void setupAStar(bool isObstacle, int privateGoal, int publicGoal);
};

#endif