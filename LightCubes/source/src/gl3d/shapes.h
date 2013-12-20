

// Shapes - defines simple shapes.


#pragma once
#include "glObject.h"
#include "vertex.h"



namespace shapes
{
    namespace plane
    {
        extern const int vertCount;
        extern const int indCount;
        extern const vertex  vert[];
        extern const GLubyte ind [];
    };



    namespace cube
    {
        extern const int vertCount;
        extern const int indCount;
        extern const int faces;
        extern const int faceVerts;
        extern const vertex  vert[];
        extern const GLubyte ind [];
    };



    namespace trapezoid
    {
        extern const int vertCount;
        extern const int indCount;
        extern const int faces;
        extern const int faceVerts;
        extern const vertex  vert[];
        extern const GLubyte ind [];
    };
};