#include "FoodBucket.h"
#include "MacUILib.h"


FoodBucket::FoodBucket()
{
    /**
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
    /**
     * This is a destructor
     */
    delete[] foodPositions;
}

void FoodBucket::randomizeFoodPos(int &x, int &y){
    /**
     * This function generates a single food position
     */
    x = rand() % 15;  //following the instruction of PPA3
    y = rand() % 30;
}

void FoodBucket::generateFoods(objPosArrayList* playerPosList){
    /**
     * This function generates all the food positions
     */
    // Initialize variables
    int x = 0, y = 0;
    int count = 0;
    bool valid, advancedValid;
    while (count < listSize)  // Generate regular food positions
    {
        randomizeFoodPos(x, y);  // Generate random food position
        valid = positionValidation(foodPositions, playerPosList, x, y);  // Check if the food position is valid
        advancedValid = AdvancedPositionValidation(playerPosList, x, y);
        if (valid && advancedValid)  // If the food position is valid
        {
            addItemToList(x, y, foodSymbol);  // Add the food position to the food position list
            count++; // Increment the count
        }
    }
    while (count < PossFoodCount + listSize) // Generate advanced food positions
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
    while (count < totalFoodCount)  // Generate advanced food positions
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
    /**
     * This function checks if the food position is valid or not by our requirements
     * if yes, return false
     * if no, return true
     */
    objPos tempFood;
    objPos tempPos;
    for (int j = 0; j < list->getSize(); j++)
    // Check if the food position is the same as the previous food position
    {
        //objPos tempFood;
        list->getElement(tempFood, j); // Get the food position from the ArrayList
        if ((tempFood.x == x && tempFood.y == y))  // If the food position is the same as the previous food position
        {
            return false;  // Return false
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
    /**
     * This function checks if the food position is the same as the player body
     * if yes, return false
     * if no, return true
     */
    objPos snakeBody; // Temporary objPos to store the player body
    for (int j = 0; j < playerPosList->getSize(); j++)
    {
        playerPosList->getElement(snakeBody, j);  // Get the player body from the ArrayList
        if ((snakeBody.x == x && snakeBody.y == y))  // If the food position is the same as the one of the index of player body
        {
            return false;
        }
    }
    return true;
}


void FoodBucket::addItemToList(int x, int y, char symbol){
    /**
     * This function adds a food position to the food position list
     */
    objPos newPos;  // Temporary objPos to store the new food position
    newPos.setObjPos(x, y, symbol);  // Initialize the new food position

    if(foodPositions->getSize() >= listSize){
        foodPositions->removeTail();  // Remove the last food position from the ArrayList
    }
    
    foodPositions->insertHead(newPos);  // Insert the new food position to the ArrayList
}

objPosArrayList *FoodBucket::getFoodPos(){
    /**
     * This function returns the food position list
     */
    return foodPositions;
}

char FoodBucket::isFoodEaten(objPosArrayList* playerPosList) {
    /**
     * This function checks if the food is eaten by the Snake head
     */
     //if(collide == 'N') => score+=5
    //else if(collide == 'P') => score += 10
    //GameMechs *tempGM;
    //Player* tempPlayer;
    objPos playerHeadPos;  // Temporary objPos to store the player head position
    objPos temp;  // Temporary objPos to store the food position
    if (playerPosList == nullptr || playerPosList->getSize() == 0)
    {
        return 0;  // No player position available to check
    }
    
    playerPosList->getHeadElement(playerHeadPos);  // Get the player head position from the ArrayList
    for (int i = 0; i < foodPositions->getSize(); ++i)
    {
        
        foodPositions->getElement(temp, i);  // Get the food position from the ArrayList
        // Check if food is eaten by the Snake head only, if yes, return the eaten food symbol
        if (temp.x == playerHeadPos.x && temp.y == playerHeadPos.y)
        {
            return temp.symbol;
        }
    }
    return 0;  // No food eaten
}

bool FoodBucket::isFoodEatenXY(int x, int y) {
    /**
     * This function checks if the food is eaten by the Snake head but using x and y
     * Another version of isFoodEaten()
     */
    objPos temp;
    
    for (int i = 0; i < foodPositions->getSize(); i++)
    {
        
        foodPositions->getElement(temp, i);
        // Check if food is eaten by the Snake head only
        if (temp.x == x && temp.y == y)
        {
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}
