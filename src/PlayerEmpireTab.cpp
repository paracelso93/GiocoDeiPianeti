#include "PlayerEmpireTab.h"

PlayerEmpire *PlayerEmpireTab::mCurrentPlayerEmpire = nullptr;

void PlayerEmpireTab::setPlayerEmpire(PlayerEmpire *e) {
    mCurrentPlayerEmpire = e;
    mTitle.setString(e->getName());
    mEmpireColor.setFillColor(e->getEmpireColor());
    mRaceTex.loadFromFile(e->getRace());
    mFlagTex.loadFromFile(e->getFlag());
    mRaceSprite.setTexture(mRaceTex);
    mFlagSprite.setTexture(mFlagTex);
    mLeaderLabel.setString(e->getLeaderName());
}