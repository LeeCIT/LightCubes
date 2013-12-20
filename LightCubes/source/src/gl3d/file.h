

// File input

#pragma once
#include "image.h"
#include <string>



namespace fileSys
{
    using std::string;



    // Read file generically.
    string read( const string& fileName, bool* readOkay=nullptr );



    // Read an image.
    // Supported formats: PNG, TGA, JPEG, GIF, BMP, PIC, PSD.
    // Resulting format is always 32-bit RGBA.
    imageSys::image readImage( const string& fileName, bool* readOkay=nullptr );
};