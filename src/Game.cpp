#include "Game.h"

DysonSphere Game::mStartingSphere = DysonSphere();
GameStates Game::mState = GameStates::battle;
Empire Game::mEmpires[2] = {Empire(), Empire()};
Star* Game::mStars = nullptr;
PlayerEmpire Game::mPlayerEmpire = PlayerEmpire();
sf::Font Game::mFont = sf::Font();

void Game::createButtons(GUI_Button buttons[]) {
    sf::RectangleShape buttonShape({40, 40});
    
    buttonShape.setPosition({625.f, 25.f});
    buttons[1].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">", 15);
    buttons[1].setFunction([]() { TimeController::mTimeDilation += 1; });

    buttonShape.setPosition({675.f, 25.f});
    buttons[0].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">>", 15);
    buttons[0].setFunction([]() { TimeController::mTimeDilation += 10; });

    buttonShape.setPosition({725.f, 25.f});
    buttons[2].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">>>", 15);
    buttons[2].setFunction([]() { TimeController::mTimeDilation += 100; });

    buttonShape.setPosition({845.f, 25.f});
    buttons[3].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<<<", 15);
    buttons[3].setFunction([]() { if(TimeController::mTimeDilation > 100) TimeController::mTimeDilation -= 100; });

    buttonShape.setPosition({895.f, 25.f});
    buttons[4].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<<", 15);
    buttons[4].setFunction([]() { if(TimeController::mTimeDilation > 10) TimeController::mTimeDilation -= 10; });

    buttonShape.setPosition({945.f, 25.f});
    buttons[5].setup(mFont, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<", 15);
    buttons[5].setFunction([]() { if(TimeController::mTimeDilation > 1) TimeController::mTimeDilation -= 1; });
}

void Game::startNewGame() {
   Parser::createGalaxy(mStars);
   mState = GameStates::game;
   // bool endLoop1 = false;
   // bool endLoop2 = false;
   bool hasShip = false;
    for(int i = 0; i < constants::GRIDSIDENUMBER; i++) {
        for(int j = 0; j < constants::GRIDSIDENUMBER; j++) {
            if(mStars[i * constants::GRIDSIDENUMBER + j].mExists) {
                if(mStars[i * constants::GRIDSIDENUMBER + j].mNumP != 0 && !hasShip) {
                    mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mX = constants::STARGUIX + mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mDistance;
                    mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mY = constants::STARGUIY + (mStars[i * constants::GRIDSIDENUMBER + j].mGuiShape.getRadius() - (mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mRadius));
                    //ship.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Santa Maria", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 0, 0.1f, 20);
                    //ship2.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Niña", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 40, 0.1f, 20);
                    mPlayerEmpire.setup(&mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0], {i, j}, &mStars[i * constants::GRIDSIDENUMBER + j], sf::Color::Green, 1, mFont, "IMPERIUM OF MAN", openEconomicsTab, openShipsTab, openResearchTab, openPlayerEmpireTab);
                    mPlayerEmpire.setRace("../Assets/human.jpg");
                    mPlayerEmpire.setFlag("../Assets/imperiumFlag.png");
                    mPlayerEmpire.setLeaderName("Lord Protettore Antonino III\n Cannavacciuolo");
                    
                    PlayerEmpireTab::setPlayerEmpire(&mPlayerEmpire);
                    //SpaceshipTab::addSpaceship(&ship);
                    //SpaceshipTab::addSpaceship(&ship2);
                    mStartingSphere.setTexture("../Assets/epicBuildingSprites/dyson.png");
                    mStartingSphere.setup(&mStars[i * constants::GRIDSIDENUMBER + j], 1);

                    mPlayerEmpire.createDysonSphere(&mStartingSphere);
                    hasShip = true;

                    for(auto build : BuildingsParser::mBuildings) {
                        BuildTab::addBuilding(build, &mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0], &mPlayerEmpire);
                        mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mAvailableBuildings.push_back(build);
                    }
                    int ind = 0;
                    for(auto ship : SpaceshipsParser::mSpaceships) {
                        //ship->position(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 0, 0, ind * 40);
                        mPlayerEmpire.mAvailableShips.push_back(ship);
                        //SpaceshipTab::addSpaceship(ship);
                        SpaceshipBuildTab::addSpaceship(ship, &mStars[i * constants::GRIDSIDENUMBER + j], &mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0], ind * 40);
                        ind ++;
                    }

                    for(auto res : ResearchParser::mResearches) {
                        ResearchTab::addResearch(res);
                        //playerEmpire.availbleResearches.push_back(res);
                        ResearchTab::setEmpire(&mPlayerEmpire);
                    }
                    
                    /*if(!endLoop1) {
                        empires[0].setup(&stars[i * constants::GRIDSIDENUMBER + j].planets[0], {i, j}, &stars[i * constants::GRIDSIDENUMBER + j], sf::Color(255, 50, 50, 255), 1);
                        endLoop1 = true;
                    } else if(!endLoop2) {
                        empires[1].setup(&stars[i * constants::GRIDSIDENUMBER + j].planets[0], {i, j}, &stars[i * constants::GRIDSIDENUMBER + j], sf::Color(50, 50, 255, 255), 2);
                        endLoop2 = true;
                    } else {
                        if(rand() %2 == 0) {
                            empires[0].conquerPlanet(&stars[i * constants::GRIDSIDENUMBER + j].planets[0],  &stars[i * constants::GRIDSIDENUMBER + j], {i, j});
                        } else {
                            empires[1].conquerPlanet(&stars[i * constants::GRIDSIDENUMBER + j].planets[0],  &stars[i * constants::GRIDSIDENUMBER + j], {i, j});
                        }
                    }*/
                }
            }
            //if(endLoop) {
            //    break;
            //}
        }
        //if(endLoop) {
        //    break;
        //}
    }
}

void Game::loadOldGame() {
    Parser::parseGalaxy(mStars);
    mState = GameStates::game;
    bool hasShip = false;
    for(int i = 0; i < constants::GRIDSIDENUMBER; i++) {
        for(int j = 0; j < constants::GRIDSIDENUMBER; j++) {
            if(mStars[i * constants::GRIDSIDENUMBER + j].mExists) {
                if(mStars[i * constants::GRIDSIDENUMBER + j].mNumP != 0 && !hasShip) {
                    mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mX = constants::STARGUIX + mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mDistance;
                    mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mY = constants::STARGUIY + (mStars[i * constants::GRIDSIDENUMBER + j].mGuiShape.getRadius() - (mStars[i * constants::GRIDSIDENUMBER + j].mPlanets[0].mRadius));
                    //ship.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Santa Maria", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 0, 0.1f, 100);
                    //ship2.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Santa Maria", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 40, 0.1f, 20);
                    hasShip = true;
                    
                }
            }
        }
    }
}

void Game::setup() {
    //sf::VideoMode windowSize(constants::SCREENX, constants::SCREENY);
    //window = sf::RenderWindow(windowSize, "SPACE");

    mLoadingTexture.loadFromFile("../Assets/gui/loading.png");
    
    mLoadingSprite.setTexture(mLoadingTexture);

    BuildingsParser::setup();
    SpaceshipsParser::setup();
    SpaceshipPartParser::setup();
    ResearchParser::setup();

    openTab = Tabs::analizeShips;

    mWindow.clear();

    mWindow.draw(mLoadingSprite);

    mWindow.display();


    //std::cout << "obama" << std::endl;
    mMouseWheelDelta = 1.f;

    mStars = new Star[constants::GRIDSIDENUMBER * constants::GRIDSIDENUMBER];

    mStarview = sf::View(sf::FloatRect(0, constants::UPPERGUIHEIGHT, constants::SCREENX, constants::SCREENY - constants::UPPERGUIHEIGHT));
    mStarview.setViewport(sf::FloatRect(0, 1.f / 11.f, 1.f, 10.f / 11.f));

    mMovement.setup();

    //Animation anim;
    //anim.setup("../Assets/cruiserAnimation.png", 10, 1, 10, 21, 130);
    //anim.setPosition({100, 100});
    //anim.setScale({10, 10});

    mAnimationCountDown = 0.1f;
    mAnimationTime = 0.f;

    if(!mFont.loadFromFile("../Assets/gui/aspace_demo.otf")) {
        std::cout << "Can't load Font!";
        return;
    }
    mState = GameStates::menu;
    
    if(!mBackgroundMusic.openFromFile("../Assets/music/newdawn.wav")) {
        std::cout << "couln't load music!\n";
        return;
    }

    mCursorImg.loadFromFile("../Assets/gui/cursor.png");
    
    mArrowC.loadFromPixels(mCursorImg.getPixelsPtr(), {16, 16}, {0, 0});
    mCursorImg.loadFromFile("../Assets/gui/cursor.png");
    
    mHandC.loadFromPixels(mCursorImg.getPixelsPtr(), {16, 16}, {0, 0});
    mBackgroundMusic.setLoop(true);
    //mBackgroundMusic.play();
    mWindow.setMouseCursor(mArrowC);
    
    mIcon.loadFromFile("../Assets/gui/icon.png");
    mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

    sf::Color colors[2] = {sf::Color::Green, sf::Color::Green};
    std::string strings[2] = {" ", " "};
    void (*functions[2])() = {[] (){}, [] (){}};

    GUI_Alert::setup(sf::Color::Blue, "", "", sf::Color::White, 2, colors, strings, mFont, functions);

    mTick = 10.f * (500.f / TimeController::mTimeDilation);
    mTimerTick = 0.f;

    mSelectBox.setRadius(constants::GRIDSIDELENGTH / 2.f);
    mSelectBox.setOutlineColor(sf::Color::Green);
    mSelectBox.setOutlineThickness(2.f);
    mSelectBox.setFillColor(sf::Color(0, 0, 0, 0));

    EconomicsTab::setup(mFont, closeTab);
    EconomicsTab::update(mPlayerEmpire.getFunds(), 1, 0);

    SpaceshipBuildTab::setup(mFont, closeTab);
    SpaceshipBuildTab::setEmpire(&mPlayerEmpire);
    //EconomicsTab::visible = false;

    BuildTab::setup(mFont, closeTab);

    SpaceshipTab::setup(mFont, closeTab);
    ResearchTab::setup(mFont, closeTab);
    PlayerEmpireTab::setup(mFont, closeTab);
    SpaceshipAnalizeTab::setup(mFont, closeTab);

    //Animation publicGoal;
    //publicGoal.setup("../Assets/spaceshipSprites/publicGoal.png", 29, 6, 5, 2988, 2490);
    
    sf::RectangleShape obama;
    obama.setSize({80, 80});
    obama.setPosition(525, 10);

    mParseButton.setup(mFont, obama, {100, 100, 100, 255}, {200, 100, 100, 255}, "PARSE", 18);

    mTitle.setFont(mFont);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setCharacterSize(40);
    mTitle.setPosition(50, 25);
    mTitle.setString("GIOCO DEI PIANETI");

    if(mState == GameStates::battle)
        startNewGame();

    mSampleBattle.setup(0, 1);
    
    mBattleMap.setup(20, 8);
    mSampleBattle.setMap(&mBattleMap);
    int owo = 0;
    for(auto s : mPlayerEmpire.mAvailableShips) {
        mSampleBattle.setSpaceship(((owo < 2) ? 0 : 1), s);
        owo ++;
    }
    //owo = 0;
    //for(auto s : mPlayerEmpire.availbleShips) {
    //    mSampleBattle.setSpaceship(((owo < 2) ? 0 : 1), s);
    //    owo ++;
    //}
    //sampleBattle.setSpaceship(0, mPlayerEmpire.availbleShips[0]);
    //sampleBattle.setSpaceship(0, mPlayerEmpire.availbleShips[1]);
    //sampleBattle.setSpaceship(1, mPlayerEmpire.availbleShips[2]);
    //sampleBattle.setSpaceship(1, mPlayerEmpire.availbleShips[3]);
    mSampleBattle.generateBattlePositions(0, 1);
    //std::cout << "obama" << std::endl;
    
    mStargui.setup(TimeController::mTimeDilation, mFont, openBuildingTab, openShipsBuildTab);

    mSelectBoxVisible = false;

    //sf::Shader shader;
    //if(!shader.loadFromFile("../Assets/shaders/border_shader.vert", "../Assets/shaders/border_shader.frag")) {
    //    std::cerr << "Unable to load shader" << std::endl;
    //    return;
    //}

    //std::vector<Building *> bees;

    //BuildingsParser::parse(bees);

    createButtons(mButtons);

    srand(time(NULL));

    /*char scelta;

    std::cout << "VUOI CARICARE SPAZIO DA FILE O CREARNE UNO NUOVO?\n\t<c>carica\t<n>nuovo\n";
    scelta = std::cin.get();

    if (scelta == 'n')
    {
        Parser::createGalaxy(stars, GRIDSIDENUMBER, GRIDSIDELENGTH);
    }
    else
    {

        Parser::parseGalaxy(stars, GRIDSIDENUMBER);
    }*/

    mMousePos = sf::Mouse::getPosition(mWindow);

    mIsHoveringCursor = false;

    mUpGUI.setup({5, 5}, {constants::SCREENX - 10, 90}, sf::Color::Blue, sf::Color::Yellow, mFont, [] (){});
    /*sf::RectangleShape upGUI({constants::SCREENX - 10, 90});
    upGUI.setFillColor(sf::Color::Blue);
    upGUI.setPosition({5, 5});
    upGUI.setOutlineThickness(5);
    upGUI.setOutlineColor(sf::Color::Yellow);*/

    mMenuScreen.setup(mFont, startNewGame, loadOldGame, quitGame);

    mHasSelectedStar = false;
    mMousePos = sf::Vector2i(0, 0);
    mLookingAtPlanet = false;
}

void Game::getInput() {
    if(mState == GameStates::quit) {
        mWindow.close();
    }

    mDt = mClock.restart();
    mTimerTick += mDt.asSeconds();
    while (mWindow.pollEvent(mEvent))
    {
        bool moving = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            mMovement.movingUp = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            mMovement.movingDown = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            mMovement.movingLeft = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            mMovement.movingRight = true;
            moving = true;
        }
        if(!moving) {
            mMovement.movingUp = false;
            mMovement.movingDown = false;
            mMovement.movingLeft = false;
            mMovement.movingRight = false;
        }
        switch (mEvent.type)
        {
        case sf::Event::KeyPressed:
            if(mEvent.key.code == sf::Keyboard::Escape) {
                mState = GameStates::menu;
            }

        break;

        case sf::Event::Closed:
            mWindow.close();
            break;

        case sf::Event::MouseButtonPressed:
            if(mState == GameStates::game) {
                if(mStargui.mVisible) {
                    if(mStargui.update(mMousePos)) {
                        mLookingAtPlanet = true;
                        break;
                    } else {
                        mLookingAtPlanet = false;
                    }
                }
                for(int i = 0; i < 6; i++) {
                    if(mButtons[i].checkForClick(mMousePos)) {
                        mButtons[i].click();
                        mStargui.mTimeDilationText.setString(std::to_string((int)TimeController::mTimeDilation) + "X");
                    }
                }
                if(mParseButton.checkForClick(mMousePos)) {
                    Parser::parseGalaxy(mStars);
                }

                mPlayerEmpire.update(mMousePos);
                switch(openTab) {
                    case Tabs::economic: 
                        EconomicsTab::getInput(mMousePos);
                        break;
                    case Tabs::building:   
                        BuildTab::getInput(mMousePos);
                        break;
                    case Tabs::ships:  
                        SpaceshipTab::getInput(mMousePos);
                        break;
                    case Tabs::buildShips:   
                        SpaceshipBuildTab::getInput(mMousePos);
                        break;
                    case Tabs::research:   
                        ResearchTab::getInput(mMousePos);
                        break;
                    case Tabs::playerEmpire:   
                        PlayerEmpireTab::getInput(mMousePos);
                        break;
                    case Tabs::analizeShips:
                        SpaceshipAnalizeTab::getInput(mMousePos);
                        break;
                    default:  break;
                }
                GUI_Alert::getInput(mMousePos);

            } else if(mState == GameStates::menu) {
                mMenuScreen.checkForClicks(mMousePos);
            } else if(mState == GameStates::battle) {
                mSampleBattle.getInput(mMousePos);
            }
                mLookingAtPlanet = false;
            break;

        case sf::Event::MouseButtonReleased:
            //std::cout << "mMousePos: " << mMousePos.x << ":" << mMousePos.y << std::endl;
            if(mState == GameStates::game) {
                if(!mLookingAtPlanet) {
                    mSelectBoxVisible = false;
                    for (int i = 0; i < constants::GRIDSIDENUMBER; i++)
                    {
                        for (int j = 0; j < constants::GRIDSIDENUMBER; j++)
                        {
                            sf::RectangleShape shape;
                            sf::Vector2f newMousePos = mWindow.mapPixelToCoords(mMousePos, mStarview);
                            shape.setPosition(i * constants::GRIDSIDELENGTH, j * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
                            //shape.setPosition(
                            //    i * constants::GRIDSIDELENGTH * (1000 / starview.getSize().x) - (((1000 - starview.getSize().x) / 2000) * 1000) * (1000 / starview.getSize().x) - (starview.getCenter().x - starview.getSize().x * mouseWheelDelta / 2) / mouseWheelDelta,
                            //    j * constants::GRIDSIDELENGTH * (1000 / starview.getSize().y) + 100 - (((1000 - starview.getSize().y) / 2000) * 1000) * (1000 / starview.getSize().y) - (starview.getCenter().y - starview.getSize().y * mouseWheelDelta / 2 - 100) / mouseWheelDelta
                            //);
                            
                            shape.setSize(sf::Vector2f(constants::GRIDSIDELENGTH * (1 / mMouseWheelDelta), constants::GRIDSIDELENGTH * (1 / mMouseWheelDelta)));
                            if (shape.getGlobalBounds().contains(newMousePos))
                            {
                                if (mStars[i * constants::GRIDSIDENUMBER + j].mExists)
                                {
                                    if(mStargui.mVisible) {
                                        if(mMousePos.y > 600.f + constants::UPPERGUIHEIGHT) {
                                            break;
                                        }
                                    }
                                    if(openTab != Tabs::none) {
                                        if(mMousePos.y < constants::UPPERGUIHEIGHT + 600.f && mMousePos.x < 405.f) {
                                            break;
                                        }
                                    }
                                    if(mStargui.mPlanetDescriptionVisible) {
                                        if(mMousePos.y < constants::STARGUIX * 2 && mMousePos.x > constants::PLANETDESCRIPTIONX) {
                                            break;
                                        }
                                    }
                                    if(GUI_Alert::mVisible) {
                                        if(mMousePos.y > 390 && mMousePos.y < 690 && mMousePos.x > 710 && mMousePos.x < 1210) {
                                            break;
                                        }
                                    }
                                    if(mMousePos.y < constants::UPPERGUIHEIGHT) {
                                        break;
                                    }
                                    //std::cout << starview.getCenter().x << ":" << starview.getCenter().y << std::endl;
                                    //std::cout << "position: " << i * constants::GRIDSIDELENGTH * mouseWheelDelta << ":" << j * constants::GRIDSIDELENGTH * mouseWheelDelta << std::endl;
                                    //std::cout << "Position: " <<  i * constants::GRIDSIDELENGTH + starview.getCenter().x - 500 << ":" << j * constants::GRIDSIDELENGTH + starview.getCenter().y - 500 << std::endl;
                                    //std::cout << "Ponk!\n";
                                    //stars[i * GRIDSIDENUMBER + j].color = sf::Color::White;
                                    mSelectBoxVisible = true;
                                    mSelectBox.setPosition(sf::Vector2f(i * constants::GRIDSIDELENGTH, j * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT));
                                    mSelectBoxVisible = true;
                                    mStargui.setStar(mStars[i * constants::GRIDSIDENUMBER + j]);
                                    mStargui.setVisible(true);
                                }
                            }
                        }
                    }
                }
                if (!mSelectBoxVisible)
                {
                    bool des = true;
                    for(int i = 0; i < 6; i++) {
                        if(mButtons[i].isClick()) {
                            mButtons[i].deselect();
                            des = false;
                        }
                    }
                    //if(des) {
                        
                        //ship.setTarget(mWindow.mapPixelToCoords(mMousePos, starview));
                    //}
                }
            } else if(mState == GameStates::menu) {

            } else if(mState == GameStates::battle) {

            }
            break;

        case sf::Event::MouseWheelScrolled:

            mMouseWheelDelta += mEvent.mouseWheel.x / 10000000000.f;
            if(mMouseWheelDelta <= 0) {
                mMouseWheelDelta = 0.2f;
            }
            if(mMouseWheelDelta >= 4) {
                mMouseWheelDelta = 4;
            }
            if(mMouseWheelDelta != 0) {
                mStarview.setSize(constants::SCREENX * mMouseWheelDelta, (constants::SCREENY - constants::UPPERGUIHEIGHT) * mMouseWheelDelta);
            }
            break;

        default:
            break;
        }
    }
}

void Game::update() {
    mMousePos = sf::Mouse::getPosition(mWindow);

    if (mStargui.mVisible)
    {
        for (int o = 0; o < mStargui.mCurrentStar.mNumP; o++)
        {
            //std::cout << "dist: " << stargui.currentStar.planets[o].distance << std::endl;
            mStargui.mCurrentStar.mPlanets[o].mAngle += mStargui.mCurrentStar.mPlanets[o].mAngularVelocity * mDt.asSeconds() * TimeController::mTimeDilation;
            mStargui.mCurrentStar.mPlanets[o].mX = mStargui.mCurrentStar.mGuiShape.getPosition().x + mStargui.mCurrentStar.mGuiShape.getRadius() + std::cos(mStargui.mCurrentStar.mPlanets[o].mAngle) * mStargui.mCurrentStar.mPlanets[o].mDistance;
            mStargui.mCurrentStar.mPlanets[o].mY = mStargui.mCurrentStar.mGuiShape.getPosition().y + mStargui.mCurrentStar.mGuiShape.getRadius() + std::sin(mStargui.mCurrentStar.mPlanets[o].mAngle) * mStargui.mCurrentStar.mPlanets[o].mDistance - (mStargui.mCurrentStar.mPlanets[o].mRadius);
            for (int p = 0; p < mStargui.mCurrentStar.mPlanets[o].mNumn; p++)
            {
                mStargui.mCurrentStar.mPlanets[o].mMoons[p].mAngle += mStargui.mCurrentStar.mPlanets[o].mMoons[p].mAngularVelocity * mDt.asSeconds() * TimeController::mTimeDilation * 500;
                mStargui.mCurrentStar.mPlanets[o].mMoons[p].mX = mStargui.mCurrentStar.mPlanets[o].mX + mStargui.mCurrentStar.mPlanets[o].mRadius + std::cos(mStargui.mCurrentStar.mPlanets[o].mMoons[p].mAngle) * mStargui.mCurrentStar.mPlanets[o].mMoons[p].mDistance;
                mStargui.mCurrentStar.mPlanets[o].mMoons[p].mY = mStargui.mCurrentStar.mPlanets[o].mY + mStargui.mCurrentStar.mPlanets[o].mRadius + std::sin(mStargui.mCurrentStar.mPlanets[o].mMoons[p].mAngle) * mStargui.mCurrentStar.mPlanets[o].mMoons[p].mDistance - (mStargui.mCurrentStar.mPlanets[o].mMoons[p].mRadius);
            }
        }
    }

    bool hovering = false;
    if(mState == GameStates::game) {
        ResearchTab::update(mDt.asSeconds());
        if(mStargui.mVisible) {
            mSelectBoxVisible = true;
        } else {
            mSelectBoxVisible = false;
        }
        mTick = 10.f * (500.f / TimeController::mTimeDilation);
        if(mTimerTick >= mTick) {
            mTimerTick = 0;
            // UPDATE EVERYTHING;
            mPlayerEmpire.setFunds(mPlayerEmpire.getFunds() + mStartingSphere.getProduction());
        }

        if(mAnimationTime >= mAnimationCountDown) {
            // UPDATE ANIMATIONS
            //anim.update();
            //publicGoal.update();
            mAnimationTime = 0;
        } else {
            mAnimationTime += mDt.asSeconds();
        }

        for(int k = 0; k < 6; k++) {
            if(mButtons[k].checkForClick(mMousePos)) {
                hovering = true;
            }
        }
        if(mParseButton.checkForClick(mMousePos)) {
            hovering = true;
        }

        for(int k = 0; k < constants::GRIDSIDENUMBER; k++) {
            for(int p = 0; p < constants::GRIDSIDENUMBER; p++) {
                if(mStars[k * constants::GRIDSIDENUMBER + p].mExists) {
                    sf::RectangleShape shape;
                    shape.setPosition(k * constants::GRIDSIDELENGTH, p * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
                    shape.setSize(sf::Vector2f(constants::GRIDSIDELENGTH, constants::GRIDSIDELENGTH));

                    if(shape.getGlobalBounds().contains(mMousePos.x, mMousePos.y)) {
                        hovering = true;
                    }
                }
            }
        }

        if(mStargui.mVisible) {
            if(mStargui.hoveringOnPlanet(mMousePos)) {
                hovering = true;
            }
        }
        //ship.update();
        //ship2.update();
        //std::cout << "OBAMA" << std::endl;
        for(auto ship : mPlayerEmpire.mSpaceships) {
            ship->update();
        }
        
        EconomicsTab::update(mPlayerEmpire.getFunds(), 1, 0);

        /*switch(openTab) {
            case economic: 
                EconomicsTab::visible = true;
                break;
            default:   
                EconomicsTab::visible = false;
                break;
        }*/
        
    }


    if((mMenuScreen.checkForHover(mMousePos) && mState == GameStates::menu) || hovering) {
        mWindow.setMouseCursor (mHandC);
        mIsHoveringCursor = true;
    } else if(mIsHoveringCursor) {
        mWindow.setMouseCursor (mArrowC);
        mIsHoveringCursor = false;
    }


    sf::Vector2f movementVector;
    if(mMovement.movingUp) {
        movementVector.y = -1000.f * mDt.asSeconds();
    }
    if(mMovement.movingDown) {
        movementVector.y = 1000.f * mDt.asSeconds();
    }
    if(mMovement.movingLeft) {
        movementVector.x = -1000.f * mDt.asSeconds();
    }
    if(mMovement.movingRight) {
        movementVector.x = 1000.f * mDt.asSeconds();
    }

    mStarview.move(movementVector);



    //std::cout << starview.getCenter().x << ":" << starview.getCenter().y << std::endl;
    //mWindow.setTitle(std::to_string((int)(1.f / mDt.asSeconds())));
}

void Game::render() {
    mWindow.clear();

    //for(int i = 0; i < windowSize.height; i += GRIDSIDELENGTH) {
    //    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(i, 0)), sf::Vertex(sf::Vector2f(i, windowSize.height)) };
    //    window.draw(line, 2,  sf::Lines);
    //    sf::Vertex otherLine[] = { sf::Vertex(sf::Vector2f(0, i)), sf::Vertex(sf::Vector2f(windowSize.height, i)) };
    //    window.draw(otherLine, 2,  sf::Lines);
    //}
    if(mState == GameStates::game) {
        // sf::CircleShape s;
        //s.setPosition(starview.getCenter().x - 10, starview.getCenter().y - 10);
        //s.setRadius(10);
        // s.setFillColor(sf::Color::Green);

        mWindow.setView(mStarview);
        //mWindow.draw(s);
        //empires[0].render(&mWindow);
        //empires[1].render(&mWindow);
        mPlayerEmpire.render(mWindow);
        int starti = 0, endi = 50;
        if(mStarview.getCenter().x <= 960 * mMouseWheelDelta) {
            starti = 0;
            endi = 50 * mMouseWheelDelta;
        } else if(mStarview.getCenter().x >= 9000 * mMouseWheelDelta) {
            starti = 200 * mMouseWheelDelta;
            endi = constants::GRIDSIDENUMBER;
        } else {
            starti = (int)((mStarview.getCenter().x - 960 * mMouseWheelDelta) / constants::GRIDSIDELENGTH);
            endi = (int)((mStarview.getCenter().x + 960 * mMouseWheelDelta) / constants::GRIDSIDELENGTH);
        }
        int startj = 0, endj = 25;
        if(mStarview.getCenter().y <= 600 * mMouseWheelDelta) {
            startj = 0 * mMouseWheelDelta;
            endj = 26 * mMouseWheelDelta;
        } else if(mStarview.getCenter().y >= 9000 * mMouseWheelDelta) {
            startj = 224 * mMouseWheelDelta;
            endj = constants::GRIDSIDENUMBER;
        }  else {
            startj = (int)((mStarview.getCenter().y - 600 * mMouseWheelDelta) / constants::GRIDSIDELENGTH);
            endj = (int)((mStarview.getCenter().y + 500 * mMouseWheelDelta) / constants::GRIDSIDELENGTH);
        }
        for (int i = starti; i < endi ; i++)
        {
            for (int j = startj; j < endj; j++)
            {
                int currentIndex = j + i * constants::GRIDSIDENUMBER;
                if (mStars[currentIndex].mExists)
                {
                    //std::cout << stars[currentIndex].radius / SOLARRADIUS << " P:" << stars[currentIndex].x<< ":" << stars[currentIndex].y <<  std::endl;
                    sf::CircleShape starCircle(mStars[currentIndex].mShape.getRadius());
                    starCircle.setFillColor(mStars[currentIndex].mColor);
                    starCircle.setPosition(mStars[currentIndex].mX, mStars[currentIndex].mY + constants::UPPERGUIHEIGHT);
                    mWindow.draw(starCircle);
                }
            }
        }


        if (mSelectBoxVisible)
        {
            mWindow.draw(mSelectBox);
        }


        mWindow.setView(mWindow.getDefaultView());

        if (mStargui.mVisible)
        {
            mStargui.render(mWindow, TimeController::mTimeDilation, mEmpires, mPlayerEmpire);
        }

        
        //ship.render(&mWindow, &mStargui.currentStar, mStargui.visible, starview);
        //ship2.render(&mWindow, &mStargui.currentStar, mStargui.visible, starview);
        for(auto ship : mPlayerEmpire.mSpaceships) {
            ship->render(mWindow, &mStargui.mCurrentStar, mStargui.mVisible, mStarview);
        }
        mUpGUI.render(mWindow);
        switch(openTab) {
            case Tabs::economic: EconomicsTab::render(mWindow);
                    break;
            case Tabs::building: BuildTab::render(mWindow);
                    break;
            case Tabs::ships: SpaceshipTab::render(mWindow);
                    break;
            case Tabs::buildShips: SpaceshipBuildTab::render(mWindow);
                    break;
            case Tabs::research: ResearchTab::render(mWindow);
                    break;
            case Tabs::playerEmpire: PlayerEmpireTab::render(mWindow);
                    break;
            case Tabs::analizeShips: SpaceshipAnalizeTab::render(mWindow);
            default:  break;
        }
        mWindow.draw(mStargui.mTimeDilationText);
        mWindow.draw(mTitle);

        mPlayerEmpire.renderGUI(mWindow);

        for(int i = 0; i < 6; i++) {
            mButtons[i].render(mWindow);
        }
        //anim.render(&mWindow);
        //publicGoal.render(&mWindow);
        mParseButton.render(mWindow);
        GUI_Alert::render(mWindow);
    } else if(mState == GameStates::menu) {
        mWindow.setView(mWindow.getDefaultView());
        mMenuScreen.render(mWindow);
    } else if(mState == GameStates::battle) {
        mSampleBattle.render(mWindow);
    }
    mWindow.display();
}