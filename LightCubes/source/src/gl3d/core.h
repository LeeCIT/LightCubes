

// Game state

#pragma once
#include "entityPlayer.h"



namespace coreSys
{
    // Timing state
    extern const int stepFrequency; // Game logic operates in discrete steps at 60hz
    extern int step; // The current step index.  Time in logical units, used for animation etc.



    // Player entity
    extern entitySys::entPlayer* player;



    // Zoom
    extern float zoomMagFactor;



    // Spotlight controls
    extern float spotConeFactor;
    extern float spotSoftnessFactor;
    

    
    // Render control
    extern bool renderToon;
    extern bool renderWireframe;
};