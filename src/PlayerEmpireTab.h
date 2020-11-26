#ifndef PLAYEREMPIRETAB_H
#define PLAYEREMPIRETAB_H

#include "EmpireTab.h"
#include "PlayerEmpire.h"

class PlayerEmpireTab : public EmpireTab {
    public:  
        static void setPlayerEmpire(PlayerEmpire *e);

    private:  
        static PlayerEmpire *currentPlayerEmpire;
};

#endif