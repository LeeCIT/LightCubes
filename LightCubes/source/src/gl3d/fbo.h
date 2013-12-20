

// FBO - Framebuffer object
// An offscreen buffer for drawing.  It can also be drawn: its buffers are textures.

#pragma once
#include "colour.h"
#include "texture.h"



namespace gl
{
    class fbo
    {
       private:
         GLuint   handle;
         texture* texColour;
         texture* texDepth;
   
         void checkStatus();


       public:
         const texture* const getTexColour();
         const texture* const getTexDepth ();

         int    getWidth () const;
         int    getHeight() const;
         colour readTexel( int x, int y ); // For picking
     
         operator GLuint() const; // Retreive handle when cast to uint.

         fbo( int width, int height, bool useDepth=false );
        ~fbo();
    };
};