

// Implements the mapping functionality for picking.

#pragma once
#include "colour.h"
#include "material.h"
#include <vector>



namespace pickSys
{
    using std::vector;



    class pickMapper
    {
      private:
        struct mapping {
            colour col;
            int    ind;
        };


      private:
        vector<mapping> core; // Maps colours to indeces and vice versa

        bool rangeCompare( const colour& a, const colour& b, float epsilon );


      public:
        void   add   ( const colour& refCol, int linkedIndex );
        int    getInd( const colour& refCol );
        colour getCol( const int&    refInd );
    };
};