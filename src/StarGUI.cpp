#include "StarGUI.h"

bool StarGUI::visible = false;
bool StarGUI::planetDescriptionVisible = false;


StarGUI::StarGUI()
{
}

StarGUI::~StarGUI()
{
}

void StarGUI::setup(float timeD, sf::Font font, void (*openBuildTab)(), void (*openSpaceshipBuildTab)())
{
    visible = false;
    this->font = font;
    /*guiRec.setPosition(5, 600 + constants::UPPERGUIHEIGHT);
    guiRec.setSize(sf::Vector2f(constants::SCREENX - 10, constants::PLANETDESCRIPTIONY * 2));
    guiRec.setOutlineColor(sf::Color::Green);
    guiRec.setOutlineThickness(5.f);
    guiRec.setFillColor(sf::Color::Blue);*/

    guiRec.setup({5.f, 600.f + constants::UPPERGUIHEIGHT}, {constants::SCREENX - 10, constants::PLANETDESCRIPTIONY * 2}, sf::Color::Blue, sf::Color::Green, this->font, closeStarGUI);


    starInfo[0].setPosition(25, 650 + constants::UPPERGUIHEIGHT);
    starInfo[1].setPosition(25, 700 + constants::UPPERGUIHEIGHT);
    starInfo[2].setPosition(25, 750 + constants::UPPERGUIHEIGHT);
    starInfo[3].setPosition(25, 800 + constants::UPPERGUIHEIGHT);
    starInfo[0].setCharacterSize(30);
    starInfo[0].setFillColor(sf::Color::White);
    starInfo[1].setCharacterSize(30);
    starInfo[1].setFillColor(sf::Color::White);
    starInfo[2].setCharacterSize(30);
    starInfo[2].setFillColor(sf::Color::White);
    starInfo[3].setCharacterSize(30);
    starInfo[3].setFillColor(sf::Color::White);
    starInfo[0].setFont(this->font);
    starInfo[1].setFont(this->font);
    starInfo[2].setFont(this->font);
    starInfo[3].setFont(this->font);

    timeDilationText.setPosition(771.25, 36);
    timeDilationText.setFillColor(sf::Color::White);
    timeDilationText.setFont(this->font);
    timeDilationText.setCharacterSize(20);
    timeDilationText.setString(std::to_string((int)(timeD)) + "X");

    planetDescriptionVisible = false;
   /* planetDescriptionBG.setFillColor(sf::Color::Blue);
    planetDescriptionBG.setOutlineThickness(5);
    planetDescriptionBG.setOutlineColor(sf::Color::Yellow);
    planetDescriptionBG.setPosition(constants::PLANETDESCRIPTIONX, constants::UPPERGUIHEIGHT);
    planetDescriptionBG.setSize({constants::PLANETDESCRIPTIONY * 2, constants::STARGUIX * 2}); // Obama*/
    planetDescriptionBG.setup({constants::PLANETDESCRIPTIONX, constants::UPPERGUIHEIGHT}, {constants::PLANETDESCRIPTIONY * 2, constants::STARGUIX * 2}, sf::Color::Blue, sf::Color::Yellow, this->font, closePlanetGUI);

    planetNameLabel.setup("Name: ", sf::Color::White, this->font, 30, {constants::PLANETDATAX, 120});
    planetRadiusLabel.setup("Radius: ", sf::Color::White, this->font, 30, {constants::PLANETDATAX, 180});
    planetMassLabel.setup("Mass: ", sf::Color::White, this->font, 30, {constants::PLANETDATAX, 240});
    planetDistanceLabel.setup("Distance: ", sf::Color::White, this->font, 30, {constants::PLANETDATAX, 300});
    planetOwnerLabel.setup("Owned by: ", sf::Color::White, this->font, 30, {constants::PLANETDATAX, 800});

    sf::RectangleShape bs;
    bs.setSize({150, 40});
    bs.setPosition(constants::PLANETDATAX, 850);
    buildButton.setup(this->font, bs,  sf::Color(100, 80, 220, 255), sf::Color(200, 80, 240, 255), "BUILD", 30);
    buildButton.setFunction(openBuildTab);

    bs.setPosition(constants::PLANETDATAX + 160, 850);
    buildShipButton.setup(this->font, bs, sf::Color(100, 80, 220, 255), sf::Color(200, 80, 240, 255), "BUILD SHIP", 20);
    buildShipButton.setFunction(openSpaceshipBuildTab);
}


void StarGUI::setStar(Star currentStar)
{
    this->currentStar = currentStar;
    starInfo[0].setString("Name: " + this->currentStar.name);
    int p = 0;
    std::string radStr = "Size: ";
    double r = this->currentStar.radius * constants::SOLARRADIUS;
    while(true) {
        if(r / pow(10, p) < 10) {
            radStr += std::to_string((int)(r / pow(10, p)));
            radStr += ",";
            radStr += std::to_string((int)(r / pow(10, p - 1)) - (int)(r / pow(10, p)) * 10);
            radStr += std::to_string((int)(r / pow(10, p - 2)) - (int)(r / pow(10, p - 1)) * 10);
            radStr += std::to_string((int)(r / pow(10, p - 3)) - (int)(r / pow(10, p - 2)) * 10);
            radStr += std::to_string((int)(r / pow(10, p - 4)) - (int)(r / pow(10, p - 3)) * 10);
            radStr += " * 10 ^ ";
            radStr += std::to_string(p);
            radStr += " m";
            break;
        }
        p++;
    }
    starInfo[1].setString(radStr);
    std::string massStr = "Mass: ";
    p = 0;
    while(true) {
        if(this->currentStar.mass * constants::SOLARMASS / pow(10, p) < 10) {
            massStr += std::to_string((int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p)));
            massStr += ",";
            massStr += std::to_string((int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 1)) - (int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p)) * 10);
            massStr += std::to_string((int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 2)) - (int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 1)) * 10);
            massStr += std::to_string((int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 3)) - (int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 2)) * 10);
            massStr += std::to_string((int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 4)) - (int)(this->currentStar.mass * constants::SOLARMASS / pow(10, p - 3)) * 10);
            massStr += " * 10 ^ ";
            massStr += std::to_string(p);
            massStr += " kg";
            break;
        }
        p++;
    }
    starInfo[2].setString(massStr);
    starInfo[3].setString("Position: (" + std::to_string(this->currentStar.x) + ";" + std::to_string(this->currentStar.y) + ")");

    for (int i = 0; i < this->currentStar.nump; i++)
    {

        this->currentStar.planets[i].x = constants::STARGUIX + this->currentStar.planets[i].distance;
        this->currentStar.planets[i].y = constants::STARGUIY + (this->currentStar.guiShape.getRadius() - (this->currentStar.planets[i].radius));

        for (int j = 0; j < this->currentStar.planets[i].numn; j++)
        {
            this->currentStar.planets[i].moons[j].x = constants::STARGUIX + i * 50 + ((this->currentStar.planets[i].radius) - (this->currentStar.planets[i].moons[j].radius));
            this->currentStar.planets[i].moons[j].y = this->currentStar.planets[i].y + (this->currentStar.planets[i].radius) + this->currentStar.planets[i].moons[j].distance;
        }
    }


}

void StarGUI::setVisible(bool visible)
{
    this->visible = visible;
}

void StarGUI::render(sf::RenderWindow *window, float timeDilation, Empire *empires, PlayerEmpire &empire)
{
    this->timeDilationText.setString(std::to_string((int)(timeDilation)) + "X");
    //std::cout << currentStar.guiShape.getPosition().x << ":" << currentStar.guiShape.getPosition().y << std::endl;
    this->guiRec.render(window);
    if(!this->currentStar.hasDysonSphere) {       
        window->draw(currentStar.guiShape);
    } else {
        DysonSphere::render(window);
    }
    for (int i = 0; i < this->currentStar.nump; i++)
    {

        sf::CircleShape pl;
        pl.setPosition(currentStar.planets[i].x - currentStar.planets[i].radius * 3, currentStar.planets[i].y - currentStar.planets[i].radius * 3);
        pl.setRadius((currentStar.planets[i].radius) * 5);
        if(this->currentStar.planets[i].getOccupierID() == constants::PLAYERID) {
            pl.setFillColor(empire.getEmpireColor());
        } else if(this->currentStar.planets[i].getOccupierID() == 0) {
            pl.setFillColor(this->currentStar.planets[i].color);
        } else {
            pl.setFillColor(empires[currentStar.planets[i].getOccupierID() - 1].getEmpireColor());
        }
        window->draw(this->currentStar.orbits[i]);
        window->draw(pl);
        for (int j = 0; j < this->currentStar.planets[i].numn; j++)
        {
            sf::CircleShape mn;
            mn.setPosition(this->currentStar.planets[i].moons[j].x - this->currentStar.planets[i].moons[j].radius * 5, this->currentStar.planets[i].moons[j].y - this->currentStar.planets[i].moons[j].radius * 5);
            mn.setRadius(this->currentStar.planets[i].moons[j].radius * constants::MOONRADIUSFACTIOR);
            mn.setFillColor(this->currentStar.planets[i].moons[j].color);
            window->draw(mn);
        }
    }

    for(int j = 0; j < 4; j++){
        window->draw(starInfo[j]);
    }

    if(planetDescriptionVisible) {
        this->planetDescriptionBG.render(window);
        this->planetRadiusLabel.render(window);
        this->planetMassLabel.render(window);
        this->planetNameLabel.render(window);
        this->planetDistanceLabel.render(window);
        this->planetOwnerLabel.render(window);

        if(this->currentStar.planets[currentPlanetIndex].getOccupierID() != 0) {
            this->buildButton.render(window);
            this->buildShipButton.render(window);
        }

        sf::CircleShape planetShape;
        planetShape.setPosition(constants::PLANETDESCRIPTIONX + (constants::PLANETDESCRIPTIONY - this->currentStar.planets[currentPlanetIndex].radius * 20), 450.0);
        planetShape.setRadius(currentStar.planets[currentPlanetIndex].radius * 20);
        if(this->currentStar.planets[this->currentPlanetIndex].getOccupierID() == constants::PLAYERID) {
            planetShape.setFillColor(empire.getEmpireColor());
        } else if(this->currentStar.planets[this->currentPlanetIndex].getOccupierID() == 0) {
            planetShape.setFillColor(this->currentStar.planets[currentPlanetIndex].color);
        } else {
            planetShape.setFillColor(empires[this->currentStar.planets[currentPlanetIndex].getOccupierID() - 1].getEmpireColor());
        }

        window->draw(planetShape);

        for (int j = 0; j < this->currentStar.planets[currentPlanetIndex].numn; j++)
        {
            sf::CircleShape mn;
            mn.setPosition(constants::PLANETDESCRIPTIONX + (constants::PLANETDESCRIPTIONY - this->currentStar.planets[currentPlanetIndex].radius * 20) + this->currentStar.planets[currentPlanetIndex].radius * 20 + std::cos(this->currentStar.planets[currentPlanetIndex].moons[j].angle) * (this->currentStar.planets[currentPlanetIndex].radius * 20 + this->currentStar.planets[currentPlanetIndex].moons[j].distance), 450.0 + this->currentStar.planets[currentPlanetIndex].radius * 20 + std::sin(this->currentStar.planets[currentPlanetIndex].moons[j].angle) * (this->currentStar.planets[currentPlanetIndex].radius * 20 + this->currentStar.planets[currentPlanetIndex].moons[j].distance));
            //mn.setPosition(600.0 + (197.5 - currentStar.planets[currentPlanetIndex].radius * 20) + currentStar.planets[currentPlanetIndex].radius * 20 + std::cos(currentStar.planets[currentPlanetIndex].moons[j].angle) * 100, 450.0 + currentStar.planets[currentPlanetIndex].radius * 20 + std::sin(currentStar.planets[currentPlanetIndex].moons[j].angle) * 100);
            mn.setRadius(this->currentStar.planets[currentPlanetIndex].moons[j].radius * constants::MOONRADIUSFACTIOR);
            mn.setFillColor(this->currentStar.planets[currentPlanetIndex].moons[j].color);
            window->draw(mn);
        }
    }
}

bool StarGUI::update(sf::Vector2i mousePos) {
    bool entered = false;
    for(int i = 0; i < this->currentStar.nump; i++) {
        sf::RectangleShape sh;
        sh.setPosition(this->currentStar.planets[i].x - this->currentStar.planets[i].radius * 3, this->currentStar.planets[i].y - this->currentStar.planets[i].radius * 3);
        if(currentStar.planets[i].radius <= 10) {
            sh.setSize({this->currentStar.planets[i].radius * 20, this->currentStar.planets[i].radius * 20});
        } else {
            sh.setSize({this->currentStar.planets[i].radius * 10, this->currentStar.planets[i].radius * 10});
        }
        if(sh.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            
            std::stringstream stream;
            stream << "Radius: " << std::scientific << std::setprecision(3) << (this->currentStar.planets[i].radius * constants::EARTHRADIUS);
            std::string str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');
            
            this->planetRadiusLabel.setString(str);

            stream.str("");
            stream << "Mass: " << std::scientific << std::setprecision(3) << (this->currentStar.planets[i].mass * constants::EARTHMASS);
            str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');

            this->planetMassLabel.setString(str);

            stream.str("");
            stream << "Distance: " << std::scientific << std::setprecision(3) << (this->currentStar.planets[i].distance * constants::EARTHDISTANCE);
            str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');

            this->planetDistanceLabel.setString(str);

            this->planetNameLabel.setString("Name: " + this->currentStar.planets[i].name);

            this->planetOwnerLabel.setString("Owned by: " + ((this->currentStar.planets[i].getOccupierID() == 0) ? "none" : std::to_string(this->currentStar.planets[i].getOccupierID())));

            this->currentPlanetIndex = i;

            entered = true;
            this->planetDescriptionVisible = true;
        }
    }
    //if(!entered) {
    //    planetDescriptionVisible = false;
    //}

    planetDescriptionBG.getExit(mousePos);
    guiRec.getExit(mousePos);
    if(buildButton.checkForClick(mousePos) && planetDescriptionVisible && currentStar.planets[currentPlanetIndex].getOccupierID() == 1) {
        buildButton.click();
    }
    if(buildShipButton.checkForClick(mousePos) && planetDescriptionVisible && currentStar.planets[currentPlanetIndex].getOccupierID() == 1) {
        buildShipButton.click();
    }

    return entered;
}

bool StarGUI::hoveringOnPlanet(sf::Vector2i mousePos) {
    for(int i = 0; i < currentStar.nump; i++) {
        sf::RectangleShape s;
        s.setPosition(currentStar.planets[i].x - currentStar.planets[i].radius * 3, currentStar.planets[i].y - currentStar.planets[i].radius * 3);
        s.setSize({currentStar.planets[i].radius * 10, currentStar.planets[i].radius * 10});

        if(s.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return true;
        }
    }
    return false;
}
