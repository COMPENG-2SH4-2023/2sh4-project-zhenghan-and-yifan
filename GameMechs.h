#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

private:
    char input;
    bool exitFlag;
    bool looseFlag;
    int score;

    int boardSizeX;
    int boardSizeY;

public:
    GameMechs();
    GameMechs(int boardX, int boardY);
    ~GameMechs();

    bool getExitFlagStatus();
    void setExitTrue();

    char getInput();
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX();
    int getBoardSizeY();

    int incrementScore();
    int getScore();

};

class Food{
private:
    objPos *FoodPos;
    int listSize;
    char foodSymbol;

public:
    Food();
    ~Food();
    void randomizeFoodPos(int &x, int &y);
    bool PositionValidation(const struct objPos list[], const struct objPos *playerPos, int count, int x, int y);
    void AddItemToList(struct objPos list[], int count, int x, int y);
    void generateFood(const objPos& playerPos);
    void getFoodPos(objPos (&returnPos)[5]);
    bool isFoodEaten(const objPos& playerPos);
};

class FoodBucket{
    //ArrayList Design
private:
    objPosArrayList* foodPositions; // Dynamic array for food positions
    int listSize;
    char foodSymbol;

public:
    FoodBucket();
    ~FoodBucket();
    void randomizeFoodPos(int &x, int &y);
    bool positionValidation(objPosArrayList *list, objPosArrayList* playerPosList, int x, int y);
    void addItemToList(int x, int y);
    void generateFoods(objPosArrayList* playerPosList);
    void getFoodPos(objPos (&returnPos)[5]);
    bool isFoodEaten(objPosArrayList* playerPosList);
};


#endif