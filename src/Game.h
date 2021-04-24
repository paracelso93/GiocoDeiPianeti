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
#include "SpaceshipAnalizeTab.h"

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
        Game() : mWindow(sf::VideoMode(constants::SCREENX, constants::SCREENY), "GIOCO DEI PIANETI") {}
        ~Game() {}
        void setup();
        void getInput();
        void update();
        void render();
        void clear() {}
        bool getClose() { return !(this->mWindow.isOpen()); }

    private:  
        sf::RenderWindow mWindow;
        static DysonSphere mStartingSphere;
        static GameStates mState;
        static Empire mEmpires[2];
        static Star* mStars;
        static PlayerEmpire mPlayerEmpire;
        static sf::Font mFont;
        

    private:
        sf::Texture mLoadingTexture;
        sf::Sprite mLoadingSprite;
        sf::View mStarview;
        float mMouseWheelDelta;
        Movement mMovement;
        float mAnimationCountDown;
        float mAnimationTime;
        sf::Music mBackgroundMusic;
        sf::Image mCursorImg;
        sf::Cursor mArrowC;
        sf::Cursor mHandC;
        sf::Image mIcon;
        float mTick;
        float mTimerTick;
        sf::CircleShape mSelectBox;
        GUI_Button mShipsButton;
        GUI_Button mParseButton;
        sf::Text mTitle;
        StarGUI mStargui;
        sf::Event mEvent;
        GUI_Button mButtons[6];
        sf::Vector2i mMousePos;
        bool mIsHoveringCursor;
        GUI_Panel mUpGUI;
        Menu mMenuScreen;
        sf::Time mDt;
        sf::Clock mClock;
        bool mHasSelectedStar;
        bool mLookingAtPlanet;
        bool mSelectBoxVisible;

    // TEMP
        Battle mSampleBattle;
        BattleMap mBattleMap;

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

        static void openAnalizeShipTab() {
            openTab = Tabs::analizeShips;
        }

        static void quitGame() {
            mState = GameStates::quit;
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