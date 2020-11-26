#include "Game.h"

DysonSphere Game::startingSphere = DysonSphere();
GameStates Game::state = GameStates::battle;
Empire Game::empires[2] = {Empire(), Empire()};
Star* Game::stars = nullptr;
PlayerEmpire Game::playerEmpire = PlayerEmpire();
sf::Font Game::font = sf::Font();

void Game::createButtons(GUI_Button buttons[]) {
    sf::RectangleShape buttonShape({40, 40});
    
    buttonShape.setPosition({625.f, 25.f});
    buttons[1].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">", 15);
    buttons[1].setFunction([]() { TimeController::timeDilation += 1; });

    buttonShape.setPosition({675.f, 25.f});
    buttons[0].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">>", 15);
    buttons[0].setFunction([]() { TimeController::timeDilation += 10; });

    buttonShape.setPosition({725.f, 25.f});
    buttons[2].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, ">>>", 15);
    buttons[2].setFunction([]() { TimeController::timeDilation += 100; });

    buttonShape.setPosition({845.f, 25.f});
    buttons[3].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<<<", 15);
    buttons[3].setFunction([]() { if(TimeController::timeDilation > 100) TimeController::timeDilation -= 100; });

    buttonShape.setPosition({895.f, 25.f});
    buttons[4].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<<", 15);
    buttons[4].setFunction([]() { if(TimeController::timeDilation > 10) TimeController::timeDilation -= 10; });

    buttonShape.setPosition({945.f, 25.f});
    buttons[5].setup(font, buttonShape, {150, 156, 163, 255}, {93, 99, 107, 255}, "<", 15);
    buttons[5].setFunction([]() { if(TimeController::timeDilation > 1) TimeController::timeDilation -= 1; });
}

void Game::startNewGame() {
   Parser::createGalaxy(stars);
   //state = GameStates::game;
   // bool endLoop1 = false;
   // bool endLoop2 = false;
   bool hasShip = false;
    for(int i = 0; i < constants::GRIDSIDENUMBER; i++) {
        for(int j = 0; j < constants::GRIDSIDENUMBER; j++) {
            if(stars[i * constants::GRIDSIDENUMBER + j].exists) {
                if(stars[i * constants::GRIDSIDENUMBER + j].nump != 0 && !hasShip) {
                    stars[i * constants::GRIDSIDENUMBER + j].planets[0].x = constants::STARGUIX + stars[i * constants::GRIDSIDENUMBER + j].planets[0].distance;
                    stars[i * constants::GRIDSIDENUMBER + j].planets[0].y = constants::STARGUIY + (stars[i * constants::GRIDSIDENUMBER + j].guiShape.getRadius() - (stars[i * constants::GRIDSIDENUMBER + j].planets[0].radius));
                    //ship.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Santa Maria", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 0, 0.1f, 20);
                    //ship2.setup(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 100, "La Niña", 0, 0, "../Assets/ship.png", SpaceShipTypes::Scout, 40, 0.1f, 20);
                    playerEmpire.setup(&stars[i * constants::GRIDSIDENUMBER + j].planets[0], {i, j}, &stars[i * constants::GRIDSIDENUMBER + j], sf::Color::Green, 1, font, "IMPERIUM OF MAN", openEconomicsTab, openShipsTab, openResearchTab, openPlayerEmpireTab);
                    playerEmpire.setRace("../Assets/human.jpg");
                    playerEmpire.setFlag("../Assets/imperiumFlag.png");
                    playerEmpire.setLeaderName("Lord Protettore Antonino III\n Cannavacciuolo");
                    
                    PlayerEmpireTab::setPlayerEmpire(&playerEmpire);
                    //SpaceshipTab::addSpaceship(&ship);
                    //SpaceshipTab::addSpaceship(&ship2);
                    startingSphere.setTexture("../Assets/epicBuildingSprites/dyson.png");
                    startingSphere.setup(&stars[i * constants::GRIDSIDENUMBER + j], 1);

                    playerEmpire.createDysonSphere(&startingSphere);
                    hasShip = true;

                    for(auto build : BuildingsParser::buildings) {
                        BuildTab::addBuilding(build, &stars[i * constants::GRIDSIDENUMBER + j].planets[0], &playerEmpire);
                        stars[i * constants::GRIDSIDENUMBER + j].planets[0].availbleBuildings.push_back(build);
                    }
                    int ind = 0;
                    for(auto ship : SpaceshipsParser::spaceships) {
                        //ship->position(&stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], 0, 0, ind * 40);
                        playerEmpire.availbleShips.push_back(ship);
                        //SpaceshipTab::addSpaceship(ship);
                        SpaceshipBuildTab::addSpaceship(ship, &stars[i * constants::GRIDSIDENUMBER + j], &stars[i * constants::GRIDSIDENUMBER + j].planets[0], ind * 40);
                        ind ++;
                    }

                    for(auto res : ResearchParser::researches) {
                        ResearchTab::addResearch(res);
                        //playerEmpire.availbleResearches.push_back(res);
                        ResearchTab::setEmpire(&playerEmpire);
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
    Parser::parseGalaxy(stars);
    state = GameStates::game;
    bool hasShip = false;
    for(int i = 0; i < constants::GRIDSIDENUMBER; i++) {
        for(int j = 0; j < constants::GRIDSIDENUMBER; j++) {
            if(stars[i * constants::GRIDSIDENUMBER + j].exists) {
                if(stars[i * constants::GRIDSIDENUMBER + j].nump != 0 && !hasShip) {
                    stars[i * constants::GRIDSIDENUMBER + j].planets[0].x = constants::STARGUIX + stars[i * constants::GRIDSIDENUMBER + j].planets[0].distance;
                    stars[i * constants::GRIDSIDENUMBER + j].planets[0].y = constants::STARGUIY + (stars[i * constants::GRIDSIDENUMBER + j].guiShape.getRadius() - (stars[i * constants::GRIDSIDENUMBER + j].planets[0].radius));
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

    loadingTexture.loadFromFile("../Assets/gui/loading.png");
    
    loadingSprite.setTexture(loadingTexture);

    BuildingsParser::setup();
    SpaceshipsParser::setup();
    SpaceshipPartParser::setup();
    ResearchParser::setup();

    openTab = Tabs::none;

    window.clear();

    window.draw(loadingSprite);

    window.display();


    //std::cout << "obama" << std::endl;
    mouseWheelDelta = 1.f;

    stars = new Star[constants::GRIDSIDENUMBER * constants::GRIDSIDENUMBER];

    starview = sf::View(sf::FloatRect(0, constants::UPPERGUIHEIGHT, constants::SCREENX, constants::SCREENY - constants::UPPERGUIHEIGHT));
    starview.setViewport(sf::FloatRect(0, 1.f / 11.f, 1.f, 10.f / 11.f));

    movement.setup();

    //Animation anim;
    //anim.setup("../Assets/cruiserAnimation.png", 10, 1, 10, 21, 130);
    //anim.setPosition({100, 100});
    //anim.setScale({10, 10});

    animationCountDown = 0.1f;
    animationTime = 0.f;

    if(!font.loadFromFile("../Assets/gui/aspace_demo.otf")) {
        std::cout << "Can't load Font!";
        return;
    }
    state = GameStates::battle;
    
    if(!backgroundMusic.openFromFile("../Assets/music/newdawn.wav")) {
        std::cout << "couln't load music!\n";
        return;
    }
    
    cursorImg.loadFromFile("../Assets/gui/cursor.png");
    
    arrowC.loadFromPixels(cursorImg.getPixelsPtr(), {16, 16}, {0, 0});
    cursorImg.loadFromFile("../Assets/gui/cursor.png");
    
    handC.loadFromPixels(cursorImg.getPixelsPtr(), {16, 16}, {0, 0});
    backgroundMusic.setLoop(true);
    //backgroundMusic.play();
    window.setMouseCursor(arrowC);
    
    icon.loadFromFile("../Assets/gui/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Color colors[2] = {sf::Color::Green, sf::Color::Green};
    std::string strings[2] = {" ", " "};
    void (*functions[2])() = {[] (){}, [] (){}};

    GUI_Alert::setup(sf::Color::Blue, "", "", sf::Color::White, 2, colors, strings, font, functions);

    tick = 10.f * (500.f / TimeController::timeDilation);
    timerTick = 0.f;

    selectBox.setRadius(constants::GRIDSIDELENGTH / 2.f);
    selectBox.setOutlineColor(sf::Color::Green);
    selectBox.setOutlineThickness(2.f);
    selectBox.setFillColor(sf::Color(0, 0, 0, 0));

    EconomicsTab::setup(font, closeTab);
    EconomicsTab::update(playerEmpire.getFunds(), 1, 0);

    SpaceshipBuildTab::setup(font, closeTab);
    SpaceshipBuildTab::setEmpire(&playerEmpire);
    //EconomicsTab::visible = false;

    BuildTab::setup(font, closeTab);

    SpaceshipTab::setup(font, closeTab);
    ResearchTab::setup(font, closeTab);
    PlayerEmpireTab::setup(font, closeTab);

    //Animation publicGoal;
    //publicGoal.setup("../Assets/spaceshipSprites/publicGoal.png", 29, 6, 5, 2988, 2490);
    
    sf::RectangleShape obama;
    obama.setSize({80, 80});
    obama.setPosition(525, 10);

    parseButton.setup(font, obama, {100, 100, 100, 255}, {200, 100, 100, 255}, "PARSE", 18);

    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(40);
    title.setPosition(50, 25);
    title.setString("GIOCO DEI PIANETI");

    if(state == GameStates::battle)
        startNewGame();

    sampleBattle.setup(0, 1);
    
    battleMap.setup(20, 8);
    sampleBattle.setMap(&battleMap);
    int owo = 0;
    for(auto s : playerEmpire.availbleShips) {
        sampleBattle.setSpaceship(((owo < 2) ? 0 : 1), s);
        owo ++;
    }
    //owo = 0;
    //for(auto s : playerEmpire.availbleShips) {
    //    sampleBattle.setSpaceship(((owo < 2) ? 0 : 1), s);
    //    owo ++;
    //}
    //sampleBattle.setSpaceship(0, playerEmpire.availbleShips[0]);
    //sampleBattle.setSpaceship(0, playerEmpire.availbleShips[1]);
    //sampleBattle.setSpaceship(1, playerEmpire.availbleShips[2]);
    //sampleBattle.setSpaceship(1, playerEmpire.availbleShips[3]);
    sampleBattle.generateBattlePositions(0, 1);
    std::cout << "obama" << std::endl;
    
    stargui.setup(TimeController::timeDilation, font, openBuildingTab, openShipsBuildTab);

    selectBoxVisible = false;

    //sf::Shader shader;
    //if(!shader.loadFromFile("../Assets/shaders/border_shader.vert", "../Assets/shaders/border_shader.frag")) {
    //    std::cerr << "Unable to load shader" << std::endl;
    //    return;
    //}

    //std::vector<Building *> bees;

    //BuildingsParser::parse(bees);

    createButtons(buttons);

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

    mousePos = sf::Mouse::getPosition(window);

    isHoveringCursor = false;

    upGUI.setup({5, 5}, {constants::SCREENX - 10, 90}, sf::Color::Blue, sf::Color::Yellow, font, [] (){});
    /*sf::RectangleShape upGUI({constants::SCREENX - 10, 90});
    upGUI.setFillColor(sf::Color::Blue);
    upGUI.setPosition({5, 5});
    upGUI.setOutlineThickness(5);
    upGUI.setOutlineColor(sf::Color::Yellow);*/

    menuScreen.setup(font, startNewGame, loadOldGame, quitGame);

    hasSelectedStar = false;
    mousePos = sf::Vector2i(0, 0);
    lookingAtPlanet = false;
}

void Game::getInput() {
    if(state == GameStates::quit) {
        window.close();
    }

    dt = clock.restart();
    timerTick += dt.asSeconds();
    while (window.pollEvent(event))
    {
        bool moving = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.movingUp = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.movingDown = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.movingLeft = true;
            moving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.movingRight = true;
            moving = true;
        }
        if(!moving) {
            movement.movingUp = false;
            movement.movingDown = false;
            movement.movingLeft = false;
            movement.movingRight = false;
        }
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) {
                state = GameStates::menu;
            }

        break;

        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if(state == GameStates::game) {
                if(stargui.visible) {
                    if(stargui.update(mousePos)) {
                        lookingAtPlanet = true;
                        break;
                    } else {
                        lookingAtPlanet = false;
                    }
                }
                for(int i = 0; i < 6; i++) {
                    if(buttons[i].checkForClick(mousePos)) {
                            buttons[i].click();
                            stargui.timeDilationText.setString(std::to_string((int)TimeController::timeDilation) + "X");
                    }
                }
                if(parseButton.checkForClick(mousePos)) {
                    Parser::parseGalaxy(stars);
                }

                playerEmpire.update(mousePos);
                switch(openTab) {
                    case Tabs::economic: 
                        EconomicsTab::getInput(mousePos);
                        break;
                    case Tabs::building:   
                        BuildTab::getInput(mousePos);
                        break;
                    case Tabs::ships:  
                        SpaceshipTab::getInput(mousePos);
                        break;
                    case Tabs::buildShips:   
                        SpaceshipBuildTab::getInput(mousePos);
                        break;
                    case Tabs::research:   
                        ResearchTab::getInput(mousePos);
                        break;
                    case Tabs::playerEmpire:   
                        PlayerEmpireTab::getInput(mousePos);
                        break;
                    default:  break;
                }
                GUI_Alert::getInput(mousePos);

            } else if(state == GameStates::menu) {
                menuScreen.checkForClicks(mousePos);
            } else if(state == GameStates::battle) {
                sampleBattle.getInput(mousePos);
            }
            lookingAtPlanet = false;
            break;

        case sf::Event::MouseButtonReleased:
            //std::cout << "mousePos: " << mousePos.x << ":" << mousePos.y << std::endl;
            if(state == GameStates::game) {
                if(!lookingAtPlanet) {
                    hasSelectedStar = false;
                    for (int i = 0; i < constants::GRIDSIDENUMBER; i++)
                    {
                        for (int j = 0; j < constants::GRIDSIDENUMBER; j++)
                        {
                            sf::RectangleShape shape;
                            sf::Vector2f newMousePos = window.mapPixelToCoords(mousePos, starview);
                            shape.setPosition(i * constants::GRIDSIDELENGTH, j * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
                            //shape.setPosition(
                            //    i * constants::GRIDSIDELENGTH * (1000 / starview.getSize().x) - (((1000 - starview.getSize().x) / 2000) * 1000) * (1000 / starview.getSize().x) - (starview.getCenter().x - starview.getSize().x * mouseWheelDelta / 2) / mouseWheelDelta,
                            //    j * constants::GRIDSIDELENGTH * (1000 / starview.getSize().y) + 100 - (((1000 - starview.getSize().y) / 2000) * 1000) * (1000 / starview.getSize().y) - (starview.getCenter().y - starview.getSize().y * mouseWheelDelta / 2 - 100) / mouseWheelDelta
                            //);
                            
                            shape.setSize(sf::Vector2f(constants::GRIDSIDELENGTH * (1 / mouseWheelDelta), constants::GRIDSIDELENGTH * (1 / mouseWheelDelta)));
                            if (shape.getGlobalBounds().contains(newMousePos))
                            {
                                if (stars[i * constants::GRIDSIDENUMBER + j].exists)
                                {
                                    if(stargui.visible) {
                                        if(mousePos.y > 600.f + constants::UPPERGUIHEIGHT) {
                                            break;
                                        }
                                    }
                                    if(openTab != Tabs::none) {
                                        if(mousePos.y < constants::UPPERGUIHEIGHT + 600.f && mousePos.x < 405.f) {
                                            break;
                                        }
                                    }
                                    if(stargui.planetDescriptionVisible) {
                                        if(mousePos.y < constants::STARGUIX * 2 && mousePos.x > constants::PLANETDESCRIPTIONX) {
                                            break;
                                        }
                                    }
                                    if(GUI_Alert::visible) {
                                        if(mousePos.y > 390 && mousePos.y < 690 && mousePos.x > 710 && mousePos.x < 1210) {
                                            break;
                                        }
                                    }
                                    if(mousePos.y < constants::UPPERGUIHEIGHT) {
                                        break;
                                    }
                                    //std::cout << starview.getCenter().x << ":" << starview.getCenter().y << std::endl;
                                    //std::cout << "position: " << i * constants::GRIDSIDELENGTH * mouseWheelDelta << ":" << j * constants::GRIDSIDELENGTH * mouseWheelDelta << std::endl;
                                    //std::cout << "Position: " <<  i * constants::GRIDSIDELENGTH + starview.getCenter().x - 500 << ":" << j * constants::GRIDSIDELENGTH + starview.getCenter().y - 500 << std::endl;
                                    //std::cout << "Ponk!\n";
                                    //stars[i * GRIDSIDENUMBER + j].color = sf::Color::White;
                                    selectBoxVisible = true;
                                    selectBox.setPosition(sf::Vector2f(i * constants::GRIDSIDELENGTH, j * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT));
                                    hasSelectedStar = true;
                                    stargui.setStar(stars[i * constants::GRIDSIDENUMBER + j]);
                                    stargui.setVisible(true);
                                }
                            }
                        }
                    }
                }
                if (!hasSelectedStar)
                {
                    bool des = true;
                    for(int i = 0; i < 6; i++) {
                        if(buttons[i].isClick()) {
                            buttons[i].deselect();
                            des = false;
                        }
                    }
                    //if(des) {
                        
                        //ship.setTarget(window.mapPixelToCoords(mousePos, starview));
                    //}
                }
            } else if(state == GameStates::menu) {

            } else if(state == GameStates::battle) {

            }
            break;

        case sf::Event::MouseWheelScrolled:
            
            mouseWheelDelta += event.mouseWheel.x / 10000000000.f;
            if(mouseWheelDelta <= 0) {
                mouseWheelDelta = 0.2f;
            }
            if(mouseWheelDelta >= 4) {
                mouseWheelDelta = 4;
            }
            if(mouseWheelDelta != 0) {
                starview.setSize(constants::SCREENX * mouseWheelDelta, (constants::SCREENY - constants::UPPERGUIHEIGHT) * mouseWheelDelta);
            }
            break;

        default:
            break;
        }
    }
}

void Game::update() {
    mousePos = sf::Mouse::getPosition(window);

    if (stargui.visible)
    {
        for (int o = 0; o < stargui.currentStar.nump; o++)
        {
            //std::cout << "dist: " << stargui.currentStar.planets[o].distance << std::endl;
            stargui.currentStar.planets[o].angle += stargui.currentStar.planets[o].angularVelocity * dt.asSeconds() * TimeController::timeDilation;
            stargui.currentStar.planets[o].x = stargui.currentStar.guiShape.getPosition().x + stargui.currentStar.guiShape.getRadius() + std::cos(stargui.currentStar.planets[o].angle) * stargui.currentStar.planets[o].distance;
            stargui.currentStar.planets[o].y = stargui.currentStar.guiShape.getPosition().y + stargui.currentStar.guiShape.getRadius() + std::sin(stargui.currentStar.planets[o].angle) * stargui.currentStar.planets[o].distance - (stargui.currentStar.planets[o].radius);
            for (int p = 0; p < stargui.currentStar.planets[o].numn; p++)
            {
                stargui.currentStar.planets[o].moons[p].angle += stargui.currentStar.planets[o].moons[p].angularVelocity * dt.asSeconds() * TimeController::timeDilation * 500;
                stargui.currentStar.planets[o].moons[p].x = stargui.currentStar.planets[o].x + stargui.currentStar.planets[o].radius + std::cos(stargui.currentStar.planets[o].moons[p].angle) * stargui.currentStar.planets[o].moons[p].distance;
                stargui.currentStar.planets[o].moons[p].y = stargui.currentStar.planets[o].y + stargui.currentStar.planets[o].radius + std::sin(stargui.currentStar.planets[o].moons[p].angle) * stargui.currentStar.planets[o].moons[p].distance - (stargui.currentStar.planets[o].moons[p].radius);
            }
        }
    }

    bool hovering = false;
    if(state == GameStates::game) {
        ResearchTab::update(dt.asSeconds()); 
        if(stargui.visible) {
            selectBoxVisible = true;
        } else {
            selectBoxVisible = false;
        }
        tick = 10.f * (500.f / TimeController::timeDilation);
        if(timerTick >= tick) {
            timerTick = 0;
            // UPDATE EVERYTHING;
            playerEmpire.setFunds(playerEmpire.getFunds() + startingSphere.getProduction());
        }

        if(animationTime >= animationCountDown) {
            // UPDATE ANIMATIONS
            //anim.update();
            //publicGoal.update();
            animationTime = 0;
        } else {
            animationTime += dt.asSeconds();
        }

        for(int k = 0; k < 6; k++) {
            if(buttons[k].checkForClick(mousePos)) {
                hovering = true;
            }
        }
        if(parseButton.checkForClick(mousePos)) {
            hovering = true;
        }

        for(int k = 0; k < constants::GRIDSIDENUMBER; k++) {
            for(int p = 0; p < constants::GRIDSIDENUMBER; p++) {
                if(stars[k * constants::GRIDSIDENUMBER + p].exists) {
                    sf::RectangleShape shape;
                    shape.setPosition(k * constants::GRIDSIDELENGTH, p * constants::GRIDSIDELENGTH + constants::UPPERGUIHEIGHT);
                    shape.setSize(sf::Vector2f(constants::GRIDSIDELENGTH, constants::GRIDSIDELENGTH));

                    if(shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        hovering = true;
                    }
                }
            }
        }

        if(stargui.visible) {
            if(stargui.hoveringOnPlanet(mousePos)) {
                hovering = true;
            }
        }
        //ship.update();
        //ship2.update();
        //std::cout << "OBAMA" << std::endl;
        for(auto ship : playerEmpire.spaceships) {
            ship->update();
        }
        
        EconomicsTab::update(playerEmpire.getFunds(), 1, 0);

        /*switch(openTab) {
            case economic: 
                EconomicsTab::visible = true;
                break;
            default:   
                EconomicsTab::visible = false;
                break;
        }*/
        
    }


    if((menuScreen.checkForHover(mousePos) && state == GameStates::menu) || hovering) {
        window.setMouseCursor (handC);
        isHoveringCursor = true;
    } else if(isHoveringCursor) {
        window.setMouseCursor (arrowC);
        isHoveringCursor = false;
    }


    sf::Vector2f movementVector;
    if(movement.movingUp) {
        movementVector.y = -1000.f * dt.asSeconds();
    }
    if(movement.movingDown) {
        movementVector.y = 1000.f * dt.asSeconds();
    }
    if(movement.movingLeft) {
        movementVector.x = -1000.f * dt.asSeconds();
    }
    if(movement.movingRight) {
        movementVector.x = 1000.f * dt.asSeconds();
    }

    starview.move(movementVector);



    //std::cout << starview.getCenter().x << ":" << starview.getCenter().y << std::endl;
    window.setTitle(std::to_string((int)(1.f / dt.asSeconds())));
}

void Game::render() {
    window.clear();

    //for(int i = 0; i < windowSize.height; i += GRIDSIDELENGTH) {
    //    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(i, 0)), sf::Vertex(sf::Vector2f(i, windowSize.height)) };
    //    window.draw(line, 2,  sf::Lines);
    //    sf::Vertex otherLine[] = { sf::Vertex(sf::Vector2f(0, i)), sf::Vertex(sf::Vector2f(windowSize.height, i)) };
    //    window.draw(otherLine, 2,  sf::Lines);
    //}
    if(state == GameStates::game) {
        // sf::CircleShape s;
        //s.setPosition(starview.getCenter().x - 10, starview.getCenter().y - 10);
        //s.setRadius(10);
        // s.setFillColor(sf::Color::Green);

        window.setView(starview);
        //window.draw(s);
        //empires[0].render(&window);
        //empires[1].render(&window);
        playerEmpire.render(&window);
        int starti = 0, endi = 50;
        if(starview.getCenter().x <= 960 * mouseWheelDelta) {
            starti = 0;
            endi = 50 * mouseWheelDelta;
        } else if(starview.getCenter().x >= 9000 * mouseWheelDelta) {
            starti = 200 * mouseWheelDelta;
            endi = constants::GRIDSIDENUMBER;
        } else {
            starti = (int)((starview.getCenter().x - 960 * mouseWheelDelta) / constants::GRIDSIDELENGTH);
            endi = (int)((starview.getCenter().x + 960 * mouseWheelDelta) / constants::GRIDSIDELENGTH);
        }
        int startj = 0, endj = 25;
        if(starview.getCenter().y <= 600 * mouseWheelDelta) {
            startj = 0 * mouseWheelDelta;
            endj = 26 * mouseWheelDelta;
        } else if(starview.getCenter().y >= 9000 * mouseWheelDelta) {
            startj = 224 * mouseWheelDelta;
            endj = constants::GRIDSIDENUMBER;
        }  else {
            startj = (int)((starview.getCenter().y - 600 * mouseWheelDelta) / constants::GRIDSIDELENGTH);
            endj = (int)((starview.getCenter().y + 500 * mouseWheelDelta) / constants::GRIDSIDELENGTH);
        }
        for (int i = starti; i < endi ; i++)
        {
            for (int j = startj; j < endj; j++)
            {
                int currentIndex = j + i * constants::GRIDSIDENUMBER;
                if (stars[currentIndex].exists)
                {
                    //std::cout << stars[currentIndex].radius / SOLARRADIUS << " P:" << stars[currentIndex].x<< ":" << stars[currentIndex].y <<  std::endl;
                    sf::CircleShape starCircle(stars[currentIndex].shape.getRadius());
                    starCircle.setFillColor(stars[currentIndex].color);
                    starCircle.setPosition(stars[currentIndex].x, stars[currentIndex].y + constants::UPPERGUIHEIGHT);
                    window.draw(starCircle);
                }
            }
        }


        if (selectBoxVisible)
        {
            window.draw(selectBox);
        }

        
        window.setView(window.getDefaultView());

        if (stargui.visible)
        {
            stargui.render(&window, TimeController::timeDilation, empires, playerEmpire);
        }

        
        //ship.render(&window, &stargui.currentStar, stargui.visible, starview);
        //ship2.render(&window, &stargui.currentStar, stargui.visible, starview);
        for(auto ship : playerEmpire.spaceships) {
            ship->render(&window, &stargui.currentStar, stargui.visible, starview);
        } 
        upGUI.render(&window);
        switch(openTab) {
            case Tabs::economic: EconomicsTab::render(&window);
                    break;
            case Tabs::building: BuildTab::render(&window);
                    break;
            case Tabs::ships: SpaceshipTab::render(&window);
                    break;
            case Tabs::buildShips: SpaceshipBuildTab::render(&window);
                    break;
            case Tabs::research: ResearchTab::render(&window);
                    break;
            case Tabs::playerEmpire:  PlayerEmpireTab::render(&window);
                    break;
            default:  break;
        }
        window.draw(stargui.timeDilationText);
        window.draw(title);
        
        playerEmpire.renderGUI(&window);

        for(int i = 0; i < 6; i++) {
            buttons[i].render(&window);
        }
        //anim.render(&window);
        //publicGoal.render(&window);
        parseButton.render(&window);
        GUI_Alert::render(&window);
    } else if(state == GameStates::menu) {
        window.setView(window.getDefaultView());
        menuScreen.render(&window);
    } else if(state == GameStates::battle) {
        sampleBattle.render(&window);
    }
    window.display();
}