

// Defines two convenient interfaces: vertexStream and meshStream.

// vertexStream: Equivalent to glBegin/End in old versions of OpenGL. Also
//               similar in terms of speed.  Respecifying vertices all the time
//               is relatively slow.

// meshStream:   Similar functionality, but can be redrawn easily and holds
//               multiple primitives.  It's much faster and once finalised
//               does not maintain a CPU-side vertex buffer.

#pragma once
#include "colour.h"
#include "glCore.h"
#include "glObject.h"
#include "vec.h"
#include "vertex.h"
#include <vector>



namespace vertexStreamSys
{
    class streamBase
    {
      protected:
        gl::vao* vaoPtr;      // VA state object
        gl::vbo* vboPtr;      // GPU-side vertex store
        vertex*  vertArray;   // CPU-side vertex store
        size_t   vertIndex;   // Current vertex index in vertArray
        size_t   vertCount;   // Number of vertices that can be drawn
        vertex   vertNext;    // Current vertex data being modified by set* functions
        vertex   vertDefault; // Initial state when beginning a new primitive
        GLint    primType;    // Type of primitive to draw


      public:
        void setNormal  ( const vec3&   norm ); // Set normal for next vertex
        void setTexCoord( const vec2&   tc   ); // ...
        void setColour  ( const colour& col  ); // ...
        void setSpecular( const colour& spec ); // ...

        void setNormal  ( float x, float y, float z );
        void setTexCoord( float x, float y );
        void setColour  ( float r, float g, float b, float a=1.0f );
        void setSpecular( float r, float g, float b, float a=1.0f );

        virtual void emit( const vec3& pos  ); // Emits vertex with the above defined attributes.
        virtual void emit( float x, float y, float z );

                 streamBase();
        virtual ~streamBase();
    };
};





class vertexStream: public vertexStreamSys::streamBase
{
  public:
    size_t getCapacity () const; // Get max vertices (given in constructor) 
    size_t getEmitCount() const; // Get number of vertices emitted since last begin().

    void begin( GLint primitiveType ); // Start a new sequence of vertices.
    void end();                        // Draw the sequence.

    vertexStream( size_t vertexCount=16384 ); // 1MB of vertices by default
   ~vertexStream();
};





class meshStream: public vertexStreamSys::streamBase
{
  private:
    gl::ibo*             iboPtr;
    bool                 isFinal;
    size_t               meshPrimIndex; // Current primitive index
    size_t               meshPrimCount; // Number of primitives
    std::vector<GLint>   meshPrimType;  // Type of nth primitive
    std::vector<GLsizei> meshPrimVerts; // Vertices in nth primitive

    void buildIbo( size_t count );

    
  public:
    size_t getCapacity()       const; // Get max vertices.  When finalised, this is the same as getVertexCount().
    size_t getVertexCount()    const; // Get number of vertices emitted into the stream.
    size_t getPrimitiveCount() const; // Get number of primitives in the stream.
    
    void begin( GLint primitive );
    void end();

    virtual void emit( const vec3& pos );
    virtual void emit( float x, float y, float z );

    void finalise();   // Copies to GPU and removes CPU-side data.  No further changes can be made.
    void draw() const; // Draws the sequence of primitives.
    
    meshStream( size_t vertexCount );
   ~meshStream();
};