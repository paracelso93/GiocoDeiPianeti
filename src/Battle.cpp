#include "Battle.h"

void Battle::setup(int ID1, int ID2) {
    this->mSide1ID = ID1;
    this->mSide2ID = ID2;
    mSelectedShipIndex = 0;
    mSelected = false;
    //this->outline.loadFromFile("../Assets/shaders/border_shader.frag", sf::Shader::Fragment);
    //this->outline.loadFromFile("../Assets/shaders/border_shader.vert", "../Assets/shaders/border_shader.frag");
}

void Battle::setSpaceship(int ID, Spaceship *spaceship) {
    if(ID == mSide1ID) {
        this->mSide1Spaceships.push_back(spaceship);
    } else if(ID == mSide2ID) {
        this->mSide2Spaceships.push_back(spaceship);
    } else {
        std::cerr << "Error, unknown id " << ID << std::endl;
    }
}

void Battle::getInput(sf::Vector2i mousePos) {
    for(int i = 0; i < mMap->mHeight; i++) {
        for(int j = 0; j < mMap->mWidth; j++) {
            if(mMap->nodes[i * mMap->mWidth + j].mShape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                mSelectedShipIndex = 0;
                mSelected = true;
                //std::cout << "obamium" << std::endl;
                //outline.setUniform( "textureOffset", 1.0f / static_cast<float>( side1Spaceships[0]->battleSprite.getPosition().x ) );
                //outline.setUniform( "texture", side1Spaceships[0]->battleSprite.getTexture() );
            }
        }
    }
}

void Battle::generateBattlePositions(int ID1, int ID2) {
    float xoffset = 0;
    float yoffset = 0;
    for(auto s : ((ID1 == mSide1ID) ? mSide1Spaceships : mSide2Spaceships)) {
        s->setupBattle(xoffset, yoffset);
        xoffset += mMap->mNWidth;
        if(xoffset >= constants::SCREENY) {
            xoffset = 0;
            yoffset += mMap->mNHeight;
        }
    }

    xoffset = 0;
    yoffset = constants::SCREENY - mMap->mNHeight;
    for(auto s : ((ID2 == mSide1ID) ? mSide1Spaceships : mSide2Spaceships)) {
        s->setupBattle(xoffset, yoffset);
        xoffset += mMap->mNWidth;
        if(xoffset >= constants::SCREENY) {
            xoffset = 0;
            yoffset -= mMap->mNHeight;
        }
    }
}

void Battle::setMap(BattleMap *map) {
    this->mMap = map;
}

void Battle::render(sf::RenderWindow& window) {
    if(mSelected) {
        int index = 0;
        for(auto s : mSide1Spaceships) {
            if(index == mSelectedShipIndex) {
                s->renderBattle(window, true);
                //s->renderBattle(window, &outline);
            } else {
                s->renderBattle(window, false);
            }
            //s->renderBattle(window);
            index++;
        }
        for(auto s : mSide2Spaceships) {
            if(index == mSelectedShipIndex) {
                //outline.setParameter("u_texture", s->getTexture());
                //outline.setParameter("u_projTrans", s->battleSprite.getTransform());
                //outline.setUniform( "textureOffset", 1.0f / static_cast<float>( s->battleSprite.getPosition().x ) );
                //outline.setUniform( "texture", s->battleSprite.getTexture() );
                s->renderBattle(window, true);
                //s->renderBattle(window, &outline);
            } else {
                s->renderBattle(window, false);
            }
            
            index++;
        }
    } else {
        for(auto s : mSide1Spaceships) {
            s->renderBattle(window, false);
        }
        for(auto s : mSide2Spaceships) {
            s->renderBattle(window, false);
        }
    }
    this->mMap->render(window);
}