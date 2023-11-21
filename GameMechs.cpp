#include "GameMechs.h"
#include <MacUILib.h>

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

    delete[] input;
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


