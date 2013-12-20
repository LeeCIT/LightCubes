

// Low-level optimisation stuff

#pragma once


namespace approx
{
    // Fast approximate reciprocal square root with zero at infinity
    float rsqrtzero( float x );



    // Fast sine approximation
    float sin( float rads );
};