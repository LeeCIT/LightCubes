

#include "vbo.h"
#include "shader.h"
#include "vertex.h"



namespace gl
{
    vbo :: operator GLuint() const {
        return handle;
    }



    // Common constructor.
    // Note: 'verts' can be nullptr.
    void vbo :: construct(  const vertex* const verts,  size_t vertexCount,  GLuint usage  ) {
        GLint prevBinding;
        glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &prevBinding );

            size_t sizeInBytes = sizeof(vertex) * vertexCount;

            glGenBuffers( 1, &handle );
            glBindBuffer( GL_ARRAY_BUFFER, *this );
            glBufferData( GL_ARRAY_BUFFER, sizeInBytes, verts, usage );

        glBindBuffer( GL_ARRAY_BUFFER, prevBinding );
    }



    // Construct from an array of vertices.
    vbo :: vbo(  const vertex* const verts,  size_t vertexCount,  GLuint usage  ) {
        construct( verts, vertexCount, usage );
    }



    // Construct blank VBO with given vertex capacity.
    vbo :: vbo(  size_t vertexCount,  GLuint usage  ) {
        construct( nullptr, vertexCount, usage );
    }



    // Destruct
    vbo ::~vbo() {
        glDeleteBuffers( 1, &handle );
    }
};