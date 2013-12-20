

// Screen-space info.

#pragma once



namespace screen
{
    // Vars
    extern float sizeX;
    extern float sizeY;
    extern float halfX;
    extern float halfY;

    extern float edgeLeft;
    extern float edgeRight;
    extern float edgeTop;
    extern float edgeBottom;

    extern const float baseFov;
    extern       float aspect;
    extern       float fovY;
    extern       float fovX;



    // Funcs
    void init  ( float sizeX, float sizeY );
    void update( float sizeX, float sizeY );
};