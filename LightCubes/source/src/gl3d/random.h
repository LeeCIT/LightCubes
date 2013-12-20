

// Pseudo-random number generation.

#pragma once
#include <cstdint>



// General purpose functions which use a single static RNG.
float random();                   // Range (0,1]
float random( float x );          // Range (0,x]
float random( float a, float b ); // Range (a,b]
bool  chance( float n );          // Returns true with probability 1/n, uniformly distributed



namespace prng
{
    class rngFloat
    {
       private:
         typedef uint32_t uint32;
       
         uint32 seed;
         union {// Overlap values in memory
             float  cfloat;
             uint32 cuint32;
         };
         
       
       public:
         float random();
       
         rngFloat( uint32 seed );
         rngFloat();
        ~rngFloat();
    };
};