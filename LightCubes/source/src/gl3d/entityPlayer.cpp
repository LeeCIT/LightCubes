

#include "entityPlayer.h"
#include "def.h"
#include "draw.h"
#include "func.h"
#include "core.h"
#include "glCore.h"
#include "input.h"



namespace entitySys
{
    // Control speeds
    const float entPlayer::speedMove   = 4.0f;
    const float entPlayer::speedRotate = 4.0f;



    // Collision
    void entPlayer :: evCollide( entity* const other ) {
        
    }



    // Step
    void entPlayer :: evStep() {

    }



    // Draw
    void entPlayer :: evDraw() const {
        
    }



    // Construct
    entPlayer :: entPlayer() {
        coreSys::player = this;

        type   = entitySys::entTypePlayer;
        radius = 1.0f;
        scale  = 1.0f;
    }



    // Destruct
    entPlayer :: ~entPlayer() {
        coreSys::player = nullptr;
    }
};