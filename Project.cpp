#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

GameMechs* myGM;
Player* myPlayer;

objPos myPos;


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

void DrawScreen(void)
{
    MacUILib_clearScreen();

    char space[myGM->getBoardSizeX()-1][myGM->getBoardSizeY()-1];   

    
    
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);  
    
    for(int i = 0; i<myGM->getBoardSizeX(); i++){
        for(int j = 0; j < myGM->getBoardSizeY(); j++){
            if(((i == myGM->getBoardSizeX()-1) || (i == 0)) || ((j == myGM->getBoardSizeY()-1) || (j == 0))){

                space[i][j] = '#';

            }

            else{
                space[i][j] = ' ';
            }
        }

    }

    space[tempPos.x][tempPos.y] = tempPos.symbol;

    for (int i = 0; i < myGM->getBoardSizeX(); i++) {
        for (int j = 0; j < myGM->getBoardSizeY(); j++) {
            MacUILib_printf("%c", space[i][j]);
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
