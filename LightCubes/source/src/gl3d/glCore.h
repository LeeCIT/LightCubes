

// Include OpenGL stuff.

#pragma once



// GLEW - adds all the extensions up to OpenGL 4.3.
#ifdef BUILD_64BIT
    #pragma comment( lib, "../../../libraries/glew/x64/lib/glew32.lib" )
#else
    #pragma comment( lib, "../../../libraries/glew/x86/lib/glew32.lib" )
#endif

#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "opengl32.lib" )
#include "../../../libraries/glew/x86/include/GL/glew.h"





// Freeglut
// Includes windows.h, which makes a great big mess.
#define WIN32_LEAN_AND_MEAN // Don't include obscure stuff.
#define NOMINMAX // Don't break STL min/max...

#ifdef BUILD_64BIT
    #pragma comment( lib, "../../../libraries/freeglut/lib/x64/freeglut.lib" )
#else
    #pragma comment( lib, "../../../libraries/freeglut/lib/freeglut.lib" )
#endif

#include "../../../libraries/freeglut/include/GL/freeglut.h"







