#include "Battle.h"

void Battle::setup(int ID1, int ID2) {
    this->side1ID = ID1;
    this->side2ID = ID2;
    selectedShipIndex = 0;
    selected = false;
    //this->outline.loadFromFile("../Assets/shaders/border_shader.frag", sf::Shader::Fragment);
    //this->outline.loadFromFile("../Assets/shaders/border_shader.vert", "../Assets/shaders/border_shader.frag");
}

void Battle::setSpaceship(int ID, Spaceship *spaceship) {
    if(ID == side1ID) {
        this->side1Spaceships.push_back(spaceship);
    } else if(ID == side2ID) {
        this->side2Spaceships.push_back(spaceship);
    } else {
        std::cerr << "Error, unknown id " << ID << std::endl;
    }
}

void Battle::getInput(sf::Vector2i mousePos) {
    for(int i = 0; i < map->height; i++) {
        for(int j = 0; j < map->width; j++) {
            if(map->nodes[i * map->width + j].shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedShipIndex = 0;
                selected = true;
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
    for(auto s : ((ID1 == side1ID) ? side1Spaceships : side2Spaceships)) {
        s->setupBattle(xoffset, yoffset);
        xoffset += map->nWidth;
        if(xoffset >= constants::SCREENY) {
            xoffset = 0;
            yoffset += map->nHeight;
        }
    }

    xoffset = 0;
    yoffset = constants::SCREENY - map->nHeight;
    for(auto s : ((ID2 == side1ID) ? side1Spaceships : side2Spaceships)) {
        s->setupBattle(xoffset, yoffset);
        xoffset += map->nWidth;
        if(xoffset >= constants::SCREENY) {
            xoffset = 0;
            yoffset -= map->nHeight;
        }
    }
}

void Battle::setMap(BattleMap *map) {
    this->map = map;
}

void Battle::render(sf::RenderWindow *window) {
    if(selected) {
        int index = 0;
        for(auto s : side1Spaceships) {
            if(index == selectedShipIndex) {
                s->renderBattle(window, true);
                //s->renderBattle(window, &outline);
            } else {
                s->renderBattle(window, false);
            }
            //s->renderBattle(window);
            index++;
        }
        for(auto s : side2Spaceships) {
            if(index == selectedShipIndex) {
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
        for(auto s : side1Spaceships) {
            s->renderBattle(window, false);
        }
        for(auto s : side2Spaceships) {
            s->renderBattle(window, false);
        }
    }
    this->map->render(window);
}