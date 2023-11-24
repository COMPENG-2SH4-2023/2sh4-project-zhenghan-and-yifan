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

void GameMechs::GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, struct objPos *itemBin)
{
    srand(time(NULL));
    int x, y;
    char symbol;
    int valid = 0;
    int count = 0;

    while (count < listSize)
    {
        randomlize(xRange, yRange, &x, &y, &symbol);
        valid = PositionValidation(list, playerPos, count, x, y, symbol);
        if (valid)
        {
            AddItemToList(list, count, x, y, symbol);
            count++;
        }
    }
    populateItemBin(list, listSize, itemBin);
}

void GameMechs::collisionCheck(int boardSizeX, int boardSizeY, struct objPos playerPosition, struct objPos itemBin[])
{
    /*
     * This function checks if the player has collided with an item
     * If a collision is detected, it calls GenerateItems to generate new items
     */
    static bool firstRun = true;
    if (firstRun) {
        GenerateItems(itemBin, 5, &playerPosition, boardSizeX, boardSizeY, itemBin);
        firstRun = false;
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (playerPosition.x == itemBin[i].x && playerPosition.y == itemBin[i].y)
            {
                GenerateItems(itemBin, 5, &playerPosition, boardSizeX, boardSizeY, itemBin);
                break;
            }
        }
    }
}

void GameMechs::randomlize(int xRange, int yRange, int *x, int *y, char *symbol){
    *x = rand() % xRange;  //following the instruction of PPA3
    *y = rand() % yRange;
    *symbol = (rand() % (126 - 33 + 1)) + 33;
}

int GameMechs::PositionValidation(const struct objPos list[],const struct objPos *playerPos, int count, int x, int y, char symbol){
    for (int j = 0; j < count; j++)
    {
        if ((list[j].x == x && list[j].y == y) || (list[j].symbol == symbol))
            return 0;
    }
    if (playerPos->x == x && playerPos->y == y)
        return 0;
    // Additional check for border items
    if (y == 0 || y == 19 || x == 0 || x == 9)
        return 0;
    return 1;
}

void GameMechs::AddItemToList(struct objPos list[], int count, int x, int y, char symbol){
    list[count].x = x;
    list[count].y = y;
    list[count].symbol = symbol;
}

void GameMechs::populateItemBin(objPos *list, int listSize, struct objPos *itemBin) {
    for (int i = 0; i < listSize; i++)
    {
        itemBin[i].x = list[i].x;
        itemBin[i].y = list[i].y;
        itemBin[i].symbol = list[i].symbol;
    }
}
