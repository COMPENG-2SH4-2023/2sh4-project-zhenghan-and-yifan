#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// temp usage, ask before use.
#include <stdexcept> // for std::out_of_range exception
#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    /**
     * This is a constructor
     * We will initialize all the  data members here
     */

    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    for (int i = 0; i < ARRAY_MAX_CAP; i++)
    {
        aList[i].x = 0;
        aList[i].y = 0;
        aList[i].symbol = '\0';
    }
}

objPosArrayList::~objPosArrayList()
{
    /**
     * This is a destructor
     * We will deallocate all the dynamic memory here
     */
    delete[] aList;
}

int objPosArrayList::getSize()
{
    /**
     * This function returns the size of the array list
     */
    return sizeList;

}

void objPosArrayList::insertHead(objPos thisPos)
{
    /**
     * This function inserts an element at the head of the array list
     */
    if (sizeList == sizeArray)
    {  // Error handling
        throw std::out_of_range("List is now fully full.");
    }
    else
    {
        for (int i = sizeList; i > 0; i--)  // shift all elements to the right
        {
            aList[i] = aList[i-1];
        }
        aList[0] = thisPos; // insert new element at the head
        sizeList++; // increment size by 1
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    /**
     * This function inserts an element at the tail of the array list
     */
    if (sizeList == sizeArray)
    {  // Error handling
        throw std::out_of_range("List is now fully full."); //[TODO]
    }
    else
    {
        aList[sizeList] = thisPos; // insert new element at the tail
        sizeList++; // increment size by 1
    }
}

void objPosArrayList::removeHead()
{
    /**
     * This function removes an element at the head of the array list
     */
    if (sizeList == 0)
    {  // Error handling
        throw std::out_of_range("List is now fully empty.");//[TODO]
    }
    else
    {
        for (int i = 0; i < sizeList; i++)  // shift all elements to the left
        {
            aList[i] = aList[i+1];
        }
        sizeList--; // decrement size by 1
    }
}

void objPosArrayList::removeTail()
{
    /**
     * This function removes an element at the tail of the array list
     */
    if (sizeList == 0)
    {  // Error handling
        throw std::out_of_range("List is now fully empty.");//[TODO]
    }
    else
    {

        sizeList--; // decrement size by 1
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    /**
     * This function returns the element at the head of the array list
     */
    if (sizeList == 0)
    {  // Error handling
        throw std::out_of_range("List is empty.");//[TODO]
    }
    else
    {
        returnPos = aList[0];
    }

}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    /**
     * This function returns the element at the tail of the array list
     */
    if (sizeList == 0)
    {  // Error handling
        throw std::out_of_range("List is empty.");//[TODO]
    }
    else
    {
        returnPos = aList[sizeList-1];
    }

}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    /**
     * This function returns the element at the index of the array list
     */
    if (index < 0 || index >= sizeArray)
    {  // Error handling
        throw std::out_of_range("Invalid index.");
    }
    else
    {
        returnPos = aList[index];
    }
}