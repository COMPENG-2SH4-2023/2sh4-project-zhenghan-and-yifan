#include "GameMechs.h"
#include "MacUILib.h"

void AddItemToList(objPos *pPos, int count, int x, int y, char symbol);

GameMechs::GameMechs()
{
    /**
     * This is a constructor
     * We will initialize all the  data members here
     */
    input = 0;
    exitFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    /**
     * This is a constructor
     * We will initialize all the  data members here
     */

    input = 0;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    /*
    * This is a destructor
    */


}

bool GameMechs::getExitFlagStatus()
{
    /*
    * This function returns the exitFlag status
    */
    return exitFlag;
}

char GameMechs::getInput()
{
    /*
    * This function returns the input
    */

    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    /*
    * This function returns the boardSizeX
    */
    return boardSizeX;

}

int GameMechs::getBoardSizeY()
{
    /*
    * This function returns the boardSizeY
    */
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    /*
    * This function sets the exitFlag to true
    */
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    /*
    * This function sets the input
    */
    input = this_input;

}

void GameMechs::clearInput()
{
    /*
    * This function clears the input
    */
    input = 0;

}

int GameMechs::incrementScore()
{
    /*
    * This function increments the score
    */
    // use bool isFoodEaten() to check if food is eaten
    score++;
    return score;
}

int GameMechs::getScore()
{
    /*
    * This function returns the score
    */
    return score;
}

Food::Food()
{
    /*
    * This is a constructor
    * We will initialize all the  data members here
    */
    srand(time(NULL));
    // Arrange 5 food items on the board
    FoodPos = new objPos[5];
    listSize = 5;
    foodSymbol = 'O';

}


Food::~Food()
{
    /*
    * This is a destructor
    */
}


void Food::randomizeFoodPos(int &x, int &y){
    x = rand() % 10;  //following the instruction of PPA3
    y = rand() % 20;
}

bool Food::PositionValidation(const struct objPos list[],const struct objPos *playerPos, int count, int x, int y){
    for (int j = 0; j < count; j++)
    // Check if the food position is the same as the previous food position
    {
        if ((list[j].x == x && list[j].y == y))
        {
            return false;
        }
    }
    // Check if the food position is the same as the player position
    if (playerPos->x == x && playerPos->y == y)
    {
        return false;
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

void Food::generateFood(const objPos& playerPos)
{
    /*
    * This function generates the food position
    */
    int x = 0, y = 0;
    int count = 0;
    bool valid;
    while (count < listSize)
    {
        randomizeFoodPos(x, y);
        valid = PositionValidation(FoodPos, &playerPos, count, x, y);
        if (valid)
        {
            AddItemToList(FoodPos, count, x, y);
            count++;
        }
    }

}

void Food::AddItemToList(struct objPos list[], int count, int x, int y){
    list[count].x = x;
    list[count].y = y;
    list[count].symbol = foodSymbol;
}

void Food::getFoodPos(objPos (&returnPos)[5])
{
    /*
    * This function returns the food position
    */
    for (int i = 0; i < 5; i++)
    {
        returnPos[i].x = FoodPos[i].x;
        returnPos[i].y = FoodPos[i].y;
        returnPos[i].symbol = FoodPos[i].symbol;
    }
}

bool Food::isFoodEaten(const objPos& playerPos) {
    for (int i = 0; i < listSize; ++i) {
        if (FoodPos[i].x == playerPos.x && FoodPos[i].y == playerPos.y) {
            return true;  // Food is eaten
        }
    }
    return false;  // No food eaten
}

FoodBucket::FoodBucket()
{
    /*
    * This is a constructor
    * We will initialize all the  data members here
    */
    srand(time(NULL));
    listSize = 5; // 5 food items
    foodSymbol = 'O'; // Regular Food symbol
    advancedFoodSymbol = 'X';  // Advanced Food symbol
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
    x = rand() % 10;  //following the instruction of PPA3
    y = rand() % 20;
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

           
            
            addItemToList(x, y);

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


void FoodBucket::addItemToList(int x, int y){
    objPos newPos;
    newPos.setObjPos(x, y, foodSymbol);

    if(foodPositions->getSize() >= 5){
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
