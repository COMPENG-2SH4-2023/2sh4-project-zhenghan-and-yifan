#ifndef SNAKETRAP_H
#define SNAKETRAP_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

#include "GameMechs.h"

using namespace std;




class SnakeTrap{
    //ArrayList Design
private:
    objPosArrayList* trapPositions; // Dynamic array for food positions
    int trapListSize;
 
    char trapSymbol;

    GameMechs* mainGameMechsRef;

public:
    SnakeTrap();
    ~SnakeTrap();
    void randomizeTrapPos(int &x, int &y);
    bool positionValidation(objPosArrayList *list, objPosArrayList* playerPosList, int x, int y);
    bool AdvancedPositionValidation(objPosArrayList* playerPosList, int x, int y);
    void addItemToList(int x, int y);
    void generateTraps(objPosArrayList* foodPositions,objPosArrayList* playerPosList);
    objPosArrayList *getTrapPos();
    bool isTrapTriggered(objPosArrayList* playerPosList);
    bool isTrapTriggeredXY(int x, int y);
};

#endif