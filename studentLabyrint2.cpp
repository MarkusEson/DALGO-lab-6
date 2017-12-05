#include "studentLabyrint2.h"
#include "rk.h"
#include "assert.h"
#include <vector>
#include <deque>

using namespace std;


RK rkOfNeighbor(RK rk, int ixOfneighbor){
    switch (ixOfneighbor){
    case 0 : return RK( rk._r,    rk._k +1);
    case 1 : return RK( rk._r,    rk._k -1);
    case 2 : return RK( rk._r +1, rk._k);
    case 3 : return RK( rk._r -1, rk._k);
    }
    assert( false );
    return RK();
}



bool didFillPathToGoalFIFO(IMaze *pMaze, int r, int k){

    vector< vector<RK> > rkPrevious( pMaze->sizeR(), vector<RK>(pMaze->sizeK(), RK()));
    deque<RK> fifo;

    fifo.push_back(RK(r,k));

    while(!fifo.empty())
    {

        RK frontRK = fifo.front();      // skapa frontRK

        if(pMaze->isWall(frontRK._r, frontRK._k) || !pMaze->isInside(frontRK._r, frontRK._k) || pMaze->hasStone(frontRK._r,frontRK._k))
            fifo.pop_front();   // om det är en vägg, eller om den inte är inne, eller om den redan har en sten så poppar vi.
        else
        {
            // LETA OSS GENOM LABYRINTEN
            pMaze->placeStone(frontRK._r,frontRK._k);       // annars placerar vi ens ten och sen kollar vi om vi står på målet.
            for(int i = 0; i < 4; i++)  // pusha nya kordinater
            {
                RK neighborRK = rkOfNeighbor(frontRK, i);   // skapa RK för grannarna

                if(!pMaze->hasStone(neighborRK._r, neighborRK._k))  // om grannen EJ har ens ten så pushar vi dem, detta för att vi inte ska lägga sten där det ligger redan
                {
                    fifo.push_back(neighborRK);
                    rkPrevious[neighborRK._r][neighborRK._k] = frontRK;
                }
            }


            // OM VI HITTADE MÅLET
            if(pMaze->isGoal(frontRK._r, frontRK._k))       // om vi är på målet skapar vi RK tillbakavägen för att hitta till start.
            {
                RK returnRK = frontRK;      // skapa returnRK för vägen tillbaka

                while(r != returnRK._r || k != returnRK._k)
                { // när r eller k skiljer sig från värdena i returnRK så placerar vi röd markering

                    pMaze->indicateThatRKIsOnPath(returnRK._r, returnRK._k);
                    returnRK = rkPrevious[returnRK._r][returnRK._k];
                }
                return true;
            }

            fifo.pop_front(); // sist poppar vi fronten
        }
    }
    return false;
}
