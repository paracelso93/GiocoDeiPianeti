#include "Parser.h"


void Parser::parseGalaxy(Star stars[])
{
    std::cout << "Loading [";
    std::ifstream file("../Assets/gameData/data.txt");

    int k = 0;
    for (int i = 0; i < constants::GRIDSIDENUMBER; i++)
    {
        for (int j = 0; j < constants::GRIDSIDENUMBER; j++)
        {
            std::string line;
            getline(file, line);
            int count = 0;
            bool hasIndex = false, hasX = false, hasY = false, hasStar = false, hasRadius = false, hasR = false, hasG = false, hasB = false, hasA = false, hasColor = false, hasName = false;
            int index = 0, x = 0, y = 0, r = 0, g = 0, b = 0, a = 0;
            int planetNum = 0;
            std::string starName = "";
            bool hasPlanets = false;
            bool exists = false;
            float radius = 0;
            bool reading = false;
            bool readingP = false;
            bool hasPRadius = false, hasPR = false, hasPColor = false, hasPB = false, hasPG = false, hasPA = false, hasPVelocity = false, hasPName = false;
            int pr[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, pg[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, pb[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, pa[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 };
            constants::PlanetSize sizes[10] = { constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall, constants::PlanetSize::Psmall };
            float pradius[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, pvelocity[10] = { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 };
            int moonNum[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            std::string pname[10] = {"", "", "", "", "", "", "", "", "", ""};
            bool hasMoons = false;
            bool readingM = false;
            bool hasMRadius = false, hasMR = false, hasMColor = false, hasMB = false, hasMG = false, hasMA = false, hasMVelocity = false, hasMMass = false;
            int mr[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }};
            int mg[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }};
            int mb[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }};
            int ma[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }};
            float mradius[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }},
                mmass[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }},
             mvelocity[10][10] = {{ 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }, { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 }};
            std::string currentValue = "";

            while (line[count] != ';' && k <= constants::GRIDSIDENUMBER * constants::GRIDSIDENUMBER)
            {
                if (!hasIndex)
                {
                    if (line[count] == ':')
                    {
                        try
                        {
                            index = std::stoi(currentValue);
                        }
                        catch (std::invalid_argument const &e)
                        {
                            std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg  \n"
                                      << currentValue << std::endl;
                            return;
                        }
                        currentValue = "";
                        hasIndex = true;
                    }
                    else
                    {
                        currentValue += line[count];
                    }
                }
                else if (!hasX)
                {
                    if (line[count] == 'x' && line[count + 1] == ':')
                    {
                        reading = true;
                        count += 2;
                    }
                    if (reading)
                    {
                        if (line[count] == ' ')
                        {
                            reading = false;
                            try
                            {
                                x = std::stoi(currentValue);
                            }
                            catch (std::invalid_argument const &e)
                            {
                                std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg \n"
                                          << currentValue << std::endl;
                                return;
                            }
                            hasX = true;
                            currentValue = "";
                        }
                        else
                        {
                            currentValue += line[count];
                        }
                    }
                }
                else if (!hasY)
                {
                    if (line[count] == 'y' && line[count + 1] == ':')
                    {
                        reading = true;
                        count += 2;
                    }
                    if (reading)
                    {
                        if (line[count] == ' ')
                        {
                            reading = false;
                            try
                            {
                                y = std::stoi(currentValue);
                            }
                            catch (std::invalid_argument const &e)
                            {
                                std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg \n"
                                          << currentValue << std::endl;
                                return;
                            }
                            hasY = true;
                            currentValue = "";
                        }
                        else
                        {
                            currentValue += line[count];
                        }
                    }
                }
                else if (!hasStar)
                {
                    if (line[count] == 'e' && line[count + 1] == 'x' && line[count + 2] == 'i' && line[count + 3] == 's' && line[count + 4] == 't' && line[count + 5] == 's' && line[count + 6] == ':')
                    {
                        exists = line[count + 7] == '0' ? false : true;
                        count += 6;
                        hasStar = true;
                    }
                }
                else if(!hasName) {
                    if(line[count] == 'n' && line[count + 1] == 'a' && line[count + 2] == 'm' && line[count + 3] == 'e' && line[count + 4] == ':') {
                        count += 5;
                        reading = true;
                    }
                    if(reading) {
                        if(line[count] == ' ') {
                            reading = false;
                            starName = currentValue;
                            hasName = true;
                            currentValue = "";
                        } else {
                            currentValue += line[count];
                        }
                    }
                }
                else if (!hasRadius)
                {
                    if (line[count] == 'r' && line[count + 1] == 'a' && line[count + 2] == 'd' && line[count + 3] == 'i' && line[count + 4] == 'u' && line[count + 5] == 's' && line[count + 6] == ':')
                    {
                        reading = true;
                        count += 7;
                    }
                    if (reading)
                    {
                        if (line[count] == ' ')
                        {
                            reading = false;
                            try
                            {
                                radius = std::stod(currentValue);
                            }
                            catch (std::invalid_argument const &e)
                            {
                                std::cout << "BAD INPUT\nString Was: salam salam  " << currentValue << std::endl;
                            }
                            hasRadius = true;
                            currentValue = "";
                        }
                        else
                        {
                            currentValue += line[count];
                        }
                    }
                }
                else if (!hasColor)
                {
                    if (line[count] == 'c' && line[count + 1] == 'o' && line[count + 2] == 'l' && line[count + 3] == 'o' && line[count + 4] == 'r' && line[count + 5] == ':')
                    {
                        count += 6;
                        reading = true;
                    }
                    if (reading)
                    {
                        if (!hasR)
                        {
                            if (line[count] == ',')
                            {
                                hasR = true;
                                try
                                {
                                    r = std::stoi(currentValue);
                                }
                                catch (std::invalid_argument const &e)
                                {
                                    std::cout << "BAD INPUT\nString Was: gfdghfg" << currentValue << std::endl;
                                }
                                currentValue = "";
                            }
                            else
                            {
                                currentValue += line[count];
                            }
                        }
                        else if (!hasG)
                        {
                            if (line[count] == ',')
                            {
                                hasG = true;
                                try
                                {
                                    g = std::stoi(currentValue);
                                }
                                catch (std::invalid_argument const &e)
                                {
                                    std::cout << "BAD INPUT\nString Was: aesdf" << currentValue << std::endl;
                                }
                                currentValue = "";
                            }
                            else
                            {
                                currentValue += line[count];
                            }
                        }
                        else if (!hasB)
                        {
                            if (line[count] == ',')
                            {
                                hasB = true;
                                try
                                {
                                    b = std::stoi(currentValue);
                                }
                                catch (std::invalid_argument const &e)
                                {
                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                }
                                currentValue = "";
                            }
                            else
                            {
                                currentValue += line[count];
                            }
                        }
                        else if (!hasA)
                        {
                            if (line[count] == ',')
                            {
                                hasA = true;
                                try
                                {
                                    a = std::stoi(currentValue);
                                }
                                catch (std::invalid_argument const &e)
                                {
                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                }
                                currentValue = "";
                                hasColor = true;
                            }
                            else
                            {
                                currentValue += line[count];
                            }
                        }
                    }
                }
                else if (!hasPlanets)
                {
                    if (line[count] == 'p' && line[count + 1] == 'l' && line[count + 2] == 'a' && line[count + 3] == 'n' && line[count + 4] == 'e' && line[count + 5] == 't' && line[count + 6] == 's' && line[count + 7] == ':')
                    {
                        if (line[count + 8] == ';')
                        {
                            break;
                        }
                        readingP = true;
                        count += 9;
                    }
                    if (readingP)
                    {
                        if (line[count] == '}')
                        {
                            planetNum++;
                            reading = false;
                            hasPRadius = false;
                            hasPA = false;
                            hasPG = false;
                            hasPB = false;
                            hasPR = false;
                            hasPColor = false;
                            hasPVelocity = false;
                            hasMoons = false;
                        }
                        else if(!hasPName) {
                            if(line[count] == 'n' && line[count + 1] == 'a' && line[count + 2] == 'm' && line[count + 3] == 'e' && line[count + 4] == ':') {
                                count += 5;
                                reading = true;
                            }
                            if(reading) {
                                if(line[count] == ' ') {
                                    reading = false;
                                    pname[planetNum] = currentValue;
                                    hasPName = true;
                                    currentValue = "";
                                } else {
                                    currentValue += line[count];
                                }
                            }
                        }
                        else if (!hasPRadius)
                        {
                            if (line[count] == 'r' && line[count + 1] == 'a' && line[count + 2] == 'd' && line[count + 3] == 'i' && line[count + 4] == 'u' && line[count + 5] == 's' && line[count + 6] == ':')
                            {
                                count += 7;
                                reading = true;
                            }
                            if (reading)
                            {
                                if (line[count] == 's' || line[count] == 'm' || line[count] == 'l')
                                {
                                    hasPRadius = true;
                                    try
                                    {
                                        pradius[planetNum] = std::stod(currentValue);
                                    }
                                    catch (std::invalid_argument const &e)
                                    {
                                        std::cout << "BAD INPUT\nString Was: !" << currentValue << "!" << std::endl;
                                        std::cout << "planetnum: " << planetNum << "\n";
                                        std::cout << "index: " << index << "string: " << currentValue << std::endl;
                                        return;
                                    }
                                    switch(line[count]) {
                                        case 's': sizes[planetNum] = constants::PlanetSize::Psmall;
                                            break;
                                        case 'm': sizes[planetNum] = constants::PlanetSize::Pnormal;
                                            break;
                                        case 'l': sizes[planetNum] = constants::PlanetSize::Plarge;
                                            break;
                                    }
                                    currentValue = "";
                                    reading = false;
                                }
                                else
                                {
                                    if (line[count] != '{' && line[count] != '[' && line[count] != ':' && line[count] != 's')
                                        currentValue += line[count];
                                }
                            }
                        }
                        else if (!hasPVelocity)
                        {
                            if (line[count] == 'v' && line[count + 1] == 'e' && line[count + 2] == 'l' && line[count + 3] == 'o' && line[count + 4] == 'c' && line[count + 5] == 'i' && line[count + 6] == 't' && line[count + 7] == 'y' && line[count + 8] == ':')
                            {
                                count += 9;
                                reading = true;
                            }
                            if (reading)
                            {
                                if (line[count] == ' ')
                                {
                                    hasPVelocity = true;
                                    try
                                    {
                                        pvelocity[planetNum] = std::stod(currentValue);
                                    }
                                    catch (std::invalid_argument const &e)
                                    {
                                        std::cout << "BAD INPUT\nString Was: ?" << currentValue << "?" << std::endl;
                                        return;
                                    }
                                    currentValue = "";
                                    reading = false;
                                }
                                else
                                {
                                    if (line[count] != '{' && line[count] != '[' && line[count] != ':' && line[count] != 's')
                                        currentValue += line[count];
                                }
                            }
                        }
                        else if (!hasPColor)
                        {
                            if (line[count] == 'c' && line[count + 1] == 'o' && line[count + 2] == 'l' && line[count + 3] == 'o' && line[count + 4] == 'r' && line[count + 5] == ':')
                            {
                                count += 6;
                                reading = true;
                            }
                            if (reading)
                            {
                                if (line[count] == ',')
                                {
                                    if (!hasPR)
                                    {
                                        hasPR = true;

                                        try
                                        {
                                            pr[planetNum] = std::stoi(currentValue);
                                        }
                                        catch (std::invalid_argument const &e)
                                        {
                                            std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                            return;
                                        }
                                        currentValue = "";
                                    }
                                    else if (!hasPG)
                                    {
                                        hasPG = true;

                                        try
                                        {
                                            pg[planetNum] = std::stoi(currentValue);
                                        }
                                        catch (std::invalid_argument const &e)
                                        {
                                            std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                            return;
                                        }
                                        currentValue = "";
                                    }
                                    else if (!hasPB)
                                    {
                                        hasPB = true;

                                        try
                                        {
                                            pb[planetNum] = std::stoi(currentValue);
                                        }
                                        catch (std::invalid_argument const &e)
                                        {
                                            std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                            return;
                                        }
                                        currentValue = "";
                                    }
                                    else if (!hasPA)
                                    {
                                        hasPA = true;

                                        try
                                        {
                                            pa[planetNum] = std::stoi(currentValue);
                                        }
                                        catch (std::invalid_argument const &e)
                                        {
                                            std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                            return;
                                        }
                                        currentValue = "";
                                        reading = false;
                                        hasPColor = true;
                                    }
                                }
                                else
                                {
                                    if (line[count] != '{' && line[count] != '[')
                                        currentValue += line[count];
                                }
                            }
                        }
                        else if (!hasMoons)
                        {
                            if (line[count] == 'm' && line[count + 1] == 'o' && line[count + 2] == 'o' && line[count + 3] == 'n' && line[count + 4] == 's' && line[count + 5] == ':')
                            {
                                if(line[count + 6] == '}') {
                                    hasMoons = true;
                                    readingM = false;
                                    count += 7;



                                } else {
                                    readingM = true;
                                    count += 7;
                                }

                            }
                            if (readingM)
                            {
                                if (line[count] == ']')
                                {
                                    moonNum[planetNum]++;
                                    //std::cout << moonNum[planetNum] << " : " << planetNum << std::endl;

                                    reading = false;
                                    hasMRadius = false;
                                    hasMA = false;
                                    hasMR = false;
                                    hasMG = false;
                                    hasMB = false;
                                    hasMColor = false;
                                    hasMVelocity = false;
                                }
                                else if (!hasMRadius)
                                {
                                    if (line[count] == 'r' && line[count + 1] == 'a' && line[count + 2] == 'd' && line[count + 3] == 'i' && line[count + 4] == 'u' && line[count + 5] == 's' && line[count + 6] == ':')
                                    {
                                        count += 7;
                                        reading = true;
                                    }
                                    if (reading)
                                    {
                                        if (line[count] == ' ')
                                        {
                                            hasMRadius = true;

                                            try
                                            {
                                                mradius[moonNum[planetNum]][planetNum] = std::stod(currentValue);
                                            }
                                            catch (std::invalid_argument const &e)
                                            {
                                                std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                                return;
                                            }
                                            currentValue = "";
                                            reading = false;
                                        }
                                        else
                                        {
                                            if (line[count] != '{' && line[count] != '[')
                                                currentValue += line[count];
                                        }
                                    }
                                }
                                else if (!hasMMass)
                                {
                                    if (line[count] == 'm' && line[count + 1] == 'a' && line[count + 2] == 's' && line[count + 3] == 's' && line[count + 4] == ':')
                                    {
                                        count += 5;
                                        reading = true;
                                    }
                                    if (reading)
                                    {
                                        if (line[count] == ' ')
                                        {
                                            hasMMass = true;

                                            try
                                            {
                                                mmass[moonNum[planetNum]][planetNum] = std::stod(currentValue);
                                            }
                                            catch (std::invalid_argument const &e)
                                            {
                                                std::cout << "BAD INPUT\nString Was: obama " << currentValue << std::endl;
                                                return;
                                            }
                                            currentValue = "";
                                            reading = false;
                                        }
                                        else
                                        {
                                            if (line[count] != '{' && line[count] != '[')
                                                currentValue += line[count];
                                        }
                                    }
                                }
                                else if (!hasMVelocity)
                                {
                                    if (line[count] == 'v' && line[count + 1] == 'e' && line[count + 2] == 'l' && line[count + 3] == 'o' && line[count + 4] == 'c' && line[count + 5] == 'i' && line[count + 6] == 't' && line[count + 7] == 'y' && line[count + 8] == ':')
                                    {
                                        count += 9;
                                        reading = true;
                                    }
                                    if (reading)
                                    {
                                        if (line[count] == ' ')
                                        {
                                            hasMVelocity = true;

                                            try
                                            {
                                                mvelocity[moonNum[planetNum]][planetNum] = std::stod(currentValue);
                                            }
                                            catch (std::invalid_argument const &e)
                                            {
                                                std::cout << "BAD INPUT\nString Was: moonV: " << currentValue << std::endl;
                                                return;
                                            }
                                            currentValue = "";
                                            reading = false;
                                        }
                                        else
                                        {
                                            if (line[count] != '{' && line[count] != '[')
                                                currentValue += line[count];
                                        }
                                    }
                                }
                                else if (!hasMColor)
                                {
                                    if (line[count] == 'c' && line[count + 1] == 'o' && line[count + 2] == 'l' && line[count + 3] == 'o' && line[count + 4] == 'r' && line[count + 5] == ':')
                                    {
                                        count += 6;
                                        reading = true;
                                    }
                                    if (reading)
                                    {
                                        if (line[count] == ',')
                                        {
                                            if (!hasMR)
                                            {
                                                hasMR = true;

                                                try
                                                {
                                                    mr[moonNum[planetNum]][planetNum] = std::stoi(currentValue);
                                                }
                                                catch (std::invalid_argument const &e)
                                                {
                                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                                    return;
                                                }
                                                currentValue = "";
                                            }
                                            else if (!hasMG)
                                            {
                                                hasMG = true;

                                                try
                                                {
                                                    mg[moonNum[planetNum]][planetNum] = std::stoi(currentValue);
                                                }
                                                catch (std::invalid_argument const &e)
                                                {
                                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                                    return;
                                                }
                                                currentValue = "";
                                            }
                                            else if (!hasMB)
                                            {
                                                hasMB = true;

                                                try
                                                {
                                                    mb[moonNum[planetNum]][planetNum] = std::stoi(currentValue);
                                                }
                                                catch (std::invalid_argument const &e)
                                                {
                                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                                    return;
                                                }
                                                currentValue = "";
                                            }
                                            else if (!hasMA)
                                            {
                                                hasMA = true;

                                                try
                                                {
                                                    ma[moonNum[planetNum]][planetNum] = std::stoi(currentValue);
                                                }
                                                catch (std::invalid_argument const &e)
                                                {
                                                    std::cout << "BAD INPUT\nString Was:gzdfhtadshadzxg " << currentValue << std::endl;
                                                    return;
                                                }
                                                currentValue = "";
                                                reading = false;
                                                hasMColor = true;
                                            }
                                        }
                                        else
                                        {
                                            if (line[count] != '{' && line[count] != '[')
                                                currentValue += line[count];
                                        }
                                    }
                                }
                            }
                        }


                    }
                }
                if (line[count] == ';')
                    break;
                count++;
            }
            int currentIndex = i * constants::GRIDSIDENUMBER + j;

            stars[currentIndex].mX = x;
            stars[currentIndex].mY = y;
            stars[currentIndex].mExists = exists;
            if (stars[currentIndex].mExists)
            {
                stars[currentIndex].mRadius = radius;
                double sampleMass = sqrt(sqrt(pow(radius, 5)));
                stars[currentIndex].mMass = sampleMass;
                stars[currentIndex].mColor.r = r;
                stars[currentIndex].mColor.g = g;
                stars[currentIndex].mColor.b = b;
                stars[currentIndex].mColor.a = a;
                stars[currentIndex].mGuiShape.setPosition(300, constants::STARGUIY + constants::UPPERGUIHEIGHT);
                stars[currentIndex].mGuiShape.setFillColor(sf::Color(r, g, b, a));
                stars[currentIndex].mGuiShape.setRadius(radius * 8);
                stars[currentIndex].mShape.setRadius(radius * 2);
                stars[currentIndex].mShape.setPosition(stars[currentIndex].mX, stars[currentIndex].mY);
                stars[currentIndex].mShape.setFillColor(sf::Color(r, g, b, a));
                stars[currentIndex].mNumP = planetNum;
                stars[currentIndex].mName = starName;
                //std::cout << planetNum << std::endl;
                for (int alfa = 0; alfa < planetNum; alfa++)
                {
                    stars[currentIndex].mPlanets[alfa].mRadius = pradius[alfa];
                    stars[currentIndex].mPlanets[alfa].mSize = sizes[alfa];
                    double samplePMass;
                    if(stars[currentIndex].mPlanets[alfa].mSize == constants::PlanetSize::Psmall) {
                        samplePMass = pow(stars[currentIndex].mPlanets[alfa].mRadius, 1 / 0.3);
                    } else if(stars[currentIndex].mPlanets[alfa].mSize == constants::PlanetSize::Pnormal) {
                        samplePMass = pow(stars[currentIndex].mPlanets[alfa].mRadius, 1 / 0.5);
                    } else {
                        samplePMass = pow(stars[currentIndex].mPlanets[alfa].mRadius / 22.6, -1 / 0.0886);
                    }

                    stars[currentIndex].mPlanets[alfa].mMass = samplePMass;

                    stars[currentIndex].mPlanets[alfa].mAngularVelocity = pvelocity[alfa];
                    stars[currentIndex].mPlanets[alfa].mAngle = 0.f;
                    stars[currentIndex].mPlanets[alfa].mColor.r = pr[alfa];
                    stars[currentIndex].mPlanets[alfa].mColor.g = pg[alfa];
                    stars[currentIndex].mPlanets[alfa].mColor.b = pb[alfa];
                    stars[currentIndex].mPlanets[alfa].mColor.a = pa[alfa];
                    stars[currentIndex].mPlanets[alfa].mNumn = moonNum[alfa];
                    stars[currentIndex].mPlanets[alfa].mName = pname[alfa];

                    if(alfa == 0) {
                        stars[currentIndex].mPlanets[alfa].mDistance = 50 + 50 + (stars[currentIndex].mPlanets[alfa].mRadius * 10);
                    } else {
                        stars[currentIndex].mPlanets[alfa].mDistance = stars[currentIndex].mPlanets[alfa - 1].mDistance + 50 + (stars[currentIndex].mPlanets[alfa].mRadius * 10);
                    }

                    stars[currentIndex].mOrbits[alfa].setFillColor(sf::Color::Transparent);
                    stars[currentIndex].mOrbits[alfa].setOutlineColor(sf::Color(255, 255, 255, 100));
                    stars[currentIndex].mOrbits[alfa].setOutlineThickness (4);

                    stars[currentIndex].mOrbits[alfa].setRadius(stars[currentIndex].mPlanets[alfa].mDistance);
                    stars[currentIndex].mOrbits[alfa].setPosition(300 - stars[currentIndex].mPlanets[alfa].mDistance + stars[currentIndex].mRadius * 8, 885 - stars[currentIndex].mPlanets[alfa].mDistance + stars[currentIndex].mRadius * 8);

                    for (int beta = 0; beta < moonNum[alfa]; beta++)
                    {
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mRadius = mradius[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mMass = mmass[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mAngularVelocity = mvelocity[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mAngle = 0.f;
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mColor.r = mr[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mColor.g = mg[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mColor.b = mb[beta][alfa];
                        stars[currentIndex].mPlanets[alfa].mMoons[beta].mColor.a = ma[beta][alfa];

                        //if(stars[currentIndex].planets[alfa].radius <= stars[currentIndex].planets[alfa].moons[beta].radius) {
                        //    std::cout << "ERROR, MOON TOO BIG!\nPlanetRadius: " << stars[currentIndex].planets[alfa].radius << "\nMoonRadius: " << stars[currentIndex].planets[alfa].moons[beta].radius << std::endl;
                        //    exit(1);
                        //}

                        if(beta == 0) {
                            stars[currentIndex].mPlanets[alfa].mMoons[beta].mDistance = 25 * (beta + 1) + (stars[currentIndex].mPlanets[alfa].mRadius) * 5;
                        } else {
                            stars[currentIndex].mPlanets[alfa].mMoons[beta].mDistance = 25 * (beta + 1) + stars[currentIndex].mPlanets[alfa].mMoons[beta - 1].mDistance;
                        }
                    }
                }
            }
            k++;
        }
        if (i % (int)(constants::GRIDSIDENUMBER / 17) == 0)
        {
            std::cout << "=";
        }
    }
    std::cout << "]\n Process Complete!" << std::endl;
    file.close();
}

void Parser::createGalaxy(Star stars[])
{
    std::ofstream file("../Assets/gameData/data.txt");

    std::cout << "Creating Galaxy: [";

    for (int i = 0; i < constants::GRIDSIDENUMBER; i++)
    {
        for (int j = 0; j < constants::GRIDSIDENUMBER; j++)
        {
            int currentIndex = i * constants::GRIDSIDENUMBER + j;
            stars[currentIndex].createStar(i * constants::GRIDSIDELENGTH, j * constants::GRIDSIDELENGTH);
            //if(stars[(int)stars.size() - 1].exists) {
            //    std::cout << "a\n";
            //}
            if (stars[currentIndex].mExists)
            {
                file << currentIndex
                     << ": x:" << stars[currentIndex].mX
                     << " y:" << stars[currentIndex].mY
                     << " exists:1"
                     << " name:" << stars[currentIndex].mName
                     << " radius:" << stars[currentIndex].mRadius
                     << " color:" << (int)stars[currentIndex].mColor.r << "," << (int)stars[currentIndex].mColor.g << "," << (int)stars[currentIndex].mColor.b << "," << (int)stars[currentIndex].mColor.a << ","
                     << " planets:";
                for (int k = 0; k < stars[currentIndex].mNumP; k++)
                {
                    file << "{name:" << stars[currentIndex].mPlanets[k].mName <<" radius:" << stars[currentIndex].mPlanets[k].mRadius;
                    switch(stars[currentIndex].mPlanets[k].mSize) {
                        case constants::PlanetSize::Psmall: file << "s";
                            break;
                        case constants::PlanetSize::Pnormal: file << "m";
                            break;
                        case constants::PlanetSize::Plarge: file << "l";
                            break;
                    }
                    file << " velocity:" << stars[currentIndex].mPlanets[k].mAngularVelocity << " color:" << (int)stars[currentIndex].mPlanets[k].mColor.r << "," << (int)stars[currentIndex].mPlanets[k].mColor.g << "," << (int)stars[currentIndex].mPlanets[k].mColor.b << "," << (int)stars[currentIndex].mPlanets[k].mColor.a << ", moons:";
                    for (int t = 0; t < stars[currentIndex].mPlanets[k].mNumn; t++)
                    {
                        file << "[radius:" << stars[currentIndex].mPlanets[k].mMoons[t].mRadius << " mass:" << stars[currentIndex].mPlanets[k].mMoons[t].mMass << " velocity:" << stars[currentIndex].mPlanets[k].mMoons[t].mAngularVelocity <<  " color:" << (int)stars[currentIndex].mPlanets[k].mMoons[t].mColor.r << "," << (int)stars[currentIndex].mPlanets[k].mMoons[t].mColor.g << "," << (int)stars[currentIndex].mPlanets[k].mMoons[t].mColor.b << "," << (int)stars[currentIndex].mPlanets[k].mMoons[t].mColor.a << ",]";
                    }
                    file << "}";
                }
                file << ";\n";
            }
            else
            {
                file << currentIndex << ": x:" << stars[currentIndex].mX << " y:" << stars[currentIndex].mY << " exists:0;\n";
            }
        }
        if(i % (constants::GRIDSIDENUMBER / 17) == 0)
                std::cout << "=";
    }

    std::cout << "]\nProcess Completed!\n";

    file.close();
}

