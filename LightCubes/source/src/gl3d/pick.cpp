

#include "pick.h"
#include <cassert>



namespace pickSys
{
    bool pickMapper :: rangeCompare( const colour& a, const colour& b, float epsilon ) {
        return ((abs(a.r - b.r) <= epsilon)
             && (abs(a.g - b.g) <= epsilon)
             && (abs(a.b - b.b) <= epsilon)
             && (abs(a.a - b.a) <= epsilon));
    }



    void pickMapper :: add( const colour& col, int linkedIndex ) {
        mapping m = { col, linkedIndex };
        core.push_back( m );
    }



    int pickMapper :: getInd( const colour& refCol ) {
        for (size_t i=0; i<core.size(); i++) {
            const colour& comCol  = core[i].col;
            const int&    index   = core[i].ind;
            const float   epsilon = 1.0f / 256.0f;

            if (rangeCompare( refCol, comCol, epsilon ))
                return index;
        }

        return -1; // Failed
    }



    colour pickMapper :: getCol( const int& refInd ) {
        for (size_t i=0; i<core.size(); i++) {
            const colour& col   = core[i].col;
            const int&    index = core[i].ind;

            if (index == refInd)
                return col;
        }

        return colour(0,0,0,0); // Failed
    }
};