#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "FoodBucket.h"
#include "SnakeTrap.h"
#include <cstdlib>  // For rand, srand
#include <ctime>    // For time


using namespace std;

#define DELAY_CONST 300000


bool exitFlag;

GameMechs* myGM;
Player* myPlayer;
//Food *SnakeFood;
FoodBucket *SnakeFoodBucket;
SnakeTrap *traps;
//SnakeTrap *TrapsList;

struct objPos myPos;
int count = 0;
int stageFlag = 0;



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
    myGM = new GameMechs(15, 30);
    myPlayer = new Player(myGM);
    //SnakeFood = new Food();
    SnakeFoodBucket = new FoodBucket();
    stageFlag = 0;
    traps = new SnakeTrap();
    //exitFlag = false;

}

void GetInput(void)
{
    myGM -> getInput();

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer -> playerCollision();
}

void DrawScreen() {
    MacUILib_clearScreen();
    bool draw;

    // Constants for the board dimensions
    const int boardSizeX = myGM->getBoardSizeX();
    const int boardSizeY = myGM->getBoardSizeY();

    // Create a 2D array to represent the screen space
    char screen[boardSizeX][boardSizeY];

    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    // Build the screen layout
    for (int x = 0; x < myGM->getBoardSizeX(); x++)
    {
        for (int y = 0; y < myGM->getBoardSizeY(); y++)
        {
            // Place borders with '#' and empty spaces with ' '
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                draw = false;
                playerBody->getElement(tempBody,k);
                if(tempBody.x == x && tempBody.y == y)
                {
                    screen[x][y]=tempBody.symbol;
                    draw = true;
                    break;
                }
            }

            if(draw) continue;

            else if (x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY() - 1)
            {
                screen[x][y] = '#';
                //MacUILib_printf("%c",'#');
            }
            else
            {
                screen[x][y] = ' ';
                //MacUILib_printf("%c",' ');
            }
        }
    }

    static bool initMap = true;
 
    bool foodeat = false;
    objPosArrayList *foodPositionList;
    objPosArrayList *trapPositionList;
    //
    objPos tempFoodPos;
    objPos tempTrapPos;
    objPos tempuserPos;

    if (initMap)
    {
        SnakeFoodBucket->generateFoods(playerBody);
        foodPositionList = SnakeFoodBucket->getFoodPos();
        traps->generateTraps(foodPositionList,playerBody);
        trapPositionList = traps->getTrapPos();
        //objPos tempFoodPos;
        //objPos tempTrapPos;
        for (int i = 0; i < 5; i++)
        {
            foodPositionList->getElement(tempFoodPos,i);
            trapPositionList->getElement(tempTrapPos,i);
            screen[tempFoodPos.x][tempFoodPos.y] = tempFoodPos.symbol;
            screen[tempTrapPos.x][tempTrapPos.y] = tempTrapPos.symbol;
        }
        initMap = false;
    }
    else
    {
        //objPos tempuserPos;
        playerBody->getHeadElement(tempuserPos);
        int userX = tempuserPos.x;
        int userY = tempuserPos.y;
        foodPositionList = SnakeFoodBucket->getFoodPos();
        trapPositionList = traps->getTrapPos();

        char eatenChar = SnakeFoodBucket->isFoodEaten(playerBody);

            switch(eatenChar){

                case 'N':
                    for(int i = 0; i<5; i++){
                        myGM->incrementScore();
                    }

                    break;
                
                case 'P':
                    for(int i = 0; i<10; i++){
                        myGM->incrementScore();
                    }

                    for(int i = 0; i<2; i++){
                        myPlayer->increasePlayerLength();
                    }

                    break;
                
                case 'O':

                    myGM->incrementScore();
                
                    myPlayer->increasePlayerLength();

                    break;


            }
        // Check if food is eaten
        if (SnakeFoodBucket->isFoodEatenXY(userX, userY))
        {
            //objPos tempFoodPos;
            //objPos tempTrapPos;
            //if food is eaten, generate new food
            SnakeFoodBucket->generateFoods(playerBody);
            foodPositionList = SnakeFoodBucket->getFoodPos(); // Update food positions array
             
            traps->generateTraps(foodPositionList,playerBody);         

            initMap = false;

            for (int i = 0; i < 5; i++)
            {
                foodPositionList->getElement(tempFoodPos,i);
                trapPositionList->getElement(tempTrapPos,i);
                screen[tempFoodPos.x][tempFoodPos.y] = tempFoodPos.symbol;
                screen[tempTrapPos.x][tempTrapPos.y] = tempTrapPos.symbol;

            }
        }
        // Check if trap is triggered
        if (traps->isTrapTriggeredXY(userX, userY))
        {
            //set the exit flag to true
            myGM->setExitTrue();
        }
        //

        //objPos tempFoodPos;
        //objPos tempTrapPos;
        for (int i = 0; i < 5; i++)
        {
            foodPositionList->getElement(tempFoodPos,i);
            trapPositionList->getElement(tempTrapPos,i);
            screen[tempFoodPos.x][tempFoodPos.y] = tempFoodPos.symbol;
            screen[tempTrapPos.x][tempTrapPos.y] = tempTrapPos.symbol;
        }
    }
    
    // Print the screen
    for (int x = 0; x < boardSizeX; x++)
    {
        for (int y = 0; y < boardSizeY; y++)
        {
            MacUILib_printf("%c", screen[x][y]);
        }
        MacUILib_printf("\n");
    }

    /////////////////////////////Debuging Info/////////////////////////////////////
    MacUILib_printf("Score: %d\n", myGM->getScore());
    objPos playerHeadPos;
    playerBody->getHeadElement(playerHeadPos);
    MacUILib_printf("Player Head: (%d, %d)\n", playerHeadPos.x, playerHeadPos.y);
    //print out food position
    //objPos tempFoodPos;
    for (int i = 0; i < 5; i++)
    {
        foodPositionList->getElement(tempFoodPos,i);
        MacUILib_printf("Food %d: (%d, %d)\n", i, tempFoodPos.x, tempFoodPos.y);
        MacUILib_printf("Eaten: %d\n", foodeat);
    }
    //Print out the food positin length
    MacUILib_printf("Food Position List Length: %d\n", foodPositionList->getSize());
    /////////////////////////////Debuging Info/////////////////////////////////////
    
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


