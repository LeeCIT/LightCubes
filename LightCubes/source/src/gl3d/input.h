

// Input system - exposes a simple, extensible interface for binding/checking input.

#pragma once
#include "vec3.h"



namespace inputSys
{
    // Control state
    extern vec3  ctrlAxisMove;  // Movement: -left,+right, -down,+up, -forward,+back    
    extern float ctrlAxisPitch; // Rotation around X
    extern float ctrlAxisYaw;   // Rotation around Y
    extern float ctrlAxisRoll;  // Rotation around Z
    extern float ctrlAxisSpotPitch;
    extern float ctrlAxisSpotYaw;
    extern float ctrlAxisSpotCone;
    extern float ctrlAxisSpotSoftness;



    namespace bind
    {
        // Binding structure def.  Could be extended later to handle devices other than the keyboard.
        struct keyBind {
            int  keyIndex;
            bool isSpecial;

            keyBind();
        };

        // Input key bindings
        extern keyBind moveForward;
        extern keyBind moveBackward;
        extern keyBind moveLeft;
        extern keyBind moveRight;
        extern keyBind moveUp;
        extern keyBind moveDown;
        extern keyBind pitchPos;
        extern keyBind pitchNeg;
        extern keyBind yawPos;
        extern keyBind yawNeg;
        extern keyBind rollPos;
        extern keyBind rollNeg;
        extern keyBind zoomMagPos;
        extern keyBind zoomMagNeg;
        extern keyBind zoomMagReset;
        extern keyBind spotConePos;
        extern keyBind spotConeNeg;
        extern keyBind spotSoftnessPos;
        extern keyBind spotSoftnessNeg;
        extern keyBind toggleWireframe;
        extern keyBind toggleToonShader;
        extern keyBind quitProgram;

        // Set a binding
        void setBind( keyBind& bindRef, int key, bool isSpecial );

        // Check state of linked key
        bool bindDown    ( const keyBind& bindref ); // Down during current step (continuous)
        bool bindPressed ( const keyBind& bindref ); // Pressed  on current step (once)
        bool bindReleased( const keyBind& bindref ); // Released on current step (once)
    };





    namespace core
    {
        // Key states, used by control functions
        extern const int keyCount;
        extern const int keySpecialOffset;
        extern bool keyState     []; // Discrete key state for the current step.
        extern bool keyStateDelta[]; // Whether key changed since the last keyUpdate() call.
        extern bool keyStateEv   []; // Instantaneous state set via callback, not used directly.

        // Funcs
        void ctrlUpdate(); // Update controls.

        void keyInit();   // Initialise the key arrays.
        void keyUpdate(); // Update the key arrays.  Run once per step.
        bool keyDown    ( int key, bool isSpecial=false ); // If key is down this step. (continuous)
        bool keyPressed ( int key, bool isSpecial=false ); // If key was pressed this step.  (once)
        bool keyReleased( int key, bool isSpecial=false ); // If key was released since last step. (once)
    };
};