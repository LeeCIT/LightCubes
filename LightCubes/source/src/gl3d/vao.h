

// VAO - Vertex Array Object
// When bound, the various array states are stored in the VAO.
// To redraw from the same buffers again, you simply bind the VAO again and draw.

// Retains:
//  - Attribute pointers and the associated VBO for each pointer
//  - Attribute enable status
//  - GL_ELEMENT_ARRAY_BUFFER binding

// VAOs DO NOT retain the GL_ARRAY_BUFFER binding.  It's important to realise that
// it's actually the pointers which have a VBO association, not the bare VAO.

#pragma once
#include "glCore.h"
#include "ibo.h"
#include "vbo.h"



namespace gl
{
    class vao
    {
      public:
        static void setAttribPointers();
        static void enableAttribArrays();


      private:
        GLuint handle;


      public:
        operator GLuint() const;

        vao( const vbo& rVbo, const ibo& rIbo );
        vao( const vbo& rVbo );
        vao();
       ~vao();
    };
};