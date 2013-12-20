

#include "core.h"
#include <cmath>



namespace coreSys
{
    // Timing state
    const int stepFrequency = int( floor(1000.0f/60.0f) );
    int step = 0;



    // Player entity
    entitySys::entPlayer* player = nullptr;



    // Zoom
    float zoomMagFactor = 1.0f;



    // Spotlight controls
    float spotConeFactor     = 1.0f;
    float spotSoftnessFactor = 1.0f;



    // Render control
    bool renderToon      = false;
    bool renderWireframe = false;
};