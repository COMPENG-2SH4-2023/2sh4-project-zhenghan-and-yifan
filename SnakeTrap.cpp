#include "SnakeTrap.h"
#include "MacUILib.h"



SnakeTrap::SnakeTrap()
{
    /**
     * This is a constructor
     * We will initialize all the  data members here
     */
    srand(time(NULL));
    trapListSize = 5;
    trapSymbol = 'X';  // Trap symbol, exit the game if eaten
    objPos temp;  // Temporary objPos
    temp.setObjPos(0, 0, '\0');  // Initialize temp
    trapPositions = new objPosArrayList(); // Dynamic array for trap positions
    trapPositions->insertHead(temp); // Initialize trapPositions by inserting temp
}

SnakeTrap::~SnakeTrap()
{
    /**
     * This is a destructor
     * We will deallocate all the dynamic memory here
     */
    delete[] trapPositions;
}

void SnakeTrap::randomizeTrapPos(int &x, int &y){
    /**
     * This function generates thr random trap position
     */
    x = rand() % 15;  
    y = rand() % 30;
}

void SnakeTrap::generateTraps(objPosArrayList* foodPositions,objPosArrayList* playerPosList){
    /**
     * This function generates the trap positions
     */
    int x = 0, y = 0;
    int count = 0;
    bool valid, advancedValid;

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
    /**
     * This function checks if the trap position is the same as the previous trap position and all other restrictions
     * Same logic as the food position validation in FoodBucket.cpp
     * if yes, return false
     * if no, return true
     */
    for (int j = 0; j < list->getSize(); j++)
    // Check if the trap position is the same as the previous trap position
    {
        objPos tempTraps;
        list->getElement(tempTraps, j);
        if ((tempTraps.x == x && tempTraps.y == y))
        {
            return false;
        }
    }
    // Check if the trap position is the same as the player position
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
    /**
     * This function checks if the trap position is the same as the player body
     * Same logic as the food position validation in FoodBucket.cpp
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
    /**
     * This function adds the trap position to the trap position list
     * Same logic with the addItemToList in FoodBucket.cpp
     */
    objPos newPos;
    newPos.setObjPos(x, y, trapSymbol);

    if(trapPositions->getSize() >= trapListSize){
        trapPositions->removeTail();
    }
    
    trapPositions->insertHead(newPos);
}

objPosArrayList *SnakeTrap::getTrapPos(){
    /**
     * This function returns the trap position list
     */
    return trapPositions;
}

bool SnakeTrap::isTrapTriggered(objPosArrayList* playerPosList) {
    /**
     * This function checks if the trap is eaten by the Snake head
     * if yes, return true
     * if no, return false
     */
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
        // Check if trap is eaten by the Snake head only
        if (temp.x == playerHeadPos.x && temp.y == playerHeadPos.y)
        {
            //mainGameMechsRef->setExitTrue();
            return true;  // trap is eaten
        }
    }
    return false;  // No trap eaten
}

bool SnakeTrap::isTrapTriggeredXY(int x, int y) {
    /**
     * This function checks if the trap is eaten by the Snake head with the given x and y of the head
     * if yes, return true
     * if no, return false
     */
    for (int i = 0; i < trapPositions->getSize(); ++i)
    {
        objPos temp;
        trapPositions->getElement(temp, i);
        // Check if trpa is eaten by the Snake head only
        if (temp.x == x && temp.y == y)
        {
            return true;  // trap is eaten
        }
    }
    return false;  // No trap eaten
}
