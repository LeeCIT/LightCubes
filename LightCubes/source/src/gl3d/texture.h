

// Texture object

#pragma once
#include "glCore.h"
#include <string>



namespace gl
{
    using std::string;



    class texture
    {
       friend class sampler;

       private:
         static GLuint getFilterMin( bool linear, bool mipmap, bool miplinear=false );
         static GLuint getFilterMag( bool linear );
         static GLuint getFormat   ( bool useCompression );


       private:
         GLuint handle;
         string name;
         int    width;
         int    height;
         bool   isMipped;
         bool   isCompressed;
     

       public:
         string getName()       const;
         int    getWidth()      const;
         int    getHeight()     const;
         bool   getMipped()     const;
         bool   getCompressed() const;

         operator GLuint() const;

         texture( const string& name, bool useMipmapping=true, bool useCompression=false );
         texture( int width, int height, bool isDepthTexture=false );
        ~texture();
    };
};



/*
    === Texture parameters ===
       
    :: Mipmaps
        - Increase VRAM usage by 1/3rd.
        - Prevents temporal aliasing and increases performance.

    :: Formats
        - GL_RGBA8
        - GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:  (0.25x VRAM use, JPEG-like quality loss)

    :: GL_TEXTURE_WRAP_S/T/R
        - GL_REPEAT
        - GL_MIRRORED_REPEAT
        - GL_CLAMP_TO_EDGE   (Clamp within texture, using nearest edge if outside)
        - GL_CLAMP_TO_BORDER (Use border colour if outside)

    :: GL_TEXTURE_BORDER_COLOR
        - Used with GL_CLAMP_TO_BORDER.  Defaults to [0,0,0,0] RGBA.

    :: GL_TEXTURE_MIN_FILTER
        - GL_NEAREST                  Nearest, no mip
        - GL_NEAREST_MIPMAP_NEAREST   Nearest, nearest mip
        - GL_NEAREST_MIPMAP_LINEAR    Nearest, linear mip
        - GL_LINEAR                   Linear, no mip
        - GL_LINEAR_MIPMAP_NEAREST    Linear, nearest mip
        - GL_LINEAR_MIPMAP_LINEAR     Linear, linear mip ('trilinear' filtering)

    :: GL_TEXTURE_MAG_FILTER
        - GL_NEAREST  
        - GL_LINEAR   

    :: GL_TEXTURE_MAX_ANISOTROPY_EXT
        - Anisotropy level.  Sharpens textures at shallow angles to the camera.
*/

