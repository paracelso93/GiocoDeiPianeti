#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <cstring>

#include "Star.h"

class Parser
{
    public:

        static void parseGalaxy(Star stars[]);
        static void createGalaxy(Star stars[]);

};

#endif // PARSER_H
