#ifndef SPACESHIPSPARSER_H
#define SPACESHIPSPARSER_H

#include "Spaceship.h"
#include <fstream>

class SpaceshipsParser {
    private:
        static Spaceship* parseSpaceship(std::string line) {
            if(line[0] == '-' || line[0] == ' ') {
                //std::cout << "B" << std::endl;
                return nullptr;
            }
            SpaceShipTypes type = SpaceShipTypes::Scout;
            int index = 0;
            int cost = 0;
            std::string name = "", filePath = "";
            int maxFuel = 0;
            float speed = 0.f;

            bool hasType = false, hasIndex = false, hasCost = false, hasName = false, hasFilePath = false, hasMaxFuel = false, hasSpeed = false;
            
            int count = 0;
            std::string currentValue = "";
            bool reading = false;
            while(line[count] != ';') {
                if(!hasIndex) {
                    if(line[count] == ':') {
                        hasIndex = true;
                        index = std::stoi(currentValue);
                        count += 1;
                        currentValue = "";
                    } else {
                        currentValue += line[count];
                    }
                }
                else if(!hasType) {
                    if(line[count] == 't' && line[count + 1] == 'y' && line[count + 2] == 'p' && line[count + 3] == 'e' && line[count + 4] == ':') {
                        //std::cout << line[count + 5] << std::endl;
                        switch(line[count + 5]) {
                            case 's': type = SpaceShipTypes::Scout;
                                break;
                            case 'r': type = SpaceShipTypes::Researcher;
                                break;
                            case 'w': type = SpaceShipTypes::War;
                                break;
                            case 'c': type = SpaceShipTypes::Colonisation;
                                break;
                            default: std::cerr << "Error, unspecified value or non-existant type." << std::endl;
                                break; 
                        }
                        count += 6;
                        hasType = true;
                        //std::cout << line[count] << line[count + 1] << line[count + 2] << line[count + 3] << line[count + 4] << line[count + 5] << std::endl;
                    }
                }
                else if(!hasCost) {
                    if(line[count] == 'c' && line[count + 1] == 'o' && line[count + 2] == 's' && line[count + 3] == 't' && line[count + 4] == ':') {
                        //std::cout << "COST" << std::endl;
                        count += 4;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ') {
                            currentValue += line[count];
                            count++;
                        }
                        //std::cout << currentValue << std::endl;
                        cost = std::stoi(currentValue);
                        currentValue = "";
                        hasCost = true;
                        reading = false;
                    }
                }
                else if(!hasName) {
                    if(line[count] == 'n' && line[count + 1] == 'a' && line[count + 2] == 'm' && line[count + 3] == 'e' && line[count + 4] == ':') {
                        // std::cout << "NAME" << std::endl;
                        count += 4;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ') {
                            currentValue += line[count];
                            count++;
                        }
                        name = currentValue;
                        currentValue = "";
                        hasName = true;
                        reading = false;
                    }
                }
                else if(!hasFilePath) {
                    if(line[count] == 's' && line[count + 1] == 'p' && line[count + 2] == 'r' && line[count + 3] == 'i' && line[count + 4] == 't' && line[count + 5] == 'e' && line[count + 6] == ':') {
                        count += 6;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ' && line[count] != ';') {

                            currentValue += line[count];
                            count++;
                        }
                        filePath = currentValue;
                        currentValue = "";
                        hasFilePath = true;
                        reading = false;
                    }
                } else if(!hasMaxFuel) {
                    if(line[count] == 'f' && line[count + 1] == 'u' && line[count + 2] == 'e' && line[count + 3] == 'l' && line[count + 4] == ':') {
                        count += 4;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ' && line[count] != ';') {

                            currentValue += line[count];
                            count++;
                        }
                        //std::cout << currentValue << std::endl;
                        maxFuel = std::stoi(currentValue);
                        currentValue = "";
                        hasMaxFuel = true;
                        reading = false;
                    }
                } else if(!hasSpeed) {
                    if(line[count] == 's' && line[count + 1] == 'p' && line[count + 2] == 'e' && line[count + 3] == 'e' && line[count + 4] == 'd' && line[count + 5] == ':') {
                        count += 5;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ' && line[count] != ';') {

                            currentValue += line[count];
                            count++;
                        }
                        speed = std::stof(currentValue);
                        currentValue = "";
                        hasSpeed = true;
                        reading = false;
                    }
                }
                count++;
            }

            for(int i = 0; i < (int)name.length(); i++) {
                if(name[i] == '_')
                    name[i] = ' ';
            }

            Spaceship *b = new Spaceship();
            b->create(maxFuel, name, filePath, type, speed, cost);
            return b; 
        }
    public:  
        static std::vector<Spaceship *> spaceships;
        static void setup() {
            parse();
        }
        static void printSpaceship(Spaceship *b) {
            std::cout << "Spaceship: \nname: " << b->getName() << "\ncost: " << b->getCost() << std::endl;
        }
        static void parse() {
            //std::cout << "Init " << std::endl;
            std::ifstream file("../Assets/gameData/spaceships.txt");
            //std::cout << "Opened!" << std::endl;
            std::string line;
            while(getline(file, line)) {
                //std::cout << "obamium" << std::endl;
                Spaceship *b = parseSpaceship(line);
                if(b != nullptr) {
                    //printSpaceship(b);
                    spaceships.push_back(b);
                }
            }
            file.close();
        }
};




#endif