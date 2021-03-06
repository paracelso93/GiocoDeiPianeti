#ifndef MAP_H__
#define MAP_H__

#include "GridNode.h"
#include "Constants.h"

class BattleMap {
    public:  
        GridNode *nodes;
        void setup(int width, int height);
        void render(sf::RenderWindow *window);
        void clear() { delete nodes; delete this; }
        int width;
        int height;
        int nWidth;
        int nHeight;
};


#endif