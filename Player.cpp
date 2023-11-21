#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                        mainGameMechsRef->getBoardSizeY()/2,
                        '@');
}


Player::~Player()
{
    // delete any heap members here
    //no heap member yet...
    //leave it empty for now...
}

void Player::getPlayerPos(objPos &returnPos)
{

    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);    
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    // where do I get the input
    //how to check te input

    //1.not by calling MacUILib.getChar
    //2.coordinate with the team mate who is designing the game mechanism class
    //3.There will be a method in GameMechanism Class that collectively check the input and store the most recent nput
    //     just need to figure out how to het to it
    //4.how it lies in the game mechanism reference inside your private method
    char input = mainGameMechsRef->getInput();
    switch(input){
        case 'w':
            if(myDir != UP && myDir != DOWN){
                myDir = UP;
            }
            break;

        case 'a':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = LEFT;
            }
            break;

        case 's':
            if(myDir != UP && myDir != DOWN){
                myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }        
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    //get the board size managed by GameMech
    
    if (playerPos.x < 1) {
            playerPos.x  = mainGameMechsRef->getBoardSizeX() - 2;
    } 

    else if (playerPos.x  >= mainGameMechsRef->getBoardSizeX()-1) {
        playerPos.x  = 1;
    }

    if (playerPos.y < 1) {
            playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    } 
    else if (playerPos.y >= mainGameMechsRef->getBoardSizeY()-1) {
            playerPos.y = 1;
        
    }
    
}

