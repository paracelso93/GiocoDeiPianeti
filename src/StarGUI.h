#ifndef STARGUI_H
#define STARGUI_H

#include <sstream>
#include <iomanip>

#include "GUI_Label.h"
#include "GUI_Panel.h"
#include "PlayerEmpire.h"

class StarGUI
{
    private:  
        GUI_Panel mGuiRec;
        sf::Text mStarInfo[4];
        sf::Font mFont;
        GUI_Panel mPlanetDescriptionBG;
        GUI_Label mPlanetRadiusLabel;
        GUI_Label mPlanetMassLabel;
        GUI_Label mPlanetNameLabel;
        GUI_Label mPlanetDistanceLabel;
        GUI_Label mPlanetOwnerLabel;
        GUI_Button mBuildButton;
        GUI_Button mBuildShipButton;
        
        int mCurrentPlanetIndex;

        // MARCO
        sf::Texture mMarcoTexture;
        sf::Sprite mMarcoSprite;
        
    public:
        Star mCurrentStar;
        StarGUI();
        virtual ~StarGUI();
        sf::Text mTimeDilationText;
        static bool mVisible;
        static bool mPlanetDescriptionVisible;
        void setup(float timeD, sf::Font font, void (*openBuildTab)(), void (*openSpaceshipBuildTab)());
        void setStar(Star currentStar);
        void setVisible(bool visible);
        void render(sf::RenderWindow& window, float timeDilation, Empire *empires, PlayerEmpire &empire);
        bool update(sf::Vector2i mousePos);
        bool hoveringOnPlanet(sf::Vector2i mousePos);

        static void closeStarGUI() { mVisible = false; }
        static void closePlanetGUI() { mPlanetDescriptionVisible = false; }
};

#endif // STARGUI_H
