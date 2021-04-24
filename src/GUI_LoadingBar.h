#ifndef GUI_LOADINGBAR_H
#define GUI_LOADINGBAR_H

#include <SFML/Graphics.hpp>

class GUI_LoadingBar {
    public:   
        void setup(int x, int y, int w, int h, sf::Color bgcolor, sf::Color fgcolor, float max, float startvalue = 0.f);
        void update(float dt);
        void render(sf::RenderWindow& window);
        bool mCompleted;
    private:   
        float mMax;
        float mCurrentValue;
        int mWidth;
        int mHeight;
        sf::RectangleShape mBackground;
        sf::RectangleShape mForeground;

};

#endif