#ifndef CONSTANTS_H_INCLUDED_OBAMA
#define CONSTANTS_H_INCLUDED_OBAMA

#include <iostream>

namespace constants {

    const double G = 6.67e-11;
    const double PI = 3.1415926535;
    const double SOLARRADIUS = 695.5e6;
    const double SOLARMASS = 1.989e30;
    const float FULLANGLE = PI * 2;
    const double EARTHMASS = 5.972e24;
    const double EARTHRADIUS = 6.361e6;
    const double EARTHDISTANCE = 1.52e9;
    const float MAGICNUMBER = 14.142135;

    enum class PlanetSize {
        Psmall, Pnormal, Plarge
    };

    const int GALAXYSIZE = 10000;

    const int GRIDSIDENUMBER = 250;
    const int GRIDSIDELENGTH = GALAXYSIZE / GRIDSIDENUMBER;

    const int SCREENX = 1920;
    const int SCREENY = 1080;

    const int UPPERGUIHEIGHT = 100;

    const int PLANETDESCRIPTIONX = 1520;
    const float PLANETDESCRIPTIONY = 197.5;
    const int PLANETDATAX = 1530;

    const int MOONRADIUSFACTIOR = 250;

    const int STARGUIX = 400;
    const int STARGUIY = 775;

    const unsigned int PLAYERID = 1;
};

enum class Tabs {
    economic,
    political,
    war,
    building,
    ships,
    buildShips,
    research,
    playerEmpire,
    none
};

inline Tabs openTab;


#endif // CONSTANTS_H_INCLUDED
