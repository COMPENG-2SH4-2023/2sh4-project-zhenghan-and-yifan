#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include <cstdlib>  // For rand, srand
#include <ctime>    // For time


using namespace std;

#define DELAY_CONST 100000


bool exitFlag;

GameMechs* myGM;
Player* myPlayer;

struct objPos myPos;
objPos* itemBin;


//char space[myGM->getBoardSizeX()-1][myGM->getBoardSizeX()-1];

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    myGM = new GameMechs(10, 20);
    myPlayer = new Player(myGM);
    itemBin = new objPos[5];

    //exitFlag = false;

}

void GetInput(void)
{
    myGM -> getInput();

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}




void DrawScreen() {
    MacUILib_clearScreen();

    // Constants for the board dimensions
    const int boardSizeX = myGM->getBoardSizeX();
    const int boardSizeY = myGM->getBoardSizeY();

    // Create a 2D array to represent the screen space
    char screen[boardSizeX][boardSizeY];

    // Get the player's position
    struct objPos playerPosition;
    myPlayer->getPlayerPos(playerPosition);

    // Build the screen layout
    for (int x = 0; x < boardSizeX; x++) {
        for (int y = 0; y < boardSizeY; y++) {
            // Place borders with '#' and empty spaces with ' '
            if (x == 0 || x == boardSizeX - 1 || y == 0 || y == boardSizeY - 1) {
                screen[x][y] = '#';
            } else {
                screen[x][y] = ' ';
            }
        }
    }

    // Place the player's symbol on the screen
    screen[playerPosition.x][playerPosition.y] = playerPosition.symbol;
    myGM->collisionCheck(boardSizeX, boardSizeY, playerPosition, itemBin);


    // Place item symbols on the screen
    for (int i = 0; i < 5; i++) {
        screen[itemBin[i].x][itemBin[i].y] = itemBin[i].symbol;
    }

    // Print the screen
    for (int x = 0; x < boardSizeX; x++) {
        for (int y = 0; y < boardSizeY; y++) {
            MacUILib_printf("%c", screen[x][y]);
        }
        MacUILib_printf("\n");
    }

}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();
}


