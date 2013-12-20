

#include "texture.h"
#include "config.h"
#include "def.h"
#include "file.h"
#include <iostream>



namespace gl
{
    // Return appropriate filter mode for given parameters.
    GLuint texture :: getFilterMin( bool linear, bool mipmap, bool miplinear ) {
        if (!mipmap) { 
            return linear ? GL_LINEAR : GL_NEAREST;
        } else {
            if (miplinear)
                 return linear ? GL_LINEAR_MIPMAP_LINEAR  : GL_NEAREST_MIPMAP_LINEAR;
            else return linear ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST;
        }
    }



    // Return appropriate filter mode for given parameters.
    GLuint texture :: getFilterMag( bool linear ) {
        return linear ? GL_LINEAR : GL_NEAREST;
    }



    // Return appropriate format for given parameters.
    GLuint texture :: getFormat( bool useCompression ) {
        return useCompression  ?  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  :  GL_RGBA;
    }




    // Getters
    string texture :: getName()       const { return name;         }
    int    texture :: getWidth()      const { return width;        }
    int    texture :: getHeight()     const { return height;       }
    bool   texture :: getMipped()     const { return isMipped;     }
    bool   texture :: getCompressed() const { return isCompressed; }





    // Implicit cast to handle
    texture :: operator GLuint() const {
        return handle;
    }





    texture :: texture( const string& name, bool useMipmapping, bool useCompression ) {
        this->name         = name;
        this->width        = 0;
        this->height       = 0;
        this->isMipped     = useMipmapping;
        this->isCompressed = useCompression;
        
        GLuint minFilter = getFilterMin( true, useMipmapping, useMipmapping );
        GLuint magFilter = getFilterMag( true );
        GLuint format    = getFormat( useCompression );

        bool imageOkay;
        auto img = fileSys::readImage( def::dirTexture + name, &imageOkay );
        
        if (imageOkay) {
            // Set info.
            this->width  = img.getWidth();
            this->height = img.getHeight();

            // Vertical flip - image editing programs use top-left [0,0], OpenGL uses bottom-left.
            img.flipY();

            int texPrevious;
            glGetIntegerv( GL_TEXTURE_BINDING_2D, &texPrevious );

                // Define tex.
                glGenTextures( 1, &handle );
                glBindTexture( GL_TEXTURE_2D, *this );
                glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
                glTexImage2D ( GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getDataPtr() );

                // Set up default sampling parameters.
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
                glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, config::texAnisoMax );            

                // Generate mipmaps.
                if (useMipmapping)
                    glGenerateMipmap( GL_TEXTURE_2D );

            // Reset to previously bound texture.
            glBindTexture( GL_TEXTURE_2D, texPrevious );
        }
        else {
            std::cerr << "Failed to load texture: '" << name << "'.";
        }
    }



    // Blank texture for FBOs.
    texture :: texture( int width, int height, bool isDepthTexture ) {
        this->width  = width;
        this->height = height;

        int texPrevious;
        glGetIntegerv( GL_TEXTURE_BINDING_2D, &texPrevious );

            GLuint formatInt = (isDepthTexture) ? GL_DEPTH_COMPONENT : GL_RGBA;
            GLuint formatExt = (isDepthTexture) ? GL_DEPTH_COMPONENT : GL_RGBA;

            glGenTextures  ( 1, &handle );
            glBindTexture  ( GL_TEXTURE_2D, *this );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getFilterMin(true,false) );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getFilterMag(true)       );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, config::texAnisoMax );
            glTexImage2D   ( GL_TEXTURE_2D, 0, formatInt, width, height, 0, formatExt, GL_FLOAT, nullptr );
    
        glBindTexture( GL_TEXTURE_2D, texPrevious );
    }



    texture ::~texture() {
        glDeleteTextures( 1, &handle );
    }
};