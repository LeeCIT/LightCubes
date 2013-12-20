

// Light - defines light structs.


#pragma once
#include "colour.h"
#include "vec.h"



namespace lightSys
{
    struct global {
        colour ambient; // Ambient light added to entire scene
    };



    struct directional {
        vec3   vec; // World-space orientation
        colour ambient;
        colour diffuse;
        colour specular;
    };



    struct point {
        vec3   pos;      // World-space light position
        vec3   decay;    // Light distance falloff params: x=constant, y=linear, z=quadratic
        colour ambient;  // Light ambient colour, modulated with material ambient
        colour diffuse;  // ...
        colour specular; // ...
    };



    struct spot {
        vec3   pos;
        vec3   vec;
        vec3   decay;
        float  cone;     // Arc around vector.
        float  softness; // Controls edge falloff.
        colour ambient;
        colour diffuse;
        colour specular;
    };



    struct line { // This one is my own invention.
        vec3   posA;
        vec3   posB;
        vec3   decay;
        colour ambient;
        colour diffuse;
        colour specular;
    };
};