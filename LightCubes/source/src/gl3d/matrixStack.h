

// Matrix stack
// Performs the functions that glPushMatrix etc used to.
// Matrix stacks are initialised to the identity matrix.

#pragma once
#include "mat4.h"
#include "stack.h"



class matrixStack
{
  private:
    stack<mat4> core;


  public:
    void  push(); // Store
    void  pop();  // Restore
    mat4& top();  // Reference current matrix

    operator mat4& ();

    const mat4& operator *= ( const mat4& mat );
    const mat4& operator  = ( const mat4& mat );

    void identity ();
    void rotateX  ( float angle );
    void rotateY  ( float angle );
    void rotateZ  ( float angle );
    void rotate   ( float angle, const vec3& unitAxis );
    void orient   ( const vec3& unitAxis );
    void scale    ( const vec3& v );
    void scale    ( float x, float y, float z );
    void translate( const vec3& v );
    void translate( float x, float y, float z );

    matrixStack();
   ~matrixStack();
};