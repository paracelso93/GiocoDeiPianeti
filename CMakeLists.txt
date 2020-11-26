cmake_minimum_required(VERSION 3.11)

project(GiocoDeiPianeti VERSION 0.1 LANGUAGES CXX)

add_executable(GiocoDeiPianeti src/Animation.cpp 
src/Battle.cpp 
src/BattleMap.cpp 
src/Building.cpp 
src/BuildingsParser.cpp 
src/BuildTab.cpp 
src/DysonSphere.cpp 
src/EconomicsTab.cpp 
    src/Empire.cpp 
    src/EmpireTab.cpp 
    src/Game.cpp 
    src/GridNode.cpp 
    src/GUI_Alert.cpp 
    src/GUI_Button.cpp 
    src/GUI_Label.cpp 
    src/GUI_LoadingBar.cpp 
    src/GUI_Panel.cpp 
    src/main.cpp 
    src/Menu.cpp 
    src/Moon.cpp 
    src/Parser.cpp 
    src/Planet.cpp 
    src/PlayerEmpire.cpp 
    src/PlayerEmpireTab.cpp 
    src/Research.cpp 
    src/ResearchParser.cpp 
    src/ResearchTab.cpp 
    src/Spaceship.cpp 
    src/SpaceshipBuildTab.cpp 
    src/SpaceshipParser.cpp 
    src/SpaceshipPart.cpp 
    src/SpaceshipPartParser.cpp 
    src/SpaceshipTab.cpp 
    src/Star.cpp 
    src/StarGUI.cpp 
    src/TimeController.cpp 
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_compile_options(GiocoDeiPianeti PRIVATE -Werror)

target_compile_features(GiocoDeiPianeti PRIVATE cxx_std_17)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

#Include SOL2 header files
#include_directories(${CMAKE_SOURCE_DIR}/sol2/include)

#add_subdirectory(ECS)

target_link_libraries(GiocoDeiPianeti
        PUBLIC
        sfml-graphics sfml-audio sfml-window sfml-system )
