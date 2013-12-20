

// Sampler - Defines the sampling parameters for a texture image unit.
// When bound, it overrides the TIU sampling state: wrap mode, filtering mode, etc.
// Before GL 3.3, filtering state was exclusively part of the texture state.

#pragma once
#include "colour.h"
#include "glCore.h"
#include "texture.h"



namespace gl
{
    class sampler
    {
      private:
        GLuint handle;


      public:
        void setWrapMode    ( GLuint mode );
        void setWrapModeX   ( GLuint mode );
        void setWrapModeY   ( GLuint mode );
        void setWrapModeZ   ( GLuint mode );
        void setBorderColour( const colour& col );
        void setFilter      ( bool linear, bool hasMip, bool linearMip );
        void setFilter      ( GLuint minFilter, GLuint magFilter );
        void setAnisotropy  ( float maxSamples );

        operator GLuint () const;

        sampler( bool linear, bool hasMip, bool linearMip, GLuint wrapMode=GL_REPEAT );
        sampler( const texture& texBasis ); // Inherit from texture - would be the easiest and safest method IF I actually got it working.
       ~sampler();
    };
};