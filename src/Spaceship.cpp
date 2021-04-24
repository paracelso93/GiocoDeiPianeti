#include "Spaceship.h"

void Spaceship::setup(Star *startingStar, Planet *startingPlanet, int maxFuel, std::string name, float x, float y, std::string texturePath, SpaceShipTypes type, int offset, float speed, int cost) {
    this->mCurrentStar = startingStar;
    this->mCurrentPlanet = startingPlanet;
    this->mMaxFuel = maxFuel;
    this->mFuel = maxFuel;
    this->mName = name;
    this->mType = type;
    this->mOffset = offset;
    this->mX = x;
    this->mY = y;
    this->mVx = 0;
    this->mVy = 0;
    this->mTexture.loadFromFile(texturePath);
    this->mTravelling = false;
    this->mCost = cost;

    this->mWorldX = this->mCurrentStar->mX;
    this->mWorldY = this->mCurrentStar->mY + constants::UPPERGUIHEIGHT;
    
    this->mShipSprite.setTexture(this->mTexture);
    this->mShipSprite.setScale(0.1f, 0.1f);
    this->mShipSprite.setPosition(mCurrentPlanet->mX - mCurrentPlanet->mRadius * 3 + offset, mCurrentPlanet->mY - mCurrentPlanet->mRadius * 3);

    this->mSpaceSprite.setTexture(this->mTexture);
    this->mSpaceSprite.setScale(0.1f, 0.1f);
    this->mSpaceSprite.setPosition(this->mWorldX + mOffset, this->mWorldY);

    this->mBattleSprite.setTexture(this->mTexture);
    this->mBattleSprite.setScale(0.3f, 0.3f);
    this->mSpeed = speed;
    std::string borderPath = texturePath;
    for(int i = 0; i < 4; i++) 
        borderPath.pop_back();

    borderPath += "_border.png";

    this->mBorderTexture.loadFromFile(borderPath);
    this->mBorderShipSprite.setTexture(mBorderTexture);
    this->mBorderShipSprite.setScale(0.3f, 0.3f);
}

void Spaceship::create(int maxFuel, std::string name, std::string texturePath, SpaceShipTypes type, float speed, int cost) {
    this->mMaxFuel = maxFuel;
    this->mFuel = mMaxFuel;
    this->mName = name;
    this->mTexture.loadFromFile(texturePath);
    this->mShipSprite.setTexture(this->mTexture);
    this->mSpaceSprite.setTexture(this->mTexture);
    this->mBattleSprite.setTexture(this->mTexture);
    this->mBattleSprite.setScale(0.3f, 0.3f);

    std::string borderPath = texturePath;
    for(int i = 0; i < 4; i++) 
        borderPath.pop_back();

    borderPath += "_border.png";

    this->mBorderTexture.loadFromFile(borderPath);
    this->mBorderShipSprite.setTexture(mBorderTexture);
    this->mBorderShipSprite.setScale(0.3f, 0.3f);
    this->mType = type;
    this->mSpeed = speed;
    this->mCost = cost;
}

void Spaceship::position(Star *star, Planet *planet, float x, float y, int offset) {
    this->mCurrentStar = star;
    this->mCurrentPlanet = planet;
    this->mX = x;
    this->mY = y;
    this->mOffset = offset;
    this->mVx = 0;
    this->mVy = 0;
    this->mTravelling = false;

    this->mWorldX = this->mCurrentStar->mX;
    this->mWorldY = this->mCurrentStar->mY + constants::UPPERGUIHEIGHT;
    
    this->mShipSprite.setScale(0.1f, 0.1f);
    this->mShipSprite.setPosition(this->mCurrentPlanet->mX - this->mCurrentPlanet->mRadius * 3 + this->mOffset, this->mCurrentPlanet->mY - this->mCurrentPlanet->mRadius * 3);

    this->mSpaceSprite.setScale(0.1f, 0.1f);
    this->mSpaceSprite.setPosition(this->mWorldX + this->mOffset, this->mWorldY);
}


void Spaceship::render(sf::RenderWindow& window, Star *selectedStar, bool isGUIVisible, sf::View view) {
    if(isGUIVisible) {
        if(mCurrentStar->mName == selectedStar->mName) {
            for(int i = 0; i < mCurrentStar->mNumP; i++) {
                if(mCurrentStar->mPlanets[i].mName == this->mCurrentPlanet->mName) {
                    this->mX = selectedStar->mPlanets[i].mX;
                    this->mY = selectedStar->mPlanets[i].mY;
                }
            }
            window.draw(this->mShipSprite);
        }
        if(window.mapCoordsToPixel({static_cast<float>(this->mWorldX), static_cast<float>(this->mWorldY)}, view).y < 690) {
            window.setView(view);
            window.draw(mSpaceSprite);
            window.setView(window.getDefaultView());
        }
    } else {
    
        window.setView(view);
        window.draw(mSpaceSprite);
        window.setView(window.getDefaultView());
    }
}

void Spaceship::update() {

    if(this->mTravelling) {
        if(this->mTarget.x > this->mWorldX) {
            mVx = this->mSpeed * (TimeController::mTimeDilation / 500.f);
        } else if(this->mTarget.x < this->mWorldX) {
            mVx = -this->mSpeed * (TimeController::mTimeDilation / 500.f);
        }

        if(this->mTarget.y > this->mWorldY) {
            mVy = this->mSpeed * (TimeController::mTimeDilation / 500.f);
        } else if(this->mTarget.y < this->mWorldY) {
            mVy = -this->mSpeed * (TimeController::mTimeDilation / 500.f);
        }

        if(std::abs(this->mTarget.x - this->mWorldX) > std::abs(this->mTarget.y - this->mWorldY)) {
            float time = (this->mTarget.x - this->mWorldX) / this->mVx;
            this->mVy = (this->mTarget.y - this->mWorldY) / time;
        } else {
            float time = (this->mTarget.y - this->mWorldY) / this->mVy;
            this->mVx = (this->mTarget.x - this->mWorldX) / time;
        }

        if(this->mTarget.x == mWorldX && this->mTarget.y == mWorldY) {
            this->mTravelling = false;
            
            this->mVx = 0;
            this->mVy = 0;
        }
        this->mWorldX += this->mVx;
        this->mWorldY += this->mVy;
        this->mSpaceSprite.setPosition(this->mWorldX, this->mWorldY);
    } else {
        this->mShipSprite.setPosition(this->mX - mCurrentPlanet->mRadius * 3 + mOffset, this->mY - mCurrentPlanet->mRadius * 3);
    }
}

void Spaceship::setTarget(sf::Vector2f position) {
    this->mTarget.x = position.x;
    this->mTarget.y = position.y;

    this->mTravelling = true;

    
    if(this->mTarget.x > this->mWorldX) {
        mVx = mSpeed * (TimeController::mTimeDilation / 500.f);
    } else if(this->mTarget.x < this->mWorldX) {
        mVx = -mSpeed * (TimeController::mTimeDilation / 500.f);
    }

    if(this->mTarget.y > this->mWorldY) {
        mVy = mSpeed * (TimeController::mTimeDilation / 500.f);
    } else if(this->mTarget.y < this->mWorldY) {
        mVy = -mSpeed * (TimeController::mTimeDilation / 500.f);
    }

    if(std::abs(this->mTarget.x - this->mWorldX) > std::abs(this->mTarget.y - this->mWorldY)) {
        float time = (this->mTarget.x - this->mWorldX) / this->mVx;
        this->mVy = (this->mTarget.y - this->mWorldY) / time * (TimeController::mTimeDilation / 500.f);
    } else {
        float time = (this->mTarget.y - this->mWorldY) / this->mVy;
        this->mVx = (this->mTarget.x - this->mWorldX) / time * (TimeController::mTimeDilation / 500.f);
    }
    if(this->mTarget.x == mWorldX && this->mTarget.y == mWorldY) {
        this->mTravelling = false;
        this->mVx = 0;
        this->mVy = 0;
    }
}

void Spaceship::setupBattle(float x, float y) {
    this->mBattlePosition.x = x;
    this->mBattlePosition.y = y;
    this->mBattleSprite.setPosition(this->mBattlePosition);
}

void Spaceship::renderBattle(sf::RenderWindow &window, bool border) {
    if(border) 
        window.draw(this->mBorderShipSprite);
    else
        window.draw(this->mBattleSprite);
}

void Spaceship::addPart(SpaceshipPart *part, bool substitute) {
    mParts.parts.push_back(part);
    this->mMaxFuel += part->getFuel();
    this->mFuel += part->getFuel();
    this->mSpeed += part->getSpeed();
    this->mCost += part->getCost();
    this->mMaxHousing += part->getHousing();
    this->mCrew += part->getHousing();
    this->mHull += part->getHull();
    this->mShields += part->getShields();

    // spaghetti
    switch (part->getType()) {
        case SpaceshipPartType::Damage: mParts.weapons.push_back(mParts.parts.size() - 1); break;
        case SpaceshipPartType::Shield: mParts.shields.push_back(mParts.parts.size() - 1); break;
        case SpaceshipPartType::Hull: if (substitute) mParts.hull = mParts.parts.size() - 1; else std::cout << "You cant't substitute part!" << part->getName() << std::endl; break;
        case SpaceshipPartType::Housing: mParts.crew.push_back(mParts.parts.size() - 1); break;
        case SpaceshipPartType::Engine: if (substitute) mParts.engine = mParts.parts.size() - 1; else std::cout << "You cant't substitute part!" << part->getName() << std::endl; break;
        case SpaceshipPartType::Fuel: mParts.fuel.push_back(mParts.parts.size() - 1); break;
    }
}