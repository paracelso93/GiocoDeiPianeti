#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <ctime>
#include <stdio.h>
#include <stdlib.h> 

#include "Parser.h"
#include "StarGUI.h"
#include "EconomicsTab.h"
#include "Menu.h"
#include "BuildTab.h"
#include "PlayerEmpire.h"
#include "BuildingsParser.h"
#include "GUI_Alert.h"
#include "TimeController.h"
#include "SpaceshipBuildTab.h"
#include "Animation.h"
#include "ResearchTab.h"
#include "ResearchParser.h"
#include "PlayerEmpireTab.h"
#include "Battle.h"

enum class GameStates {
    game,
    menu,
    battle,
    quit
};

struct Movement {
    bool movingUp;
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    void setup() {
        movingUp = false;
        movingDown = false;
        movingLeft = false;
        movingRight = false;
    }
};

class Game {
    public:  
        Game() : window(sf::VideoMode(constants::SCREENX, constants::SCREENY), "GIOCO DEI PIANETI") {}
        ~Game() {}
        void setup();
        void getInput();
        void update();
        void render();
        void clear() {}
        bool getClose() { return !(this->window.isOpen()); }

    private:  
        sf::RenderWindow window;
        static DysonSphere startingSphere;
        static GameStates state;
        static Empire empires[2];
        static Star* stars;
        static PlayerEmpire playerEmpire;
        static sf::Font font;
        

    private:
        sf::Texture loadingTexture;
        sf::Sprite loadingSprite;
        sf::View starview;
        float mouseWheelDelta;
        Movement movement;
        float animationCountDown;
        float animationTime;
        sf::Music backgroundMusic;
        sf::Image cursorImg;
        sf::Cursor arrowC;
        sf::Cursor handC;
        sf::Image icon;
        float tick;
        float timerTick;
        sf::CircleShape selectBox;
        GUI_Button shipsButton;
        GUI_Button parseButton;
        sf::Text title;
        StarGUI stargui;
        sf::Event event;
        GUI_Button buttons[6];
        sf::Vector2i mousePos;
        bool isHoveringCursor;
        GUI_Panel upGUI;
        Menu menuScreen;
        sf::Time dt;
        sf::Clock clock;
        bool hasSelectedStar;
        bool lookingAtPlanet;
        bool selectBoxVisible;

    // TEMP
        Battle sampleBattle;
        BattleMap battleMap;

    private:  
        static void openEconomicsTab() {
            openTab = Tabs::economic;
        }

        static void openPlayerEmpireTab() {
            openTab = Tabs::playerEmpire;
        }

        static void openBuildingTab() {
            openTab = Tabs::building;
        }

        static void openShipsTab() {
            openTab = Tabs::ships;
        }

        static void openShipsBuildTab() {
            openTab = Tabs::buildShips;
        }

        static void openResearchTab() {
            openTab = Tabs::research;
        }

        static void quitGame() {
            state = GameStates::quit;
        }

        static void closeTab() {
            //std::cout << "Close!"<< std::endl;
            openTab = Tabs::none;
        }

        static void empty() {

        }

        static void startNewGame();
        static void loadOldGame();
    private:  
        void createButtons(GUI_Button buttons[]);
};

#endif