

// GLSL shaders.
// Construction is abstracted away into classes.  Usage isn't.


#pragma once
#include "colour.h"
#include "def.h"
#include "glCore.h"
#include "mat4.h"
#include "material.h"
#include "vec.h"
#include <string>
#include <vector>



namespace gl
{
    using std::string;
    using std::vector;


    
    // Shader.
    // Automatically constructed by shaderProgram class.
    class shader 
    {
       friend class shaderProgram; // SP can access private members


       private:
         enum shaderType{ typeVert, typeFrag };

         GLuint handle;

         shader( const string& fileName, const shaderType& type );
        ~shader();


       public:
         operator GLuint() const;
    };





    // Shader program.
    // Use directly in glUseProgram().
    class shaderProgram
    {
       public:
         // Attribute indices
         static const enum: GLuint {
             attribLocPosition,
             attribLocNormal,
             attribLocTexCoord,
             attribLocDiffuse,
             attribLocSpecular,
             attribLocCount // Number of attribs.
         };


       private:
         vector<shader*> shaders;
         GLuint handle;
       
         void construct( const string& nameVert, const string& nameFrag );


       public:
         void setUniform ( const char* name, const GLint&  ind );
         void setUniform ( const char* name, const float&  f   );
         void setUniform ( const char* name, const vec2&   vec );
         void setUniform ( const char* name, const vec3&   vec );
         void setUniform ( const char* name, const vec4&   vec );
         void setUniform ( const char* name, const colour& col );
         void setUniform ( const char* name, const mat4&   mat );
         void setUniform ( const char* name, GLint  ind[], int count );
         void setUniform ( const char* name, float  f  [], int count );
         void setUniform ( const char* name, vec2   vec[], int count );
         void setUniform ( const char* name, vec3   vec[], int count );
         void setUniform ( const char* name, vec4   vec[], int count );
         void setUniform ( const char* name, colour col[], int count );
         void setUniform ( const char* name, mat4   mat[], int count );
         void setMaterial( const material& mtr );
       
         operator GLuint() const;

         shaderProgram( const string& nameVert, const string& nameFrag );
         shaderProgram( const string& name );
        ~shaderProgram();
    };
};