#ifndef FOODBUCKET_H
#define FOODBUCKET_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

#include "objPos.h"
#include "Player.h"


using namespace std;




class FoodBucket{
    //ArrayList Design
private:
    objPosArrayList* foodPositions; // Dynamic array for food positions
    int listSize;
    int PossFoodCount;
    int NegFoodCount;
    int totalFoodCount;
    char foodSymbol;
    char PositiveFoodSymbol;
    char NegativeFoodSymbol;

public:
    FoodBucket();
    ~FoodBucket();
    void randomizeFoodPos(int &x, int &y);
    bool positionValidation(objPosArrayList *list, objPosArrayList* playerPosList, int x, int y);
    bool AdvancedPositionValidation(objPosArrayList* playerPosList, int x, int y);
    void addItemToList(int x, int y, char symbol);
    void generateFoods(objPosArrayList* playerPosList);
    objPosArrayList *getFoodPos();
    char isFoodEaten(objPosArrayList* playerPosList);
    bool isFoodEatenXY(int x, int y);
};

#endif