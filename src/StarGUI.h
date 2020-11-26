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
        GUI_Panel guiRec;
        sf::Text starInfo[4];
        sf::Font font;
        GUI_Panel planetDescriptionBG;
        GUI_Label planetRadiusLabel;
        GUI_Label planetMassLabel;
        GUI_Label planetNameLabel;
        GUI_Label planetDistanceLabel;
        GUI_Label planetOwnerLabel;
        GUI_Button buildButton;
        GUI_Button buildShipButton;
        
        int currentPlanetIndex;
        
    public:
        Star currentStar;
        StarGUI();
        virtual ~StarGUI();
        sf::Text timeDilationText;
        static bool visible;
        static bool planetDescriptionVisible;
        void setup(float timeD, sf::Font font, void (*openBuildTab)(), void (*openSpaceshipBuildTab)());
        void setStar(Star currentStar);
        void setVisible(bool visible);
        void render(sf::RenderWindow *window, float timeDilation, Empire *empires, PlayerEmpire &empire);
        bool update(sf::Vector2i mousePos);
        bool hoveringOnPlanet(sf::Vector2i mousePos);

        static void closeStarGUI() { visible = false; }
        static void closePlanetGUI() { planetDescriptionVisible = false; }
};

#endif // STARGUI_H
