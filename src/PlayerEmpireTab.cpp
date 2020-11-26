#include "PlayerEmpireTab.h"

PlayerEmpire *PlayerEmpireTab::currentPlayerEmpire = nullptr;

void PlayerEmpireTab::setPlayerEmpire(PlayerEmpire *e) {
    currentPlayerEmpire = e;
    title.setString(e->getName());
    empireColor.setFillColor(e->getEmpireColor());
    raceTex.loadFromFile(e->getRace());
    flagTex.loadFromFile(e->getFlag());
    raceSprite.setTexture(raceTex);
    flagSprite.setTexture(flagTex);
    leaderLabel.setString(e->getLeaderName());
}