

#include "screen.h"



namespace screen
{
    float sizeX;
    float sizeY;
    float halfX;
    float halfY;

    float edgeLeft;
    float edgeBottom;
    float edgeRight; 
    float edgeTop; 

    const float baseFov = 60.0f;
          float aspect;
          float fovY;
          float fovX;


    void init( float newSizeX, float newSizeY ) {
        // Just for code clarity / de-duplication.
        update( newSizeX, newSizeY );
    }



    void update( float newSizeX, float newSizeY ) {
        screen::sizeX = newSizeX;
        screen::sizeY = newSizeY;
        screen::halfX = sizeX / 2.0f;
        screen::halfY = sizeY / 2.0f;

        screen::edgeLeft   = -halfX;     // Assumes 0,0 centre
        screen::edgeBottom = -halfY;     // ...
        screen::edgeRight  = +halfX - 1; // -1 because zero occupies a pixel too.
        screen::edgeTop    = +halfY - 1; // Otherwise the screen would be n+1 pixels from edge to edge.

        screen::aspect = sizeX / sizeY;
        screen::fovY   = baseFov;
        screen::fovX   = fovY * aspect;
    }
};