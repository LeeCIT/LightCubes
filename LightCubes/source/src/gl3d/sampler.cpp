

#include "sampler.h"
#include "func.h"
#include <cassert>



namespace gl
{
    sampler :: operator GLuint () const {
        return handle;
    }



    void sampler :: setWrapMode( GLuint mode ) {
        setWrapModeX( mode );
        setWrapModeY( mode );
        setWrapModeZ( mode );
    }



    void sampler :: setWrapModeX( GLuint mode ) {
        glSamplerParameteri( *this, GL_TEXTURE_WRAP_S, mode );
    }



    void sampler :: setWrapModeY( GLuint mode ) {
        glSamplerParameteri( *this, GL_TEXTURE_WRAP_T, mode );
    }



    void sampler :: setWrapModeZ( GLuint mode ) {
        glSamplerParameteri( *this, GL_TEXTURE_WRAP_R, mode );
    }



    void sampler :: setBorderColour( const colour& col ) {
        glSamplerParameterfv( *this, GL_TEXTURE_BORDER_COLOR, col );
    }



    void sampler :: setFilter( bool linear, bool hasMip, bool linearMip ) {
        GLuint minFilter = gl::texture::getFilterMin( linear, hasMip, linearMip );
        GLuint magFilter = gl::texture::getFilterMag( linear );

        glSamplerParameteri( *this, GL_TEXTURE_MIN_FILTER, minFilter );
        glSamplerParameteri( *this, GL_TEXTURE_MAG_FILTER, magFilter );
    }



    void sampler :: setFilter( GLuint minFilter, GLuint magFilter ) {
        glSamplerParameteri( *this, GL_TEXTURE_MIN_FILTER, minFilter );
        glSamplerParameteri( *this, GL_TEXTURE_MAG_FILTER, magFilter );
    }



    void sampler :: setAnisotropy( float maxSamples ) {
        maxSamples = clamp( maxSamples, 1.0f, 16.0f );
        glSamplerParameterf( *this, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxSamples );
    }



    sampler :: sampler( bool linear, bool hasMip, bool linearMip, GLuint wrapMode ) {
        glGenSamplers( 1, &handle );
        setFilter( linear, hasMip, linearMip );
        setWrapMode( wrapMode );
    }



    sampler :: sampler( const texture& texBasis ) {
        glGenSamplers( 1, &handle );

        // TODO: Fix it.  This doesn't work.
        //       And it's so simple I really can't see what could possibly be wrong. 
        assert(false);
        
        // Get sampling information from the texture
        GLint texLast;
        glGetIntegerv( GL_TEXTURE_BINDING_2D, &texLast );

            glBindTexture( GL_TEXTURE_2D, texBasis );
                GLint   wrapX;    glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,             &wrapX   );
                GLint   wrapY;    glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,             &wrapY   );
                GLint   wrapZ;    glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R,             &wrapZ   );
                colour  bordCol;  glGetTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,        bordCol );
                GLint   minFilt;  glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,         &minFilt );
                GLint   magFilt;  glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,         &magFilt );
                GLfloat aniso;    glGetTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &aniso   );
            glBindTexture( GL_TEXTURE_2D, texLast ); // Rebind last
        
        // Apply sampling parameters.
        // There are actually loads more besides the ones I implemented here.
        setFilter( minFilt, magFilt );
        setWrapModeX( wrapX );
        setWrapModeY( wrapY );
        setWrapModeZ( wrapZ );
        setAnisotropy( aniso );
    }



    sampler ::~sampler()
    {
        glDeleteSamplers( 1, &handle );
    }
};