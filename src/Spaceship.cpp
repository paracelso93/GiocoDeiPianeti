#include "Spaceship.h"

void Spaceship::setup(Star *startingStar, Planet *startingPlanet, int maxFuel, std::string name, float x, float y, std::string texturePath, SpaceShipTypes type, int offset, float speed, int cost) {
    this->currentStar = startingStar;
    this->currentPlanet = startingPlanet;
    this->maxFuel = maxFuel;
    this->fuel = maxFuel;
    this->name = name;
    this->type = type;
    this->offset = offset;
    this->x = x;
    this->y = y;
    this->vx = 0;
    this->vy = 0;
    this->texture.loadFromFile(texturePath);
    this->travelling = false;
    this->cost = cost;

    this->worldx = this->currentStar->x;
    this->worldy = this->currentStar->y + constants::UPPERGUIHEIGHT;
    
    this->shipSprite.setTexture(this->texture);
    this->shipSprite.setScale(0.1f, 0.1f);
    this->shipSprite.setPosition(currentPlanet->x - currentPlanet->radius * 3 + offset, currentPlanet->y - currentPlanet->radius * 3);

    this->spaceSprite.setTexture(this->texture);
    this->spaceSprite.setScale(0.1f, 0.1f);
    this->spaceSprite.setPosition(this->worldx + offset, this->worldy);

    this->battleSprite.setTexture(this->texture);
    this->battleSprite.setScale(0.3f, 0.3f);
    this->speed = speed;
    std::string borderPath = texturePath;
    for(int i = 0; i < 4; i++) 
        borderPath.pop_back();

    borderPath += "_border.png";

    this->borderTexture.loadFromFile(borderPath);
    this->borderShipSprite.setTexture(borderTexture);
    this->borderShipSprite.setScale(0.3f, 0.3f);
}

void Spaceship::create(int maxFuel, std::string name, std::string texturePath, SpaceShipTypes type, float speed, int cost) {
    this->maxFuel = maxFuel;
    this->name = name;
    this->texture.loadFromFile(texturePath);
    this->shipSprite.setTexture(this->texture);
    this->spaceSprite.setTexture(this->texture);
    this->battleSprite.setTexture(this->texture);
    this->battleSprite.setScale(0.3f, 0.3f);

    std::string borderPath = texturePath;
    for(int i = 0; i < 4; i++) 
        borderPath.pop_back();

    borderPath += "_border.png";

    this->borderTexture.loadFromFile(borderPath);
    this->borderShipSprite.setTexture(borderTexture);
    this->borderShipSprite.setScale(0.3f, 0.3f);
    this->type = type;
    this->speed = speed;
    this->cost = cost;
}

void Spaceship::position(Star *star, Planet *planet, float x, float y, int offset) {
    this->currentStar = star;
    this->currentPlanet = planet;
    this->x = x;
    this->y = y;
    this->offset = offset;
    this->vx = 0;
    this->vy = 0;
    this->travelling = false;

    this->worldx = this->currentStar->x;
    this->worldy = this->currentStar->y + constants::UPPERGUIHEIGHT;
    
    this->shipSprite.setScale(0.1f, 0.1f);
    this->shipSprite.setPosition(this->currentPlanet->x - this->currentPlanet->radius * 3 + this->offset, this->currentPlanet->y - this->currentPlanet->radius * 3);

    this->spaceSprite.setScale(0.1f, 0.1f);
    this->spaceSprite.setPosition(this->worldx + this->offset, this->worldy);
}


void Spaceship::render(sf::RenderWindow *window, Star *selectedStar, bool isGUIVisible, sf::View view) {
    if(isGUIVisible) {
        if(currentStar->name == selectedStar->name) {
            for(int i = 0; i < currentStar->nump; i++) {
                if(currentStar->planets[i].name == this->currentPlanet->name) {
                    this->x = selectedStar->planets[i].x;
                    this->y = selectedStar->planets[i].y;
                }
            }
            window->draw(this->shipSprite);
        }
        if(window->mapCoordsToPixel({static_cast<float>(this->worldx), static_cast<float>(this->worldy)}, view).y < 690) {
            window->setView(view);
            window->draw(spaceSprite);
            window->setView(window->getDefaultView());
        }
    } else {
    
        window->setView(view);
        window->draw(spaceSprite);
        window->setView(window->getDefaultView());
    }
}

void Spaceship::update() {

    if(this->travelling) {
        if(this->target.x > this->worldx) {
            vx = this->speed * (TimeController::timeDilation / 500.f);
        } else if(this->target.x < this->worldx) {
            vx = -this->speed * (TimeController::timeDilation / 500.f);
        }

        if(this->target.y > this->worldy) {
            vy = this->speed * (TimeController::timeDilation / 500.f);
        } else if(this->target.y < this->worldy) {
            vy = -this->speed * (TimeController::timeDilation / 500.f);
        }

        if(std::abs(this->target.x - this->worldx) > std::abs(this->target.y - this->worldy)) {
            float time = (this->target.x - this->worldx) / this->vx;
            this->vy = (this->target.y - this->worldy) / time;
        } else {
            float time = (this->target.y - this->worldy) / this->vy;
            this->vx = (this->target.x - this->worldx) / time;
        }

        if(this->target.x == worldx && this->target.y == worldy) {
            this->travelling = false;
            
            this->vx = 0;
            this->vy = 0;
        }
        this->worldx += this->vx;
        this->worldy += this->vy;
        this->spaceSprite.setPosition(this->worldx, this->worldy);
    } else {
        this->shipSprite.setPosition(this->x - currentPlanet->radius * 3 + offset, this->y - currentPlanet->radius * 3);
    }
}

void Spaceship::setTarget(sf::Vector2f position) {
    this->target.x = position.x;
    this->target.y = position.y;

    this->travelling = true;

    
    if(this->target.x > this->worldx) {
        vx = speed * (TimeController::timeDilation / 500.f);
    } else if(this->target.x < this->worldx) {
        vx = -speed * (TimeController::timeDilation / 500.f);
    }

    if(this->target.y > this->worldy) {
        vy = speed * (TimeController::timeDilation / 500.f);
    } else if(this->target.y < this->worldy) {
        vy = -speed * (TimeController::timeDilation / 500.f);
    }

    if(std::abs(this->target.x - this->worldx) > std::abs(this->target.y - this->worldy)) {
        float time = (this->target.x - this->worldx) / this->vx;
        this->vy = (this->target.y - this->worldy) / time * (TimeController::timeDilation / 500.f);
    } else {
        float time = (this->target.y - this->worldy) / this->vy;
        this->vx = (this->target.x - this->worldx) / time * (TimeController::timeDilation / 500.f);
    }
    if(this->target.x == worldx && this->target.y == worldy) {
        this->travelling = false;
        this->vx = 0;
        this->vy = 0;
    }
}

void Spaceship::setupBattle(float x, float y) {
    this->battlePosition.x = x;
    this->battlePosition.y = y;
    this->battleSprite.setPosition(this->battlePosition);
}

void Spaceship::renderBattle(sf::RenderWindow *window, bool border) {
    if(border) 
        window->draw(this->borderShipSprite);
    else
        window->draw(this->battleSprite);
}
