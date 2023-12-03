#include "Player.h"
#define ESC_KEY 27
// WASD uppercase
#define UP_KEY_W 87
#define DOWN_KEY_S 83
#define LEFT_KEY_A 65
#define RIGHT_KEY_D 68
// WASD lowercase
#define UP_KEY_w 119
#define DOWN_KEY_s 115
#define LEFT_KEY_a 97
#define RIGHT_KEY_d 100
// number Keys
#define KEY_1 49
// tab key
#define TAB_KEY 9
// F1 key
#define SHIFT_KEY 16

Player::Player(GameMechs* thisGMRef)
{
    /**
     * This is a constructor
     * We will initialize all the  data members here
     */
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    //objPos playerPos;
    objPos tempPos;
    // more actions to be included
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                        mainGameMechsRef->getBoardSizeY()/2,
                        '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    // debug only
    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);
    //playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    /**
     * This is a destructor
     */
    // delete any heap members here
    //no heap member yet...
    //leave it empty for now...
    delete playerPosList;
}


objPosArrayList *Player::getPlayerPos()
{
    /**
     * This function returns the player position
     */
    // return playerPos by pass by reference
    return playerPosList;
}

/*
void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}
*/

void Player::updatePlayerDir()
{
    /**
     * This function updates the player direction based on the input
     * Logic is based on the Finite State Machine from previous PPA3
     */
    // PPA3 input processing logic
    // where do I get the input
    //how to check te input

    //1.not by calling MacUILib.getChar
    //2.coordinate with the team mate who is designing the game mechanism class
    //3.There will be a method in GameMechanism Class that collectively check the input and store the most recent nput
    //     just need to figure out how to het to it
    //4.how it lies in the game mechanism reference inside your private method
    char input = mainGameMechsRef->getInput();
    switch (input) {
        case ESC_KEY:
            mainGameMechsRef->setExitTrue();
            break;
        case UP_KEY_W:
        case UP_KEY_w:
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP) {
                myDir = UP;
            }
            break;
        case DOWN_KEY_S:
        case DOWN_KEY_s:
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP) {
                myDir = DOWN;
            }
            break;
        case LEFT_KEY_A:
        case LEFT_KEY_a:
            if (myDir == UP || myDir == DOWN || myDir == STOP) {
                myDir = LEFT;
            }
        case RIGHT_KEY_D:
        case RIGHT_KEY_d:
            if (myDir == UP || myDir == DOWN || myDir == STOP ) {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
    movePlayer();
}



void Player::movePlayer()
{
    /**
     * This function move the player position based on the direction
     * Logic is based on the Finite State Machine from previous PPA3
     */
    // PPA3 Finite State Machine logic
    //get the board size managed by GameMech

    //check input is valid
    //if valid, update the player position
    //if not valid, do nothing
    objPos currentHead; //Initialise the currentHead for holding the current position
    playerPosList->getHeadElement(currentHead);
    if (mainGameMechsRef->getInput() != 0)
    {
        if (mainGameMechsRef->getInput() == ESC_KEY)
        {
            mainGameMechsRef->setExitTrue();
        }
        switch (myDir) {
            case UP:
                currentHead.x--;
                break;
            case DOWN:
                currentHead.x++;
                break;
            case LEFT:
                currentHead.y--;
                break;
            case RIGHT:
                currentHead.y++;
                break;
            default:
                break;
        }
        //wrap around
        if (currentHead.x > mainGameMechsRef->getBoardSizeX() - 2)
        {
            currentHead.x = 1;
        }
        else if (currentHead.x < 1)
        {
            currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        if (currentHead.y > mainGameMechsRef->getBoardSizeY() - 2)
        {
            currentHead.y = 1;
        }
        else if (currentHead.y < 1)
        {
            currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
    }
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}

void Player::increasePlayerLength()
{
    /**
     * This function increases the player length by 1
     */
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    objPos newHead;
    switch (myDir) {
        case UP:
            newHead.setObjPos(currentHead.x - 1, currentHead.y, '*');
            break;
        case DOWN:
            newHead.setObjPos(currentHead.x + 1, currentHead.y, '*');
            break;
        case LEFT:
            newHead.setObjPos(currentHead.x, currentHead.y - 1, '*');
            break;
        case RIGHT:
            newHead.setObjPos(currentHead.x, currentHead.y + 1, '*');
            break;
        default:
            break;
    }
    playerPosList->insertHead(newHead);
}



void Player::playerCollision()
{
    /**
     * This function checks if the player collides with itself
     * if yes, set the exitFlag to true
     */
    objPos temp;
    objPos tempHead;
    playerPosList->getHeadElement(tempHead);
    int counter;

    if(playerPosList->getSize()>2){

        for(counter = 1; counter<playerPosList->getSize();counter++){

            playerPosList->getElement(temp,counter);
            
            if(temp.x == tempHead.x && temp.y == tempHead.y){
                mainGameMechsRef->setExitTrue();
                break;
            }

        }

    }

}
