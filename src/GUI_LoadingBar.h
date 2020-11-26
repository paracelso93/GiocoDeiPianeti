#ifndef GUI_LOADINGBAR_H
#define GUI_LOADINGBAR_H

#include <SFML/Graphics.hpp>

class GUI_LoadingBar {
    public:   
        void setup(int x, int y, int w, int h, sf::Color bgcolor, sf::Color fgcolor, float max, float startvalue = 0.f);
        void update(float dt);
        void render(sf::RenderWindow *window);
        bool completed;
    private:   
        float max;
        float currentValue;
        int w;
        int h;
        sf::RectangleShape background;
        sf::RectangleShape foreground;

};

#endif