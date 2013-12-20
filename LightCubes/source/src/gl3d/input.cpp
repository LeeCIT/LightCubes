

#include "input.h"
#include "core.h"
#include "func.h"
#include "glCore.h"
#include <cmath>



namespace inputSys
{
    // Control state
    vec3  ctrlAxisMove         = 0.0f;
    float ctrlAxisPitch        = 0.0f;
    float ctrlAxisYaw          = 0.0f;
    float ctrlAxisRoll         = 0.0f;
    float ctrlAxisSpotPitch    = 0.0f;
    float ctrlAxisSpotYaw      = 0.0f;
    float ctrlAxisSpotCone     = 0.0f;
    float ctrlAxisSpotSoftness = 0.0f;
    




    namespace bind
    {
        // Constructor, initialises to zero
        keyBind :: keyBind() {
            keyIndex  = 0;
            isSpecial = false;
        }



        // Input bindings.  Just initialised here - change them with setBind() in evStart().
        keyBind moveForward,
                moveBackward,
                moveLeft,
                moveRight,
                moveUp,
                moveDown,
                pitchPos,
                pitchNeg,
                yawPos,
                yawNeg,
                rollPos,
                rollNeg,
                zoomMagPos,
                zoomMagNeg,
                zoomMagReset,
                spotConePos,
                spotConeNeg,
                spotSoftnessPos,
                spotSoftnessNeg,
                toggleWireframe,
                toggleToonShader,
                quitProgram;



        // Set binding
        void setBind( keyBind& bindref, int key, bool isSpecial ) {
            bindref.keyIndex  = key;
            bindref.isSpecial = isSpecial;
        }



        // Check binding state
        // Down
        bool bindDown( const keyBind& bindref ) {
            return core::keyDown( bindref.keyIndex, bindref.isSpecial );
        }

        // Press
        bool bindPressed( const keyBind& bindref ) {
            return core::keyPressed( bindref.keyIndex, bindref.isSpecial );
        }

        // Release
        bool bindReleased( const keyBind& bindref ) {
            return core::keyReleased( bindref.keyIndex, bindref.isSpecial );
        }
    };





    namespace core
    {
        // Key states
        // There are two sets of 256 bools, one for normal ASCII keys
        // and another for GLUT specials.  Their ranges overlap so they
        // have to be separated by an offset.
        const int keyCount         = 256 * 2;
        const int keySpecialOffset = keyCount / 2;

        bool keyState     [ keyCount ];
        bool keyStateDelta[ keyCount ];
        bool keyStateEv   [ keyCount ];



        // Update controls
        void ctrlUpdate() {
            using namespace inputSys::bind;
            using coreSys::zoomMagFactor;
            using coreSys::spotConeFactor;
            using coreSys::spotSoftnessFactor;

            // High-level axes
            // Movement and orientation are smoothed by continuous lerping
            vec3  SRCctrlAxisMove   = vec3( float( bindDown(moveRight)    - bindDown(moveLeft)    ),
                                            float( bindDown(moveUp)       - bindDown(moveDown)    ),
                                            float( bindDown(moveBackward) - bindDown(moveForward) ) );

            // Movement axes map to a sphere, not a cube.
            if (length(SRCctrlAxisMove) > 0.0f) 
                SRCctrlAxisMove = normalise( SRCctrlAxisMove );

            float SRCctrlAxisPitch     = float( bindDown(pitchPos) - bindDown(pitchNeg) );            
            float SRCctrlAxisYaw       = float( bindDown(  yawPos) - bindDown(  yawNeg) );
            float SRCctrlAxisRoll      = float( bindDown( rollPos) - bindDown( rollNeg) );
            
            float ctrlAxisSpotCone     = float( bindDown(    spotConePos) - bindDown(    spotConeNeg) );
            float ctrlAxisSpotSoftness = float( bindDown(spotSoftnessPos) - bindDown(spotSoftnessNeg) );

            // Lerp movement/orientation axes
            const float lerpRate = 0.05f;
            ctrlAxisMove  = lerp( ctrlAxisMove,  SRCctrlAxisMove,  lerpRate );
            ctrlAxisPitch = lerp( ctrlAxisPitch, SRCctrlAxisPitch, lerpRate );
            ctrlAxisYaw   = lerp( ctrlAxisYaw,   SRCctrlAxisYaw,   lerpRate );
            ctrlAxisRoll  = lerp( ctrlAxisRoll,  SRCctrlAxisRoll,  lerpRate );


            // Zoom
            const float zoomInc = 0.0325f * zoomMagFactor; // Self-multiply makes it perceptually constant
            zoomMagFactor += zoomInc * float(bindDown(zoomMagNeg) - bindDown(zoomMagPos));
            zoomMagFactor  = clamp( zoomMagFactor, 0.05f, 2.0f );

            // Zoom reset
            if (bindPressed( zoomMagReset ))
                coreSys::zoomMagFactor = 1.0f;

            // Spot
            const float spotFactorRate = 0.0625f;
            spotConeFactor     += ctrlAxisSpotCone     * spotFactorRate;
            spotSoftnessFactor += ctrlAxisSpotSoftness * spotFactorRate;

            spotConeFactor     = clamp( spotConeFactor,     0.01f, 4.0f );
            spotSoftnessFactor = clamp( spotSoftnessFactor, 0.01f, 4.0f );


            // Render control
            // Toon
            if (bindPressed(toggleToonShader))
                toggle( coreSys::renderToon );

            // Wireframe
            if (bindPressed(toggleWireframe))
                toggle( coreSys::renderWireframe );
        }





        ///////////////////////////////////////////////////
        // Functions for handling 'raw' keyboard input
        ///////////////////////////////////////////////////

        // Initialise the arrays
        void keyInit() {
            for (int i=0; i<keyCount; i++) {
                keyState     [i] = false;
                keyStateDelta[i] = false;
                keyStateEv   [i] = false;
            }
        }



        // Update
        void keyUpdate() {
            for (int i=0; i<keyCount; i++) {
                keyStateDelta[i] = (keyState[i] != keyStateEv[i]); // Changed since last step?
                keyState     [i] = keyStateEv[i]; // Down right now?
            }
        }



        void keyDoSpecialOffset( int* key, bool isSpecial ) {
            if (isSpecial)
                *key += keySpecialOffset;
        }



        // Down - Key is held down right now
        bool keyDown( int key, bool isSpecial ) {
            keyDoSpecialOffset( &key, isSpecial );
            return keyState[key];
        }



        // Press - Key is down right now, and it changed since last step
        bool keyPressed( int key, bool isSpecial ) {
            keyDoSpecialOffset( &key, isSpecial );
            return keyState[key] && keyStateDelta[key];
        }



        // Release - Key isn't down, and it changed since last step
        bool keyReleased( int key, bool isSpecial ) {
            keyDoSpecialOffset( &key, isSpecial );
            return !keyState[key] && keyStateDelta[key];
        }
    };
};