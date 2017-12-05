#include "studentLabyrint1.h"

bool didFillPathToGoal(IMaze *pMaze, int r, int k){


    if(pMaze->isWall(r,k))
        return false;
    else if(pMaze->isGoal(r,k))
    {
        pMaze->placeStone(r,k);
        return true;
    }
    else
    {
        pMaze->placeStone(r,k);

        if( didFillPathToGoal(pMaze, r+1,k) || didFillPathToGoal(pMaze, r-1,k)
         || didFillPathToGoal(pMaze, r,k+1) || didFillPathToGoal(pMaze, r,k-1))
        {
            pMaze->placeStone(r,k);
            return true;
        }
    }
    return false;
}


