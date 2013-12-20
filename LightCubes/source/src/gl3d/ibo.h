

// IBO - Index Buffer Object
// A GPU-resident memory buffer for vertex indeces.
// Indeces can be 8, 16 or 32 bits.  The smaller the better.

#pragma once
#include "glCore.h"



namespace gl
{
    class ibo
    {
       private:
         GLuint indexType;
         GLuint handle;

         void construct( const void* const indeces, size_t sizeInBytes, GLuint usage );


       public:
         GLuint getIndexType();
         size_t getIndexSize();

         operator GLuint() const;

         ibo(  const GLubyte*  const indeces,  size_t indexCount,  GLuint usage=GL_STATIC_DRAW  );
         ibo(  const GLushort* const indeces,  size_t indexCount,  GLuint usage=GL_STATIC_DRAW  );
         ibo(  const GLuint*   const indeces,  size_t indexCount,  GLuint usage=GL_STATIC_DRAW  );
        ~ibo();
    };
};