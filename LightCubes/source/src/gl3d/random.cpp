

#include "random.h"
#include "func.h"
#include <cmath>
#include <ctime>



// Range (0,1]  (0 inclusive, 1 exclusive)
// All random functions build upon this one.
float random() {
    static prng::rngFloat basisRng;
    return basisRng.random();
}



// Range [0,x]
float random( float x ) {
    return random() * x;
}



// Range (a,b]
float random( float a, float b ) {
    return lerp( a, b, random() );
}



// Returns true with probability 1/n, uniformly distributed.
bool chance( float n ) {
    return (0.0f == floor( random(n) ));
}





namespace prng
{
    // Return random float between 0 and 1, exclusive of 1.
    // There are 23 bits of randomness.  2^23 variations.
    float rngFloat::random() {
        // How it works:
        // mul:   Changes all the bits of the integer, eventually, without ever becoming zero.
        // shift: Shifting right by 9 sets the left 9 bits to zero for the OR.
        // or:    Combines 1.0f with the random mantissa from the seed.
        // sub:   The float has the range (1-2] because there is an implicit 1 in the IEEE-754 mantissa.
        //        This is reduced to (0-1] for mathematical convenience.

        const uint32 mulprime = 16807;      // Prime number for mul-add accumulate
        const uint32 onef     = 0x3F800000; // 1.0f in hex
        const uint32 shift    = 8 + 1;      // Bitcount in binary32 mantissa + sign bit

        seed    *= mulprime;
        cuint32  = (seed >> shift) | onef;

        return cfloat - 1.0f;
    }



    rngFloat::rngFloat() {
        // Check that the RNG will work correctly on the target platform.
        static_assert( 
            (sizeof(float)==4)  &&  (sizeof(float)==sizeof(uint32_t)),
            "RNG requires IEEE-754 binary32 float and a 32-bit unsigned integer type."
        );

        // Initialise the RNG based on the current time.  Ensures the RNG doesn't
        // repeat the same sequence of numbers every time the program runs.

        // It can be initialised with any non-zero constant value. It's possible
        // to save the initial seed and repeat the same sequence at a later point,
        // but there's no need for that function in this program.

        seed  = (uint32) std::time( nullptr ); 
        seed += (seed == 0); // If the seed is zero, add 1.  The seed can never be zero or the RNG will break.
    }



    rngFloat::rngFloat( uint32 seed ) {
        this->seed = seed;
    }



    rngFloat::~rngFloat() {
        // Do nothing
    }
};