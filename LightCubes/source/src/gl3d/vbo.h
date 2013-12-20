

// VBO - Vertex buffer object
// A GPU-resident memory buffer for vertex attributes.
// TODO: template this class

#pragma once
#include "glCore.h"
#include "vertex.h"
#include <vector>



namespace gl
{
    class vbo
    {
      private:
        GLuint handle;

        void construct(  const vertex* const verts,  size_t vertexCount,  GLuint usage  );


      public:
        operator GLuint() const;

        vbo(  const vertex* const verts,  size_t vertexCount,  GLuint usage=GL_STATIC_DRAW  );
        vbo(                              size_t vertexCount,  GLuint usage=GL_STATIC_DRAW  );
       ~vbo();
    };
};