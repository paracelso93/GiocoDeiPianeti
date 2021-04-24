#ifndef RESEARCHPARSER_H
#define RESEARCHPARSER_H

#include "Research.h"
#include "SpaceshipPartParser.h"
#include "BuildingsParser.h"
#include "SpaceshipsParser.h"

class ResearchParser {
    private:   
        static Research* parseResearch(std::string line) {
            if(line[0] == '-' || line[0] == ' ') {
               // std::cout << "B" << std::endl;
                return nullptr;
            }
            ResearchTypes type = ResearchTypes::Buff;
            ResearchField field = ResearchField::Physics;
            int index = 0;
            int cost = 0;
            std::string name = "", filePath = "";
            int difficulty = 0;
            int dataIndex = 0;
            bool hasType = false, hasField = false, hasIndex = false, hasCost = false, hasData = false, hasName = false, hasFilePath = false, hasDifficulty = false;
            
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
                            case 'f': type = ResearchTypes::Buff;
                                break;
                            case 's': type = ResearchTypes::UnlockShip;
                                break;
                            case 'b': type = ResearchTypes::UnlockBuilding;
                                break;
                            case 'p': type = ResearchTypes::UnlockShipPart;
                                break;
                            default: std::cerr << "Error, unspecified value or non-existant type." << std::endl;
                                break; 
                        }
                        count += 6;
                        hasType = true;
                        //std::cout << line[count] << line[count + 1] << line[count + 2] << line[count + 3] << line[count + 4] << line[count + 5] << std::endl;
                    }
                }
                else if(!hasField) {
                    if(line[count] == 'f' && line[count + 1] == 'i' && line[count + 2] == 'e' && line[count + 3] == 'l' && line[count + 4] == 'd' && line[count + 5] == ':') {
                        //std::cout << line[count + 5] << std::endl;
                        switch(line[count + 6]) {
                            case 'p': field = ResearchField::Physics;
                                break;
                            case 'e': field = ResearchField::Engineering;
                                break;
                            case 'b': field = ResearchField::Biology;
                                break;
                            case 'c': field = ResearchField::Chemistry;
                                break;
                            default: std::cerr << "Error, unspecified value or non-existant type." << std::endl;
                                break; 
                        }
                        count += 7;
                        hasField = true;
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
                }else if(!hasDifficulty) {
                    if(line[count] == 'd' && line[count + 1] == 'i' && line[count + 2] == 'f' && line[count + 3] == 'f' && line[count + 4] == ':') {
                        //std::cout << "COST" << std::endl;
                        count += 4;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ') {
                            currentValue += line[count];
                            count++;
                        }
                        //std::cout << currentValue << std::endl;
                        difficulty = std::stoi(currentValue);
                        currentValue = "";
                        hasDifficulty = true;
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
                        //std::cout << "COST" << std::endl;
                        count += 4;
                        reading = true;
                    } else if(reading) {
                        while(line[count] != ' ') {
                            currentValue += line[count];
                            count++;
                        }
                        //std::cout << currentValue << std::endl;
                        dataIndex = std::stoi(currentValue);
                        currentValue = "";
                        hasData = true;
                        reading = false;
                    }
                }
                count++;
            }
            for(int i = 0; i < (int)name.length(); i++) {
                if(name[i] == '_')
                    name[i] = ' ';
            } 
            Research *b = new Research();
            b->setup(name, cost, type, field, filePath, difficulty);
            switch(type) {
                case ResearchTypes::Buff: break;
                case ResearchTypes::UnlockBuilding: b->unlockBuilding(BuildingsParser::mBuildings[dataIndex]);
                        break;
                case ResearchTypes::UnlockShip: b->unlockShip(SpaceshipsParser::mSpaceships[dataIndex]);
                        break;
                case ResearchTypes::UnlockShipPart: b->unlockPart(SpaceshipPartParser::mSpaceshipParts[dataIndex]);
                        break;
                default: std::cout << "Invalid type!" << std::endl;
            }
            return b; 
        }

        static void printResearch(Research *r) {
            std::cout << r->getName() << ": cost:" << r->getCost() << std::endl;
        }

    public:   
        static std::vector<Research *> mResearches;
        static void setup() {
            parse();
        }
        static void parse() {
            std::fstream file("../Assets/gameData/researches.txt");

            std::string line;
            while(getline(file, line)) {
                Research *p = parseResearch(line);
                if(p != nullptr) {
                    //printResearch(p);
                    mResearches.push_back(p);
                }
            }
            file.close();
        }
};



#endif