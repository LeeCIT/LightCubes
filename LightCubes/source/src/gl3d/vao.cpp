

#include "vao.h"
#include "shader.h"



namespace gl
{
    void vao :: setAttribPointers() {
        /*
           Configures OpenGL to understand my interleaved vertex type.
           See also shaderProgram::attribLoc which defines the shader attribute
           locations.
        
           How the actual binding works warrants some explanation. These
           commands affect the currently bound VAO, but they create a linkage
           between the currently bound _VBO_.  Once called, the pointers are
           always associated with that VBO even if it's not bound anymore.
           There is no need to rebind the VBO again when drawing, only the VAO.
           In fact the GL_ARRAY_BUFFER binding isn't even part of the VAO state.
           This also means that it's possible to put attributes into many
           different VBOs and use them all together in a shader.  Interleaving
           as I've done here isn't mandatory.
        */

        // The attrib pointers require fairly low-level code.
        // WARNING: This code assumes all the variables are floats.
        #define ATTR(name) gl::shaderProgram::attribLoc ## name                                // Literal append
        #define MSIZE(member) sizeof( decltype( ((vertex*) nullptr)->member )) / sizeof(float) // Get number of floats in member
        #define MOFFS(member) (void*) offsetof( vertex, member )                               // Get member's relative byte offset
        #define GLVAP(attr,member) glVertexAttribPointer( ATTR(attr), MSIZE(member), GL_FLOAT, false, sizeof(vertex), MOFFS(member) );

            // glVertexAttribPointer
            GLVAP( Position, pos      );
            GLVAP( Normal,   norm     );
            GLVAP( TexCoord, tex      );
            GLVAP( Diffuse,  diffuse  );
            GLVAP( Specular, specular );

        #undef ATTR
        #undef MSIZE
        #undef MOFFS
        #undef GLVAP
    }



    void vao :: enableAttribArrays() {
        // Turns on vertex attributes.  If not enabled, they don't get to the shaders!
        for (int i=0; i<gl::shaderProgram::attribLocCount; i++)
            glEnableVertexAttribArray( i );
    }



    vao :: operator GLuint() const {
        return handle;
    }



    vao :: vao( const vbo& rVbo, const ibo& rIbo ) {
        GLint bindPrev;
        glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &bindPrev );

        glGenVertexArrays( 1, &handle );
        glBindVertexArray( *this );
            glBindBuffer( GL_ARRAY_BUFFER,         rVbo );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, rIbo );
            vao::setAttribPointers();
            vao::enableAttribArrays();
        glBindVertexArray( bindPrev );
    }



    vao :: vao( const vbo& rVbo ) {
        GLint bindPrev;
        glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &bindPrev );

        glGenVertexArrays( 1, &handle );
        glBindVertexArray( *this );
            glBindBuffer( GL_ARRAY_BUFFER, rVbo );
            vao::setAttribPointers();
            vao::enableAttribArrays();
        glBindVertexArray( bindPrev );
    }



    vao :: vao() {
        glGenVertexArrays( 1, &handle );
    }



    vao ::~vao() {
        glDeleteVertexArrays( 1, &handle );
    }
};