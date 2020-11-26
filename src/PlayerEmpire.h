#ifndef PLAYER_EMPIRE_H
#define PLAYER_EMPIRE_H


#include "Empire.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "SpaceshipPart.h"

class PlayerEmpire : public Empire {

    private:
        GUI_Label fundsLabel;
        GUI_Button economyTabButton;
        GUI_Button shipsButton;
        GUI_Button researchButton;
        GUI_Button playerEmpireButton;
        sf::Texture bizTex;
        sf::Sprite bizSpr;

    public:  
        PlayerEmpire() {}
        ~PlayerEmpire() {}

        std::vector<SpaceshipPart *> parts;

        void setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name, void (*economyClick)(), void (*shipsClick)(), void (*researchClick)(), void (*playerEmpireClick)());
        void render(sf::RenderWindow *window) override;
        void renderGUI(sf::RenderWindow *window);
        void update(sf::Vector2i mousePos);
        
        void setFunds(int f) override {
            this->funds = f;
            this->fundsLabel.setString(std::to_string(this->funds));
        }
};



#endif