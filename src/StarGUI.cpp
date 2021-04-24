#include "StarGUI.h"

bool StarGUI::mVisible = false;
bool StarGUI::mPlanetDescriptionVisible = false;


StarGUI::StarGUI()
{
}

StarGUI::~StarGUI()
{
}

void StarGUI::setup(float timeD, sf::Font font, void (*openBuildTab)(), void (*openSpaceshipBuildTab)())
{
    mVisible = false;
    this->mFont = font;
    mGuiRec.setup({5.f, 600.f + constants::UPPERGUIHEIGHT}, {constants::SCREENX - 10, constants::PLANETDESCRIPTIONY * 2}, sf::Color::Blue, sf::Color::Green, this->mFont, closeStarGUI);


    mStarInfo[0].setPosition(25, 650 + constants::UPPERGUIHEIGHT);
    mStarInfo[1].setPosition(25, 700 + constants::UPPERGUIHEIGHT);
    mStarInfo[2].setPosition(25, 750 + constants::UPPERGUIHEIGHT);
    mStarInfo[3].setPosition(25, 800 + constants::UPPERGUIHEIGHT);
    mStarInfo[0].setCharacterSize(30);
    mStarInfo[0].setFillColor(sf::Color::White);
    mStarInfo[1].setCharacterSize(30);
    mStarInfo[1].setFillColor(sf::Color::White);
    mStarInfo[2].setCharacterSize(30);
    mStarInfo[2].setFillColor(sf::Color::White);
    mStarInfo[3].setCharacterSize(30);
    mStarInfo[3].setFillColor(sf::Color::White);
    mStarInfo[0].setFont(this->mFont);
    mStarInfo[1].setFont(this->mFont);
    mStarInfo[2].setFont(this->mFont);
    mStarInfo[3].setFont(this->mFont);

    mTimeDilationText.setPosition(771.25, 36);
    mTimeDilationText.setFillColor(sf::Color::White);
    mTimeDilationText.setFont(this->mFont);
    mTimeDilationText.setCharacterSize(20);
    mTimeDilationText.setString(std::to_string((int)(timeD)) + "X");

    mPlanetDescriptionVisible = false;
    mPlanetDescriptionBG.setup({constants::PLANETDESCRIPTIONX, constants::UPPERGUIHEIGHT}, {constants::PLANETDESCRIPTIONY * 2, constants::STARGUIX * 2}, sf::Color::Blue, sf::Color::Yellow, this->mFont, closePlanetGUI);

    mPlanetNameLabel.setup("Name: ", sf::Color::White, this->mFont, 30, {constants::PLANETDATAX, 120});
    mPlanetRadiusLabel.setup("Radius: ", sf::Color::White, this->mFont, 30, {constants::PLANETDATAX, 180});
    mPlanetMassLabel.setup("Mass: ", sf::Color::White, this->mFont, 30, {constants::PLANETDATAX, 240});
    mPlanetDistanceLabel.setup("Distance: ", sf::Color::White, this->mFont, 30, {constants::PLANETDATAX, 300});
    mPlanetOwnerLabel.setup("Owned by: ", sf::Color::White, this->mFont, 30, {constants::PLANETDATAX, 800});

    sf::RectangleShape bs;
    bs.setSize({150, 40});
    bs.setPosition(constants::PLANETDATAX, 850);
    mBuildButton.setup(this->mFont, bs,  sf::Color(100, 80, 220, 255), sf::Color(200, 80, 240, 255), "BUILD", 30);
    mBuildButton.setFunction(openBuildTab);

    bs.setPosition(constants::PLANETDATAX + 160, 850);
    mBuildShipButton.setup(this->mFont, bs, sf::Color(100, 80, 220, 255), sf::Color(200, 80, 240, 255), "BUILD SHIP", 20);
    mBuildShipButton.setFunction(openSpaceshipBuildTab);

    mMarcoTexture.loadFromFile("../Assets/gui/marco.jpg");
    mMarcoSprite.setTexture(mMarcoTexture);
    mMarcoSprite.setScale(0.2f, 0.2f);
    mMarcoSprite.setPosition(constants::SCREENX - mMarcoTexture.getSize().x * mMarcoSprite.getScale().x, constants::SCREENY - mMarcoTexture.getSize().y * mMarcoSprite.getScale().x);
}


void StarGUI::setStar(Star currentStar)
{
    this->mCurrentStar = currentStar;
    mStarInfo[0].setString("Name: " + this->mCurrentStar.mName);
    int p = 0;
    std::string radStr = "Size: ";
    double r = this->mCurrentStar.mRadius * constants::SOLARRADIUS;
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
    mStarInfo[1].setString(radStr);
    std::string massStr = "Mass: ";
    p = 0;
    while(true) {
        if(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p) < 10) {
            massStr += std::to_string((int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p)));
            massStr += ",";
            massStr += std::to_string((int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 1)) - (int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p)) * 10);
            massStr += std::to_string((int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 2)) - (int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 1)) * 10);
            massStr += std::to_string((int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 3)) - (int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 2)) * 10);
            massStr += std::to_string((int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 4)) - (int)(this->mCurrentStar.mMass * constants::SOLARMASS / pow(10, p - 3)) * 10);
            massStr += " * 10 ^ ";
            massStr += std::to_string(p);
            massStr += " kg";
            break;
        }
        p++;
    }
    mStarInfo[2].setString(massStr);
    mStarInfo[3].setString("Position: (" + std::to_string(this->mCurrentStar.mX) + ";" + std::to_string(this->mCurrentStar.mY) + ")");

    for (int i = 0; i < this->mCurrentStar.mNumP; i++)
    {

        this->mCurrentStar.mPlanets[i].mX = constants::STARGUIX + this->mCurrentStar.mPlanets[i].mDistance;
        this->mCurrentStar.mPlanets[i].mY = constants::STARGUIY + (this->mCurrentStar.mGuiShape.getRadius() - (this->mCurrentStar.mPlanets[i].mRadius));

        for (int j = 0; j < this->mCurrentStar.mPlanets[i].mNumn; j++)
        {
            this->mCurrentStar.mPlanets[i].mMoons[j].mX = constants::STARGUIX + i * 50 + ((this->mCurrentStar.mPlanets[i].mRadius) - (this->mCurrentStar.mPlanets[i].mMoons[j].mRadius));
            this->mCurrentStar.mPlanets[i].mMoons[j].mY = this->mCurrentStar.mPlanets[i].mY + (this->mCurrentStar.mPlanets[i].mRadius) + this->mCurrentStar.mPlanets[i].mMoons[j].mDistance;
        }
    }


}

void StarGUI::setVisible(bool visible)
{
    this->mVisible = visible;
}

void StarGUI::render(sf::RenderWindow& window, float timeDilation, Empire *empires, PlayerEmpire &empire)
{
    this->mTimeDilationText.setString(std::to_string((int)(timeDilation)) + "X");
    //std::cout << currentStar.guiShape.getPosition().x << ":" << currentStar.guiShape.getPosition().y << std::endl;
    this->mGuiRec.render(window);
    if(!this->mCurrentStar.mHasDysonSphere) {
        window.draw(mCurrentStar.mGuiShape);
    } else {
        DysonSphere::render(window);
    }
    for (int i = 0; i < this->mCurrentStar.mNumP; i++)
    {

        sf::CircleShape pl;
        pl.setPosition(mCurrentStar.mPlanets[i].mX - mCurrentStar.mPlanets[i].mRadius * 3, mCurrentStar.mPlanets[i].mY - mCurrentStar.mPlanets[i].mRadius * 3);
        pl.setRadius((mCurrentStar.mPlanets[i].mRadius) * 5);
        if(this->mCurrentStar.mPlanets[i].getOccupierID() == constants::PLAYERID) {
            pl.setFillColor(empire.getEmpireColor());
        } else if(this->mCurrentStar.mPlanets[i].getOccupierID() == 0) {
            pl.setFillColor(this->mCurrentStar.mPlanets[i].mColor);
        } else {
            pl.setFillColor(empires[mCurrentStar.mPlanets[i].getOccupierID() - 1].getEmpireColor());
        }
        window.draw(this->mCurrentStar.mOrbits[i]);
        window.draw(pl);
        for (int j = 0; j < this->mCurrentStar.mPlanets[i].mNumn; j++)
        {
            sf::CircleShape mn;
            mn.setPosition(this->mCurrentStar.mPlanets[i].mMoons[j].mX - this->mCurrentStar.mPlanets[i].mMoons[j].mRadius * 5, this->mCurrentStar.mPlanets[i].mMoons[j].mY - this->mCurrentStar.mPlanets[i].mMoons[j].mRadius * 5);
            mn.setRadius(this->mCurrentStar.mPlanets[i].mMoons[j].mRadius * constants::MOONRADIUSFACTIOR);
            mn.setFillColor(this->mCurrentStar.mPlanets[i].mMoons[j].mColor);
            window.draw(mn);
        }
    }

    for(int j = 0; j < 4; j++){
        window.draw(mStarInfo[j]);
    }

    if(mPlanetDescriptionVisible) {
        this->mPlanetDescriptionBG.render(window);
        this->mPlanetRadiusLabel.render(window);
        this->mPlanetMassLabel.render(window);
        this->mPlanetNameLabel.render(window);
        this->mPlanetDistanceLabel.render(window);
        this->mPlanetOwnerLabel.render(window);

        if(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].getOccupierID() != 0) {
            this->mBuildButton.render(window);
            this->mBuildShipButton.render(window);
        }

        sf::CircleShape planetShape;
        planetShape.setPosition(constants::PLANETDESCRIPTIONX + (constants::PLANETDESCRIPTIONY - this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20), 450.0);
        planetShape.setRadius(mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20);
        if(this->mCurrentStar.mPlanets[this->mCurrentPlanetIndex].getOccupierID() == constants::PLAYERID) {
            planetShape.setFillColor(empire.getEmpireColor());
        } else if(this->mCurrentStar.mPlanets[this->mCurrentPlanetIndex].getOccupierID() == 0) {
            planetShape.setFillColor(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mColor);
        } else {
            planetShape.setFillColor(empires[this->mCurrentStar.mPlanets[mCurrentPlanetIndex].getOccupierID() - 1].getEmpireColor());
        }

        window.draw(planetShape);

        for (int j = 0; j < this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mNumn; j++)
        {
            sf::CircleShape mn;
            mn.setPosition(constants::PLANETDESCRIPTIONX + (constants::PLANETDESCRIPTIONY - this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20) + this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20 + std::cos(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mAngle) * (this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20 + this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mDistance), 450.0 + this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20 + std::sin(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mAngle) * (this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mRadius * 20 + this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mDistance));
            //mn.setPosition(600.0 + (197.5 - currentStar.planets[currentPlanetIndex].radius * 20) + currentStar.planets[currentPlanetIndex].radius * 20 + std::cos(currentStar.planets[currentPlanetIndex].moons[j].angle) * 100, 450.0 + currentStar.planets[currentPlanetIndex].radius * 20 + std::sin(currentStar.planets[currentPlanetIndex].moons[j].angle) * 100);
            mn.setRadius(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mRadius * constants::MOONRADIUSFACTIOR);
            mn.setFillColor(this->mCurrentStar.mPlanets[mCurrentPlanetIndex].mMoons[j].mColor);
            window.draw(mn);
        }
    }

    window.draw(mMarcoSprite);
}

bool StarGUI::update(sf::Vector2i mousePos) {
    bool entered = false;
    for(int i = 0; i < this->mCurrentStar.mNumP; i++) {
        sf::RectangleShape sh;
        sh.setPosition(this->mCurrentStar.mPlanets[i].mX - this->mCurrentStar.mPlanets[i].mRadius * 3, this->mCurrentStar.mPlanets[i].mY - this->mCurrentStar.mPlanets[i].mRadius * 3);
        if(mCurrentStar.mPlanets[i].mRadius <= 10) {
            sh.setSize({this->mCurrentStar.mPlanets[i].mRadius * 20, this->mCurrentStar.mPlanets[i].mRadius * 20});
        } else {
            sh.setSize({this->mCurrentStar.mPlanets[i].mRadius * 10, this->mCurrentStar.mPlanets[i].mRadius * 10});
        }
        if(sh.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            
            std::stringstream stream;
            stream << "Radius: " << std::scientific << std::setprecision(3) << (this->mCurrentStar.mPlanets[i].mRadius * constants::EARTHRADIUS);
            std::string str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');
            
            this->mPlanetRadiusLabel.setString(str);

            stream.str("");
            stream << "Mass: " << std::scientific << std::setprecision(3) << (this->mCurrentStar.mPlanets[i].mMass * constants::EARTHMASS);
            str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');

            this->mPlanetMassLabel.setString(str);

            stream.str("");
            stream << "Distance: " << std::scientific << std::setprecision(3) << (this->mCurrentStar.mPlanets[i].mDistance * constants::EARTHDISTANCE);
            str = stream.str();
            std::replace(str.begin(), str.end(), '.', ',');

            this->mPlanetDistanceLabel.setString(str);

            this->mPlanetNameLabel.setString("Name: " + this->mCurrentStar.mPlanets[i].mName);

            this->mPlanetOwnerLabel.setString("Owned by: " + ((this->mCurrentStar.mPlanets[i].getOccupierID() == 0) ? "none" : std::to_string(this->mCurrentStar.mPlanets[i].getOccupierID())));

            this->mCurrentPlanetIndex = i;

            entered = true;
            this->mPlanetDescriptionVisible = true;
        }
    }
    //if(!entered) {
    //    mPlanetDescriptionVisible = false;
    //}

    mPlanetDescriptionBG.getExit(mousePos);
    mGuiRec.getExit(mousePos);
    if(mBuildButton.checkForClick(mousePos) && mPlanetDescriptionVisible && mCurrentStar.mPlanets[mCurrentPlanetIndex].getOccupierID() == 1) {
        mBuildButton.click();
    }
    if(mBuildShipButton.checkForClick(mousePos) && mPlanetDescriptionVisible && mCurrentStar.mPlanets[mCurrentPlanetIndex].getOccupierID() == 1) {
        mBuildShipButton.click();
    }

    return entered;
}

bool StarGUI::hoveringOnPlanet(sf::Vector2i mousePos) {
    for(int i = 0; i < mCurrentStar.mNumP; i++) {
        sf::RectangleShape s;
        s.setPosition(mCurrentStar.mPlanets[i].mX - mCurrentStar.mPlanets[i].mRadius * 3, mCurrentStar.mPlanets[i].mY - mCurrentStar.mPlanets[i].mRadius * 3);
        s.setSize({mCurrentStar.mPlanets[i].mRadius * 10, mCurrentStar.mPlanets[i].mRadius * 10});

        if(s.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return true;
        }
    }
    return false;
}
