

// Image library
// Uses STB_Image from http://nothings.org.
// The library is public domain and supports most standard image formats.

#pragma once
#include "memoryRaw.h"
#include <cstdint>
#include <string>



namespace imageSys
{
    namespace libSTBI // STBI_Image.  I stuck it in a namespace for the sake of neatness.
    {
        #define STBI_NO_STDIO
        #define STBI_NO_HDR
        #define STBI_HEADER_FILE_ONLY
            #include "../../../libraries/stb_image/stb_image.c"
        #undef  STBI_HEADER_FILE_ONLY
    };



    // 32-bit 8BPC RGBA image container.
    // Constructs from memory-resident compressed image file.
    class image
    {
      private:
        typedef memory::raw<uint8_t> storage;
        typedef const uint8_t* const ptrType;

        storage data;
        int     width;
        int     height;
        bool    isGood;


      public:
        ptrType getDataPtr()       const;
        int     getWidth()         const;
        int     getHeight()        const;
        int     getBytesPerPixel() const;
        size_t  getSizeInBytes()   const;
        bool    getGoodness()      const;
        void    flipY(); // Mirror vertically.  Needed for OpenGL textures.

        image( void* imgDataPtr, size_t bytes );
       ~image();
    };
};