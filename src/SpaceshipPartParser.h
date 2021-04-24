#ifndef SPACESHIPPARTPARSER_H
#define SPACESHIPPARTPARSER_H

#include "SpaceshipPart.h"
#include <fstream>

class SpaceshipPartParser {
    private: 
        static SpaceshipPart* parseSpaceshipPart(std::string line) {
            if(line[0] == '-' || line[0] == ' ') {
               // std::cout << "B" << std::endl;
                return nullptr;
            }
            SpaceshipPartType type = SpaceshipPartType::Damage;
            int index = 0;
            int cost = 0;
            int weight = 0;
            std::string name = "", filePath = "";
            int fuel = 0;
            float speed = 0.f;
            int damage = 0;
            int housing = 0;
            int shield = 0;
            int hull = 0;

            bool hasType = false, hasIndex = false, hasCost = false, hasWeight = false, hasName = false, hasFilePath = false, hasData = false;
            
            int count = 0;
            std::string currentValue = "";
            bool reading = false;
            while(line[count] != ';') {
                if(!hasIndex) {
                    
                    if(line[count] == ':') {
                        //std::cout << "HERE!" << std::endl;
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
                            case 'd': type = SpaceshipPartType::Damage;
                                break;
                            case 's': type = SpaceshipPartType::Shield;
                                break;
                            case 'h': type = SpaceshipPartType::Hull;
                                break;
                            case 'p': type = SpaceshipPartType::Housing;
                                break;
                            case 'e': type = SpaceshipPartType::Engine;
                                break;
                            case 'f': type = SpaceshipPartType::Fuel;
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
                }else if(!hasWeight) {
                    if(line[count] == 'w' && line[count + 1] == 'e' && line[count + 2] == 'i' && line[count + 3] == 'g' && line[count + 4] == 'h' && line[count + 5] == 't' && line[count + 6] == ':') {
                        //std::cout << "COST" << std::endl;
                        count += 6;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ') {
                            currentValue += line[count];
                            count++;
                        }
                        //std::cout << currentValue << std::endl;
                        weight = std::stoi(currentValue);
                        currentValue = "";
                        hasWeight = true;
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
                } else if(!hasData) {
                    if(line[count] == 'd' && line[count + 1] == 'a' && line[count + 2] == 't' && line[count + 3] == 'a' && line[count + 4] == ':') {
                        count += 4;
                        reading = true;
                        if(line.substr(count + 1, 3) == "dmg") {
                            //std::cout << line.substr(count + 4, line.length() - 2) << std::endl;
                            damage = std::stoi(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;
                        } else if(line.substr(count + 1, 3) == "shd") {
                            shield = std::stoi(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;

                        } else if(line.substr(count + 1, 3) == "hul") {
                            hull = std::stoi(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;
                        } else if(line.substr(count + 1, 3) == "hse") {
                            housing = std::stoi(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;
                        } else if(line.substr(count + 1, 3) == "eng") {
                            speed = std::stof(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;
                        } else if(line.substr(count + 1, 3) == "fel") {
                            fuel = std::stoi(line.substr(count + 5, line.length() - 3));
                            hasData = true;
                            count += 3;
                        }

                    }
                }
                count++;
            }
            for(int i = 0; i < (int)name.length(); i++) {
                if(name[i] == '_')
                    name[i] = ' ';
            }
            SpaceshipPart *b = new SpaceshipPart();
            b->setup(type, filePath, cost, weight, name);
            switch (type)
            {
                case SpaceshipPartType::Damage: b->setDamage(damage);
                    break;
                case SpaceshipPartType::Engine: b->setEngineSpeed(speed);
                    break;
                case SpaceshipPartType::Fuel: b->setFuel(fuel);
                    break;
                case SpaceshipPartType::Housing: b->setHousing(housing);
                    break;
                case SpaceshipPartType::Hull: b->setHull(hull);
                    break;
                case SpaceshipPartType::Shield: b->setShield(shield);
                    break;
                default: std::cout << "Missing type, obama" << std::endl;
                    break;
            }
            return b; 
        }
        
    public:  
        static void printSpaceshipPart(SpaceshipPart *p) {
            std::cout << p->getName() << " cost:" << p->getCost() << std::endl;
        }
        static std::vector<SpaceshipPart *> mSpaceshipParts;
        static void setup() {
            parse();
        }
        static void parse() {
            std::ifstream file("../Assets/gameData/spaceshipParts.txt");

            std::string line;
            while(getline(file, line)) {
                SpaceshipPart *p = parseSpaceshipPart(line);
                if(p != nullptr) {
                    //printSpaceshipPart(p);
                    mSpaceshipParts.push_back(p);
                }
            }
            file.close();
        }
};



#endif