#include "SnakeTrap.h"
#include "MacUILib.h"



SnakeTrap::SnakeTrap()
{
    /*
    * This is a constructor
    * We will initialize all the  data members here
    */
    srand(time(NULL));
    trapListSize = 8;
    // Regular Food symbol
    trapSymbol = 'X';  // Advanced Food symbol
    objPos temp;  // Temporary objPos
    temp.setObjPos(0, 0, '\0');  // Initialize temp
    trapPositions = new objPosArrayList(); // Dynamic array for food positions
    trapPositions->insertHead(temp); // Initialize foodPositions by inserting temp
}

SnakeTrap::~SnakeTrap()
{
    /*
    * This is a destructor
    */
    delete[] trapPositions;
}

void SnakeTrap::randomizeTrapPos(int &x, int &y){
    /*
     * This function generates a single food position
     */
    x = rand() % 15;  //following the instruction of PPA3
    y = rand() % 30;
}

void SnakeTrap::generateTraps(objPosArrayList* foodPositions,objPosArrayList* playerPosList){
    int x = 0, y = 0;
    int count = 0;
    bool valid, advancedValid;
    //for(int i = 0; i<listSize;i++){
         //if(foodPositions->getSize() == 0)
    //{
        
        //break;
    //}
        //foodPositions->removeTail();
    //}
    while (count < trapListSize)
    {
        randomizeTrapPos(x, y);
        valid = positionValidation(trapPositions, foodPositions, x, y);
        advancedValid = AdvancedPositionValidation(playerPosList, x, y);
        if (valid && advancedValid)
        {
            addItemToList(x, y);

            count++;
        }
    }
}


bool SnakeTrap::positionValidation(objPosArrayList *list, objPosArrayList* foodPositions, int x, int y)
{
    for (int j = 0; j < list->getSize(); j++)
    // Check if the food position is the same as the previous food position
    {
        objPos tempTraps;
        list->getElement(tempTraps, j);
        if ((tempTraps.x == x && tempTraps.y == y))
        {
            return false;
        }
    }
    // Check if the food position is the same as the player position
    for (int j = 0; j < foodPositions->getSize(); j++)
    {
        objPos tempPos;
        foodPositions->getElement(tempPos, j);
        if (tempPos.x == x && tempPos.y == y)
        {
            return false;
        }
    }
    // Additional check for border items
    if (x == 0 || x == 9 || y == 0 || y == 19)
    {
        return false;
    }
    if (x <= 0 || x >= 9 || y <= 1 || y >= 19)
    {
        return false;
    }
    return true;
}

bool SnakeTrap::AdvancedPositionValidation(objPosArrayList* playerPosList, int x, int y)
{
    /*
     * This function checks if the food position is the same as the player body
     * if yes, return false
     * if no, return true
     */
    objPos snakeBody;
    for (int j = 0; j < playerPosList->getSize(); j++)
    {
        playerPosList->getElement(snakeBody, j);
        if ((snakeBody.x == x && snakeBody.y == y))
        {
            return false;
        }
    }
    return true;
}


void SnakeTrap::addItemToList(int x, int y){
    objPos newPos;
    newPos.setObjPos(x, y, trapSymbol);

    if(trapPositions->getSize() >= trapListSize){
        trapPositions->removeTail();
    }
    
    trapPositions->insertHead(newPos);
}

objPosArrayList *SnakeTrap::getTrapPos(){
    return trapPositions;
}

bool SnakeTrap::isTrapTriggered(objPosArrayList* playerPosList) {
    if (playerPosList == nullptr || playerPosList->getSize() == 0)
    {
        return false;  // No player position available to check
    }
    objPos playerHeadPos;
    playerPosList->getHeadElement(playerHeadPos);
    for (int i = 0; i < trapPositions->getSize(); ++i)
    {
        objPos temp;
        trapPositions->getElement(temp, i);
        // Check if food is eaten by the Snake head only
        if (temp.x == playerHeadPos.x && temp.y == playerHeadPos.y)
        {
            //mainGameMechsRef->setExitTrue();
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}

bool SnakeTrap::isTrapTriggeredXY(int x, int y) {
    for (int i = 0; i < trapPositions->getSize(); ++i)
    {
        objPos temp;
        trapPositions->getElement(temp, i);
        // Check if food is eaten by the Snake head only
        if (temp.x == x && temp.y == y)
        {
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}
