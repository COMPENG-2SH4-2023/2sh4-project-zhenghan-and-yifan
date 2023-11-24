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

    void collisionCheck(int boardSizeX, int boardSizeY, struct objPos playerPosition, struct objPos itemBin[]);
    void randomlize(int xRange, int yRange, int *x, int *y, char *symbol);
    int PositionValidation(const struct objPos list[],const struct objPos *playerPos, int count, int x, int y, char symbol);
    void AddItemToList(struct objPos list[], int count, int x, int y, char symbol);
    void populateItemBin(objPos *list, int listSize, struct objPos itemBin[]);
    void GenerateItems(objPos *list, const int listSize, const objPos *playerPos, const int xRange, const int yRange, struct objPos *itemBin);
};

#endif