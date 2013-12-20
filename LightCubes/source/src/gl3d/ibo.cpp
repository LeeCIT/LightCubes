

#include "ibo.h"
#include <cassert>



namespace gl
{
    GLuint ibo::getIndexType() {
        return indexType;
    }



    size_t ibo::getIndexSize() {
        switch (indexType) {
            case GL_UNSIGNED_BYTE:  return sizeof( GLubyte  );
            case GL_UNSIGNED_SHORT: return sizeof( GLushort );
            case GL_UNSIGNED_INT:   return sizeof( GLuint   );
        }

        assert( false );
        return 0;
    }



    ibo::operator GLuint() const {
        return handle;
    }



    void ibo::construct(  const void* const indeces,  size_t sizeInBytes,  GLuint usage  ) {
        // Common constructor.
        // Note: 'verts' can be nullptr.

        GLint prevBinding;
        glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &prevBinding );
            
            glGenBuffers( 1, &handle );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, handle );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, indeces, usage );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, prevBinding );
    }



    ibo::ibo(  const GLubyte* const indices,  size_t indexCount,  GLuint usage  ) {
        this->indexType = GL_UNSIGNED_BYTE;
        construct( indices, indexCount*sizeof(GLubyte), usage );
    }



    ibo::ibo(  const GLushort* const indices,  size_t indexCount,  GLuint usage  ) {
        this->indexType = GL_UNSIGNED_SHORT;
        construct( indices, indexCount*sizeof(GLushort), usage );
    }



    ibo::ibo(  const GLuint* const indices,  size_t indexCount,  GLuint usage  ) {
        this->indexType = GL_UNSIGNED_INT;
        construct( indices, indexCount*sizeof(GLuint), usage );
    }
    


    ibo::~ibo() {
        glDeleteBuffers( 1, &handle );
    }
};