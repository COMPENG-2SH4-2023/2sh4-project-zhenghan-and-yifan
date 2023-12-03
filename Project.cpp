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

// Global variables
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
    /*
     * This function initializes the game
     */
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
    /**
     * This function gets the input from the user by using GameMechs class
     */
    myGM -> getInput(); // Get the input from the user

}

void RunLogic(void)
{
    /**
     * This function runs the logic of the game
     * It updates the player position and checks if the player collides with itself
     */
    myPlayer->updatePlayerDir();  // Update the player direction
    myPlayer -> playerCollision();  // Check if the player collides with itself
}

void DrawScreen() {
    /**
     * This function draws the screen
     * It prints the player position and the food position
     */
    MacUILib_clearScreen();
    bool draw;

    // Constants for the board dimensions
    const int boardSizeX = myGM->getBoardSizeX();
    const int boardSizeY = myGM->getBoardSizeY();

    // Create a 2D array to represent the screen space
    char screen[boardSizeX][boardSizeY];

    objPosArrayList *playerBody = myPlayer->getPlayerPos(); // Get the player position
    objPos tempBody;  // Temporary objPos to store the player body position

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

    static bool initMap = true; // Initialize the food
 
    bool foodeat = false;  // Flag to Check if the food is eaten
    objPosArrayList *foodPositionList;  // ArrayList to store the food positions
    objPosArrayList *trapPositionList;  // ArrayList to store the trap positions
    //
    objPos tempFoodPos;  // Temporary objPos to store the food position for the loop
    objPos tempTrapPos;  // Temporary objPos to store the trap position for the loop
    objPos tempuserPos;  // Temporary objPos to store the user position for the loop

    if (initMap)  // If the map is not initialized
    {
        SnakeFoodBucket->generateFoods(playerBody);  // Generate the food
        foodPositionList = SnakeFoodBucket->getFoodPos();  // Get the food positions and store them in foodPositionList
        traps->generateTraps(foodPositionList,playerBody);  // Generate the traps
        trapPositionList = traps->getTrapPos();  // Get the trap positions and store them in trapPositionList
        //objPos tempFoodPos;
        //objPos tempTrapPos;
        for (int i = 0; i < 5; i++)
            // Loop through the foodPositionList and trapPositionList and add them to the screen
        {
            foodPositionList->getElement(tempFoodPos,i);  // Get the food position from the ArrayList
            trapPositionList->getElement(tempTrapPos,i);  // Get the trap position from the ArrayList
            screen[tempFoodPos.x][tempFoodPos.y] = tempFoodPos.symbol;  // Add the food position to the screen
            screen[tempTrapPos.x][tempTrapPos.y] = tempTrapPos.symbol;  // Add the trap position to the screen
        }
        initMap = false;  // Set the initMap to false
    }
    else
    {
        playerBody->getHeadElement(tempuserPos);  // Get the user position from the ArrayList
        int userX = tempuserPos.x;  // Get the user x position
        int userY = tempuserPos.y;  // Get the user y position
        foodPositionList = SnakeFoodBucket->getFoodPos();  // Get the food positions and store them in foodPositionList
        trapPositionList = traps->getTrapPos();  // Get the trap positions and store them in trapPositionList

        char eatenChar = SnakeFoodBucket->isFoodEaten(playerBody);  // Check which food is eaten

            switch(eatenChar){
                // different food gives different score and effect
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


