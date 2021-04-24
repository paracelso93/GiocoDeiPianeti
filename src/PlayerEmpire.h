#ifndef PLAYER_EMPIRE_H
#define PLAYER_EMPIRE_H


#include "Empire.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "SpaceshipPart.h"

class PlayerEmpire : public Empire {

    private:
        GUI_Label mFundsLabel;
        GUI_Button mEconomyTabButton;
        GUI_Button mShipsButton;
        GUI_Button mResearchButton;
        GUI_Button mPlayerEmpireButton;
        sf::Texture mBizTex;
        sf::Sprite mBizSpr;

    public:  
        PlayerEmpire() {}
        ~PlayerEmpire() {}

        std::vector<SpaceshipPart *> mParts;

        void setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name, void (*economyClick)(), void (*shipsClick)(), void (*researchClick)(), void (*playerEmpireClick)());
        void render(sf::RenderWindow& window) override;
        void renderGUI(sf::RenderWindow& window);
        void update(sf::Vector2i mousePos);
        
        void setFunds(int f) override {
            this->mFunds = f;
            this->mFundsLabel.setString(std::to_string(this->mFunds));
        }
};



#endif