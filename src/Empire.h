#ifndef EMPIRE_H
#define EMPIRE_H

#include <vector>

#include "Spaceship.h"
#include "DysonSphere.h"


class Empire {

    protected:
        sf::Color empireColor;
        unsigned int ID;
        int size;
        int funds;
        bool isAI;
        std::string raceSprite;
        std::string flagSprite;
        std::string leaderName;
        sf::Font font;
        std::string name;
        sf::RectangleShape empireSquares[constants::GRIDSIDENUMBER * constants::GRIDSIDENUMBER]; 
        
    public:  
        Empire() {}
        ~Empire() {}
        std::vector<Planet* > planets;
        std::vector<Star *> stars;
        std::vector<Spaceship *> spaceships;
        std::vector<Spaceship *> availbleShips;
        std::vector<DysonSphere *> dysonSpheres;
        std::vector<Building *> availbleBuildings;
        //std::vector<Research *> availbleResearches;

        void conquerPlanet(Planet *p, Star *s, sf::Vector2i pos);
        void loosePlanet(Planet *p, Star *s) { 
            auto i = std::find(planets.begin(), planets.end(), p);
            planets.erase(i);
            auto j = std::find(stars.begin(), stars.end(), s);
            stars.erase(j);
        }
        void setLeaderName(std::string name) { 
            this->leaderName = name;
        }
        std::string getLeaderName() {
            return this->leaderName;
        }
        void setName(std::string name) {
            this->name = name;
        }
        std::string getName() { return this->name; } 
        void setRace(std::string filePath) { this->raceSprite = filePath; }
        void setFlag(std::string filePath) { this->flagSprite = filePath; }
        std::string getRace() { return this->raceSprite; }
        std::string getFlag() { return this->flagSprite; }
        void buildShip(Spaceship *s) {
            spaceships.push_back(s);
        }
        void looseShip(Spaceship *s) {
            auto i = std::find(spaceships.begin(), spaceships.end(), s);
            spaceships.erase(i);
        }

        void createDysonSphere(DysonSphere *d) {
            dysonSpheres.push_back(d);
        }
        void looseDysonSphere(DysonSphere *d) {
            auto i = std::find(dysonSpheres.begin(), dysonSpheres.end(), d);
            dysonSpheres.erase(i);
        }
        unsigned int getID() { return ID; }

        int getFunds() { return funds; }
        virtual void setFunds(int f) { this->funds = f; }
        void setAI(bool a) { this->isAI = a; }
        bool getAI() { return this->isAI; }

        sf::Color getEmpireColor() { return empireColor; }
        void setup(Planet *startingPlanet, sf::Vector2i pos, Star *startingStar, sf::Color empireColor, unsigned int ID, sf::Font font, std::string name);
        virtual void render(sf::RenderWindow *window);
};

#endif