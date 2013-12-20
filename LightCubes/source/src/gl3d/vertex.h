
// Vertex structs.



#pragma once
#include "colour.h"
#include "glCore.h"
#include "vec.h"



struct vertex { // 5 interleaved attributes, 16 floats, 64 bytes.
    vec3   pos;      // Position
    vec3   norm;     // Normal
    vec2   tex;      // Texture coordinates
    colour diffuse;  // Diffuse colour
    colour specular; // Specular colour (really just an arbitrary secondary colour)

    vertex( const vec3&   p,
            const vec3&   n,
            const vec2&   t = vec2(0.0f),
            const colour& d = colour::white,
            const colour& s = colour::white );

    vertex();
};



struct vertex2d { // 3 interleaved attribs, 8 floats, 32 bytes
    vec2   pos;      // Position
    vec2   tex;      // Texture coordinates
    colour diffuse;  // Diffuse colour

    vertex2d( const vec2&   p,
              const vec2&   t = vec2(0.0f),
              const colour& d = colour::white );

    vertex2d();
};



// Test my own assumptions...
static_assert( sizeof(vertex)==64, "sizeof(vertex) isn't 64!" );