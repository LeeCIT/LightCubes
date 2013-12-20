

#include "vertexStream.h"
#include "arrayFunc.h"
#include <cassert>



namespace vertexStreamSys
{
    void streamBase :: setNormal  ( const vec3&   norm ) { vertNext.norm     = norm; }
    void streamBase :: setTexCoord( const vec2&   tc   ) { vertNext.tex      = tc;   }
    void streamBase :: setColour  ( const colour& col  ) { vertNext.diffuse  = col;  }
    void streamBase :: setSpecular( const colour& spec ) { vertNext.specular = spec; }

    void streamBase :: setNormal  ( float x, float y, float z )          { vertNext.norm     = vec3(x,y,z);     } 
    void streamBase :: setTexCoord( float x, float y )                   { vertNext.tex      = vec2(x,y);       }
    void streamBase :: setColour  ( float r, float g, float b, float a ) { vertNext.diffuse  = colour(r,g,b,a); }
    void streamBase :: setSpecular( float r, float g, float b, float a ) { vertNext.specular = colour(r,g,b,a); }



    void streamBase :: emit( const vec3& pos )
    {
        vertNext.pos = pos;
        vertArray[ vertIndex++ ] = vertNext;

        assert( !(vertIndex > vertCount) ); // Check for buffer overflow
    }



    void streamBase :: emit( float x, float y, float z )
    {
        emit( vec3(x,y,z) );
    }



    streamBase :: streamBase()
    {
        // Initialise to defaults.
        this->vaoPtr      = nullptr;
        this->vboPtr      = nullptr;
        this->vertArray   = nullptr;
        this->vertIndex   = 0;
        this->vertDefault = vertex( vec3(0.0f), vec3(0,0,1), vec2(0.0f), colour::white, colour::white );
        this->vertNext    = vertDefault;
    }



    streamBase ::~streamBase()
    {
        // Do nothing.  Derived classes must handle their own resources.
    }
};







//////////////////////////////////
// vertexStream
/////////////////////////////////


size_t vertexStream :: getCapacity () const { return vertCount; }
size_t vertexStream :: getEmitCount() const { return vertIndex; }



void vertexStream :: begin( GLint primitiveType ) {
    primType  = primitiveType;
    vertIndex = 0;
    vertNext  = vertDefault;
}



void vertexStream :: end() {
    size_t vertEmitCount = getEmitCount();
    size_t vertBytes     = vertEmitCount * sizeof(vertex);

    glBindVertexArray( *vaoPtr );
        glBindBuffer   ( GL_ARRAY_BUFFER, *vboPtr );
        glBufferSubData( GL_ARRAY_BUFFER, 0, vertBytes, vertArray );
        glDrawArrays( primType, 0, GLsizei(vertEmitCount) );
    glBindVertexArray( 0 );
}



// Init
vertexStream :: vertexStream( size_t vertexCount ) {
    vboPtr      = new gl::vbo( vertexCount, GL_STREAM_DRAW );
    vaoPtr      = new gl::vao( *vboPtr );
    vertArray   = new vertex[ vertexCount ];
    vertCount   = vertexCount;
}



vertexStream ::~vertexStream() {
    delete   vaoPtr;
    delete   vboPtr;
    delete[] vertArray;
}







//////////////////////////////////
// meshStream
/////////////////////////////////

size_t meshStream :: getCapacity()       const { return vertCount;     }
size_t meshStream :: getVertexCount()    const { return vertIndex;     }
size_t meshStream :: getPrimitiveCount() const { return meshPrimCount; }



void meshStream :: begin( GLint primitive ) {
    meshPrimCount++;
    meshPrimIndex = meshPrimCount - 1;
    meshPrimType .push_back( primitive );
    meshPrimVerts.push_back( 0 );

    assert( meshPrimType.size() == meshPrimCount ); // DEBUG ASSERT
}



void meshStream :: end() {
    // Do nothing.  This is purely to present a familiar interface.
}



void meshStream :: emit( const vec3& pos ) {
    // Insert the vertex
    vertNext.pos = pos;
    vertArray[ vertIndex++ ] = vertNext;

    // Update the mesh info
    meshPrimVerts[ meshPrimIndex ]++;

    // Check for buffer overflow if in debug mode
    assert( !(vertIndex > vertCount) );
}



void meshStream :: emit( float x, float y, float z ) {
    emit( vec3(x,y,z) );
}



void meshStream :: buildIbo( size_t count ) {
    if (count <= 255) {
        GLubyte* indArray = genArrayLinear<GLubyte>( 0, (GLubyte) count );
                 iboPtr   = new gl::ibo( indArray, count, GL_STATIC_DRAW );
        delete[] indArray;
    }
    else if (count <= 65535) {
        GLushort* indArray = genArrayLinear<GLushort>( 0, (GLushort) count );
                  iboPtr   = new gl::ibo( indArray, count, GL_STATIC_DRAW );
        delete[] indArray;
    }
    else { 
        GLuint*  indArray = genArrayLinear<GLuint>( 0, (GLuint) count );
                 iboPtr   = new gl::ibo( indArray, count, GL_STATIC_DRAW );
        delete[] indArray;
    }
}



void meshStream :: finalise() {
    assert( !isFinal );

    // Set capacity to match size
    vertCount = getVertexCount();

    // Create GL objects
    vboPtr = new gl::vbo( vertArray, vertCount, GL_STATIC_DRAW );
    buildIbo( vertCount );
    vaoPtr = new gl::vao( *vboPtr, *iboPtr );

    // Delete unnecessary CPU-side storage
    delete[] vertArray;
    meshPrimType .shrink_to_fit();
    meshPrimVerts.shrink_to_fit();

    // Finalise
    vertCount = vertCount;
    isFinal   = true;
}



void meshStream :: draw() const {
    assert( isFinal );

    glBindVertexArray( *vaoPtr );

        char*   indPtr  = nullptr;
        GLsizei indCtr  = 0;
        GLuint  indType = iboPtr->getIndexType();
        size_t  indSize = iboPtr->getIndexSize();
        
        for (size_t i=0; i<meshPrimCount; i++) {
            GLint   prim  = (GLint)   meshPrimType [i];
            GLsizei verts = (GLsizei) meshPrimVerts[i];

            glDrawRangeElements( prim, indCtr, indCtr+verts, verts, indType, (void*) indPtr );

            indPtr += verts * indSize;
            indCtr += verts;

            assert( glGetError() == GL_NO_ERROR );
        }
    
    glBindVertexArray( 0 );
}



meshStream :: meshStream( size_t vertexCount ) {
    this->vaoPtr        = nullptr;
    this->vboPtr        = nullptr;
    this->iboPtr        = nullptr;
    this->vertArray     = new vertex[ vertexCount ];
    this->vertCount     = vertexCount;
    this->isFinal       = false;
    this->meshPrimIndex = 0;
    this->meshPrimCount = 0;
}



meshStream ::~meshStream() {
    delete   vaoPtr;
    delete   vboPtr;
    delete   iboPtr;
    delete[] vertArray;
}