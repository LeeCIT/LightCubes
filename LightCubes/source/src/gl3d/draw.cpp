


#include "glCore.h"
#include "screen.h"



// Fit the viewport to the window.  Adapts field of view parameters.
void setViewportAspectCorrect( int windowSizeX, int windowSizeY ) {
    screen::update( (float) windowSizeX,  (float) windowSizeY );

    // Update the viewport.
    glViewport( 0,0, windowSizeX,windowSizeY );
}