

#include "fbo.h"
#include "texture.h"
#include <iostream>



namespace gl
{
    fbo :: operator GLuint() const {
        return handle;
    }



    void fbo :: checkStatus() {
        GLuint status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "FBO incomplete!  Error: ";

            switch (status) {
              case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         std::cerr << "INCOMPLETE_ATTACHMENT";          break;
              case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: std::cerr << "INCOMPLETE_MISSING_ATTACHMENT";  break;
              case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:     std::cerr << "INCOMPLETE_DIMENSIONS";          break;
              case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:        std::cerr << "INCOMPLETE_FORMATS";             break;
              case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        std::cerr << "INCOMPLETE_DRAW_BUFFER";         break;
              case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        std::cerr << "INCOMPLETE_READ_BUFFER";         break;
              case GL_FRAMEBUFFER_UNSUPPORTED:                   std::cerr << "NOT SUPPORTED";                  break;
              default:                                           std::cerr << "Unknown error!";                 break;
            }
        }
    }



    ///////////
    // Get
    /////////
    int fbo :: getWidth() const {
        return texColour->getWidth();
    }



    int fbo :: getHeight() const {
        return texColour->getHeight();
    }



    const texture* const fbo :: getTexColour() {
        return texColour;
    }



    const texture* const fbo :: getTexDepth() {
        return texDepth;
    }



    colour fbo::readTexel( int x, int y ) {
        GLint prevBinding;
        glGetIntegerv( GL_FRAMEBUFFER_BINDING, &prevBinding );

        colour col;

            glBindFramebuffer( GL_FRAMEBUFFER, *this );
            glPixelStorei( GL_PACK_ALIGNMENT, 1 );
            glReadPixels( x,y, 1,1, GL_RGBA, GL_FLOAT, col );

        glBindFramebuffer( GL_FRAMEBUFFER, prevBinding );

        return col;
    }





    ///////////////
    // Construct
    ////////////

    fbo :: fbo ( int width, int height, bool useDepth ) {
        this->texColour = new texture( width, height );
        this->texDepth  = nullptr;

        GLint prevBinding;
        glGetIntegerv( GL_FRAMEBUFFER_BINDING, &prevBinding );

            glGenFramebuffers     ( 1, &handle );
            glBindFramebuffer     ( GL_FRAMEBUFFER, *this );
            glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texColour, 0 );

            if (useDepth) {
                this->texDepth = new texture( width, height, true );
                glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *texDepth, 0 );
            }

            // How'd it go?
            checkStatus();

        // Reset to previous framebuffer.
        glBindFramebuffer( GL_FRAMEBUFFER, prevBinding ); 
    }



    fbo ::~fbo() {
        glDeleteFramebuffers( 1, &handle );
        delete texColour;
        delete texDepth;
    }
};