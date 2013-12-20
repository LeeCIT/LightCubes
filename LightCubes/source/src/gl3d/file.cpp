
// File input

#include "file.h"
#include "memoryRaw.h"
#include <cassert>
#include <fstream>
#include <iostream>



#define SETOKAY(b) if (readOkay != nullptr) { *readOkay = (b); }



namespace fileSys
{
    // Read generic
    string read( const string& fileName, bool* readOkay )
    {
        using std::ifstream;
        using std::cerr;
        using std::istreambuf_iterator;

        string   out;
        ifstream file;
        
        file.open( fileName, ifstream::in | ifstream::binary );
        if (!file.is_open()) {
            cerr << "Failed to open file '" + fileName + "'.\n";
            SETOKAY( false );
        } 
        else {
            file.seekg( 0, ifstream::end );
            size_t size = (size_t) file.tellg();

            auto mem = memory::raw<char>( size );

                file.seekg( 0, ifstream::beg );
                file.read( mem, size );

                out.resize( size );
                memcpy( (void*) out.data(), mem, size );

            SETOKAY( true );
        }

        return out;
    }





    // Read image
    imageSys::image readImage( const string& fileName, bool* readOkay ) {
        using imageSys::image;
        using std::cerr;

        // Read raw file
        bool   rawOkay;
        string rawData = read( fileName, &rawOkay );
        void*  rawPtr  = (void*) rawData.data();

        assert( rawOkay );

        // Decompress
        image img( rawPtr, rawData.size() );
        SETOKAY( img.getGoodness() );

        if (!img.getGoodness())
            cerr << "Failed to decompress image '" << fileName << "'.\n";

        return img;
    }
}