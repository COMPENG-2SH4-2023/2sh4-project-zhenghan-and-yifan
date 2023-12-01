#include "FoodBucket.h"
#include "MacUILib.h"


FoodBucket::FoodBucket()
{
    /*
    * This is a constructor
    * We will initialize all the  data members here
    */
    srand(time(NULL));
    listSize = 5;
    PossFoodCount = 1;
    NegFoodCount = 2;
    totalFoodCount = listSize + PossFoodCount + NegFoodCount;
    foodSymbol = 'O'; // Regular Food symbol
    PositiveFoodSymbol = 'P';  // Advanced Food symbol
    NegativeFoodSymbol = 'N';  // Advanced Food symbol
    objPos temp;  // Temporary objPos
    temp.setObjPos(0, 0, '\0');  // Initialize temp
    foodPositions = new objPosArrayList(); // Dynamic array for food positions
    foodPositions->insertHead(temp); // Initialize foodPositions by inserting temp
}

FoodBucket::~FoodBucket()
{
    /*
    * This is a destructor
    */
    delete[] foodPositions;
}

void FoodBucket::randomizeFoodPos(int &x, int &y){
    /*
     * This function generates a single food position
     */
    x = rand() % 15;  //following the instruction of PPA3
    y = rand() % 30;
}

void FoodBucket::generateFoods(objPosArrayList* playerPosList){
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
    while (count < listSize)
    {
        randomizeFoodPos(x, y);
        valid = positionValidation(foodPositions, playerPosList, x, y);
        advancedValid = AdvancedPositionValidation(playerPosList, x, y);
        if (valid && advancedValid)
        {
            addItemToList(x, y, foodSymbol);

            count++;
        }
    }
    while (count < PossFoodCount + listSize)
    {
        randomizeFoodPos(x, y);
        valid = positionValidation(foodPositions, playerPosList, x, y);
        advancedValid = AdvancedPositionValidation(playerPosList, x, y);
        if (valid && advancedValid)
        {
            addItemToList(x, y, PositiveFoodSymbol);
            count++;
        }
    }
    while (count < totalFoodCount)
    {
        randomizeFoodPos(x, y);
        valid = positionValidation(foodPositions, playerPosList, x, y);
        advancedValid = AdvancedPositionValidation(playerPosList, x, y);
        if (valid && advancedValid)
        {
            addItemToList(x, y, NegativeFoodSymbol);
            count++;
        }
    }
}


bool FoodBucket::positionValidation(objPosArrayList *list, objPosArrayList* playerPosList, int x, int y)
{
    for (int j = 0; j < list->getSize(); j++)
    // Check if the food position is the same as the previous food position
    {
        objPos tempFood;
        list->getElement(tempFood, j);
        if ((tempFood.x == x && tempFood.y == y))
        {
            return false;
        }
    }
    // Check if the food position is the same as the player position
    for (int j = 0; j < playerPosList->getSize(); j++)
    {
        objPos tempPos;
        playerPosList->getElement(tempPos, j);
        if (tempPos.x == x && tempPos.y == y)
        {
            return false;
        }
    }
    // Additional check for border items
    if (x == 0 || x == 14 || y == 0 || y == 29)
    {
        return false;
    }
    if (x <= 0 || x >= 14 || y <= 1 || y >= 29)
    {
        return false;
    }
    return true;
}

bool FoodBucket::AdvancedPositionValidation(objPosArrayList* playerPosList, int x, int y)
{
    /*
     * This function checks if the food position is the same as the player body
     * if yes, return false
     * if no, return true
     */
    objPos snakeBody;;
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


void FoodBucket::addItemToList(int x, int y, char symbol){
    objPos newPos;
    newPos.setObjPos(x, y, symbol);

    if(foodPositions->getSize() >= listSize){
        foodPositions->removeTail();
    }
    
    foodPositions->insertHead(newPos);
}

objPosArrayList *FoodBucket::getFoodPos(){
    return foodPositions;
}

bool FoodBucket::isFoodEaten(objPosArrayList* playerPosList) {
    if (playerPosList == nullptr || playerPosList->getSize() == 0)
    {
        return false;  // No player position available to check
    }
    objPos playerHeadPos;
    playerPosList->getHeadElement(playerHeadPos);
    for (int i = 0; i < foodPositions->getSize(); ++i)
    {
        objPos temp;
        foodPositions->getElement(temp, i);
        // Check if food is eaten by the Snake head only
        if (temp.x == playerHeadPos.x && temp.y == playerHeadPos.y)
        {
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}

bool FoodBucket::isFoodEatenXY(int x, int y) {
    for (int i = 0; i < foodPositions->getSize(); ++i)
    {
        objPos temp;
        foodPositions->getElement(temp, i);
        // Check if food is eaten by the Snake head only
        if (temp.x == x && temp.y == y)
        {
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}
