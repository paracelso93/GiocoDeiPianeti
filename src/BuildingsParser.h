#ifndef BUILDINGSPARSER_H
#define BUILDINGSPARSER_H

#include <iostream>
#include <fstream>

#include "Building.h"

class BuildingsParser {
    private:
        static Building* parseBuilding(std::string line) {
            if(line[0] == '-' || line[0] == ' ') {
                //std::cout << "B" << std::endl;
                return nullptr;
            }
            BuildingTypes type = BuildingTypes::housing;
            int index = 0;
            int cost = 0;
            std::string name = "", filePath = "";

            bool hasType = false, hasIndex = false, hasCost = false, hasName = false, hasFilePath = false;
            
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
                        //std::cout << "TYPE" << std::endl;
                        switch(line[count + 5]) {
                            case 'h': type = BuildingTypes::housing;
                                break;
                            case 'm': type = BuildingTypes::military;
                                break;
                            case 'p': type = BuildingTypes::production;
                                break;
                            case 'e': type = BuildingTypes::energy;
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
                }
                count++;
            }

            for(int i = 0; i < (int)name.length(); i++) {
                if(name[i] == '_')
                    name[i] = ' ';
            }

            Building *b = new Building();
            b->setup(cost, name, filePath, type);
            return b;
        }
        static void printBuilding(Building *b) {
            std::cout << "Building: \nname: " << b->name << "\ncost: " << b->cost << std::endl;
        }
    public:  
        static std::vector<Building *> buildings;
        static void setup() {
            parse();
        }
        static void parse() {
            std::ifstream file("../Assets/gameData/buildings.txt");

            std::string line;
            while(getline(file, line)) {
                
                Building *b = parseBuilding(line);
                if(b != nullptr) {
                    //printBuilding(b);
                    buildings.push_back(b);
                }
            }
            file.close();
        }
}; 




#endif