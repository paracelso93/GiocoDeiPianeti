#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Star.h"
#include "TimeController.h"
#include "Helper.h"
#include "SpaceshipPart.h"

enum class SpaceShipTypes {
    Scout, Researcher, War, Colonisation
};


// PARTS:
/*
 *  1 - motore
 *  N - armi
 *  1 - base
 *  N - combustibile
 *  N - scudi
 *  N - alloggi
 * */

struct SpaceshipParts {
    std::vector<SpaceshipPart*> parts;
    size_t engine;
    std::vector<size_t> weapons; // TODO: un po' orribile
    size_t hull;
    std::vector<size_t> fuel;
    std::vector<size_t> shields;
    std::vector<size_t> crew;
};

class Spaceship {

    private:
        Star *mCurrentStar;
        Planet *mCurrentPlanet;
        int mFuel;
        SpaceShipTypes mType;
        int mMaxFuel;
        int mMaxHousing;
        int mCrew;
        int mHull;
        int mShields;

        std::string mName;
        bool mTravelling;
        float mX, mY;
        float mWorldX, mWorldY;
        float mVx, mVy;
        int mCost;
        sf::Texture mTexture;
        sf::Texture mBorderTexture;
        sf::Sprite mShipSprite;
        sf::Sprite mBorderShipSprite;
        
        SpaceshipParts mParts;
        int mOffset;
        sf::Vector2f mTarget;
        sf::Vector2f mBattlePosition;
        float mSpeed;

    public:  
        void setup(Star *startingStar, Planet *startingPlanet, int maxFuel, std::string name, float x, float y, std::string texturePath, SpaceShipTypes type, int offset, float speed, int cost);
        void render(sf::RenderWindow& window, Star *currentStar, bool isGUIVisible, sf::View view);
        void update();
        sf::Vector2f getBattlePosition() { return this->mBattlePosition; }
        void setBattlePosition(float x, float y) { this->mBattlePosition.x = x; this->mBattlePosition.y = y; this->mBattleSprite.setPosition(this->mBattlePosition); }
        void setupBattle(float x, float y);
        void renderBattle(sf::RenderWindow &window, bool border);
        //void renderBattle(sf::RenderWindow *window, sf::Shader *shader);
        void create(int maxFuel, std::string name, std::string texturePath, SpaceShipTypes type, float speed, int cost);
        void position(Star *star, Planet *planet, float x, float y, int offset);
        int getCost() { return this->mCost; }
        int getOffset() { return this->mOffset; }
        void setOffset(int off) { this->mOffset = off; }
        SpaceShipTypes getType() { return this->mType; }
        void setTarget(sf::Vector2f position);
        std::string getName() { return this->mName; }
        Star *getStar() { return mCurrentStar; }
        Planet *getPlanet() { return mCurrentPlanet; }

        // SpaceShipParts
        void addPart(SpaceshipPart* part, bool substitute);

        sf::Texture getTexture() { return this->mTexture; }
        sf::Sprite mSpaceSprite;
        sf::Sprite mBattleSprite;
        Spaceship() {}
        ~Spaceship() {}
};

#endif