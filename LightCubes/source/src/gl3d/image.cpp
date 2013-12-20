

#include "image.h"
#include <iostream>



namespace imageSys
{
    namespace libSTBI {
        #include "../../../libraries/stb_image/stb_image.c"
    };



    // Getters
    const uint8_t* const image :: getDataPtr()        const { return data.ptr();   }
    int                  image :: getWidth()          const { return width;        }
    int                  image :: getHeight()         const { return height;       }
    int                  image :: getBytesPerPixel()  const { return 4;            }
    size_t               image :: getSizeInBytes()    const { return data.bytes(); }
    bool                 image :: getGoodness()       const { return isGood;       }



    // Modify
    void image :: flipY() {
        const size_t imageBytes = getSizeInBytes();
        const size_t rowBytes   = width * getBytesPerPixel();
        const size_t rows       = height;

        uint8_t* rowStart = data.ptr();
        uint8_t* rowEnd   = rowStart + imageBytes - rowBytes;
        auto     rowTemp  = memory::raw<uint8_t>( rowBytes );

        for (size_t rowOffset=0; rowOffset<rows/2; rowOffset++) {
            uint8_t* rowA = rowStart + (rowOffset * rowBytes);
            uint8_t* rowB = rowEnd   - (rowOffset * rowBytes);
            
            memcpy( rowTemp, rowA,    rowBytes ); // A -> T
            memcpy( rowA,    rowB,    rowBytes ); // B -> A
            memcpy( rowB,    rowTemp, rowBytes ); // T -> B
        }
    }



    // Construct
    image :: image( void* imgDataPtr, size_t sizeInBytes ) {
        using namespace libSTBI;
        using std::cerr;

        // Try to decode the file.
        const int imgCompDesired  = getBytesPerPixel(); // Always 4-component 8-bit RGBA.
              int imgCompInSource = 0;                  // Informational; the actual value in the source image.
        
        stbi_uc* decodePtr = stbi_load_from_memory(
            (stbi_uc*) imgDataPtr,
            int(sizeInBytes),
            &this->width,
            &this->height,
            &imgCompInSource,
            imgCompDesired
        );


        // Did it work?
        this->isGood = (decodePtr != nullptr);

        if (this->isGood) { 
            // Great!  Transfer to vector and free STBI data.
            size_t decodeBytes = this->width * this->height * imgCompDesired;
            this->data = storage( decodePtr, decodeBytes );
            stbi_image_free( decodePtr );
        } else {
            // Things got bad!
            this->data   = storage();
            this->width  = 0;
            this->height = 0;
            std::cerr << "Failed to decode image.\n";
        }
    }



    image::~image() {
        // Do nothing
    }
};