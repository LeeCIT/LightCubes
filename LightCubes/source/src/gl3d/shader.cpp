

#include "shader.h"
#include "file.h"
#include <iostream>



namespace gl
{

    /////////////////////////////////////////////////
    // Shader 
    //////////////////////////////////////////////

    shader :: operator GLuint() const {
        return handle;
    }



    shader :: shader( const string& name, const shaderType& type ) {
        // File extension
        string extension;

        // Create appropriate shader type.
        switch (type) {
            case shader::typeVert:
                this->handle = glCreateShader( GL_VERTEX_SHADER );
                extension    = ".vert";
                break;

            case shader::typeFrag:
                this->handle = glCreateShader( GL_FRAGMENT_SHADER );
                extension    = ".frag";
                break;
            
            default:
                std::cerr << "Unknown shader type '" << type 
                          << "' given for shader '" << name << "'\n\n";
        }

        // Load source from drive
        const string fileName   = def::dirShader + name + extension;
        const string sourceCode = fileSys::read( fileName );
        const char*  sourcePtr  = sourceCode.c_str();
        glShaderSource( *this, 1, &sourcePtr, nullptr );

        // Compile
        glCompileShader( *this );


        // Check if everything went well, and if there's any log output.
        int compileGood;
        int logLength;
        glGetShaderiv( *this, GL_COMPILE_STATUS,  &compileGood );
        glGetShaderiv( *this, GL_INFO_LOG_LENGTH, &logLength   );

        // If present, output log on standard error stream.
        if (!compileGood  ||  logLength > 1) { // +1 for \0
            if (!compileGood)
                 std::cerr << "SHADER COMPILE ERROR";
            else std::cerr << "SHADER COMPILE MESSAGE";

            std::cerr << " for shader '" << name << extension << "'\n"
                      << "Log:\n";

            char* logPtr = new char[logLength];
                glGetShaderInfoLog( *this, logLength, nullptr, logPtr );
                std::cerr << logPtr << "\n\n\n";
            delete[] logPtr;
        }
    }



    shader ::~shader () {
        glDeleteShader( handle );
    }




    




    /////////////////////////////////////////////////
    // ShaderProgram
    //////////////////////////////////////////////

    ///////////////////////////
    // Set uniform (single)
    /////////////////////////

    // Set single integer (IE a sampler index)
    void shaderProgram :: setUniform( const char* name, const GLint& ind ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform1i( loc, ind );
    }



    void shaderProgram :: setUniform( const char* name, const float& f ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform1f( loc, f );
    }



    void shaderProgram :: setUniform( const char* name, const vec2& vec ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform2fv( loc, 1, vec );
    }


    
    void shaderProgram :: setUniform( const char* name, const vec3& vec ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform3fv( loc, 1, vec );
    }



    void shaderProgram :: setUniform( const char* name, const vec4& vec ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform4fv( loc, 1, vec );
    }



    void shaderProgram :: setUniform( const char* name, const colour& col ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform4fv( loc, 1, col );
    }



    void shaderProgram :: setUniform( const char* name, const mat4& mat ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniformMatrix4fv( loc, 1, false, mat );
    }



    ///////////////////////////
    // Set uniform (array)
    /////////////////////////

    void shaderProgram :: setUniform( const char* name, int ind[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform1iv( loc, count, ind );
    }



    void shaderProgram :: setUniform( const char* name, float f[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform1fv( loc, count, f );
    }



    void shaderProgram :: setUniform( const char* name, vec2 vec[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform2fv( loc, count, *vec );
    }


    
    void shaderProgram :: setUniform( const char* name, vec3 vec[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform3fv( loc, count, *vec );
    }



    void shaderProgram :: setUniform( const char* name, vec4 vec[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform4fv( loc, count, *vec );
    }



    void shaderProgram :: setUniform( const char* name, colour col[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniform4fv( loc, count, *col );
    }



    void shaderProgram :: setUniform( const char* name, mat4 mat[], int count ) {
        auto loc = glGetUniformLocation( *this, name );
        glUniformMatrix4fv( loc, count, false, *mat );
    }



    // Set all material uniforms
    void shaderProgram :: setMaterial( const material& mtr ) {
        setUniform( "mtrAmbient",  mtr.ambient  );
        setUniform( "mtrDiffuse",  mtr.diffuse  );
        setUniform( "mtrSpecular", mtr.specular );
        setUniform( "mtrShine",    mtr.shine    );
    }



    shaderProgram :: operator GLuint () const {
        return handle;
    }



    void shaderProgram :: construct( const string& nameVert, const string& nameFrag ) {
        // Function common to both constructors.

        // Create program
        this->handle = glCreateProgram();

        // Instantiate shaders
        this->shaders.push_back( new shader( nameVert, shader::typeVert ) );
        this->shaders.push_back( new shader( nameFrag, shader::typeFrag ) );

        // Attach
        for (size_t i=0; i<shaders.size(); i++)
            glAttachShader( *this, *(shaders[i]) );
        
        // Bind attributes to the shader.
        // The 'in' variables in the vertex shader must be named this way, if present.
        glBindAttribLocation( *this, attribLocPosition, "inPosition" );
        glBindAttribLocation( *this, attribLocNormal,   "inNormal"   );
        glBindAttribLocation( *this, attribLocTexCoord, "inTexCoord" );
        glBindAttribLocation( *this, attribLocDiffuse,  "inDiffuse"  );
        glBindAttribLocation( *this, attribLocSpecular, "inSpecular" );

        // Link
        glLinkProgram( *this );


        // Check if everything went well.
        int linkGood;
        int logLength;
        glGetProgramiv( *this, GL_LINK_STATUS,     &linkGood  );
        glGetProgramiv( *this, GL_INFO_LOG_LENGTH, &logLength );

        // Output log on standard error stream.
        if (!linkGood  || logLength > 1) {
            if (!linkGood)
                 std::cerr << "SHADER-PROGRAM LINK ERROR";
            else std::cerr << "SHADER-PROGRAM LINK MESSAGE";
            
            std::cerr << " for shader program with:\n"
                      << "- Vert: '" << nameVert << "'\n"
                      << "- Frag: '" << nameFrag << "'\n"
                      << "Log:\n";

            char* logPtr = new char[logLength];
                glGetProgramInfoLog( *this, logLength, nullptr, logPtr );
                std::cerr << logPtr << "\n\n\n";
            delete[] logPtr;
        }
    }



    shaderProgram :: shaderProgram( const string& name ) {
        construct( name, name );
    }



    shaderProgram :: shaderProgram( const string& nameVert, const string& nameFrag ) {
        construct( nameVert, nameFrag );
    }



    shaderProgram :: ~shaderProgram() {
        for (size_t i=0; i<shaders.size(); i++) {
            glDetachShader( handle, *(shaders[i]) );
            delete shaders[i];
        }

        glDeleteProgram( handle );
    }

};