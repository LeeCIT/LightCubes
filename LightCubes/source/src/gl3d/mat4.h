

// Matrix 4x4
// Column-major; same memory layout as OpenGL matrices.
// Output is exactly the same as native OpenGL matrix functions.
// Can be used directly in openGL functions and as shader uniforms.

#pragma once
#include "vec.h"



class mat4
{
  private:
    static const mat4 ident;


  public:
    static const mat4& identity();

    static mat4 rotateX  ( float angle );
    static mat4 rotateY  ( float angle );
    static mat4 rotateZ  ( float angle );
    static mat4 rotate   ( float angle, const vec3& axis );
    static mat4 orient   ( const vec3& axis );
    static mat4 scale    ( const vec3& v );
    static mat4 translate( const vec3& v );

    static mat4 lookAt     ( const vec3& posFrom, const vec3& posTo, const vec3& dirUp );
    static mat4 ortho      ( float left, float right, float bottom, float top, float znear=-1.0f, float zfar=+1.0f );
    static mat4 perspective( float vFov, float aspect, float znear, float zfar );

    static mat4 transpose  ( const mat4& f );
    static mat4 inverse3x3 ( const mat4& f );
    static mat4 normal     ( const mat4& f );
    


  private:
    float m[16];
    


  public:
    operator       float* ();
    operator const float* ();
    operator       float* () const;
    operator const float* () const;

    const float& operator [] ( const int& index ) const;
          float& operator [] ( const int& index );

    const mat4& operator  = ( const mat4& other );
    const mat4& operator *= ( const mat4&  f ); // Matrix multiply
    const mat4& operator *= ( const float& f ); // Scalar multiply

    mat4( const mat4& other );

    mat4( float x0, float y0, float z0, 
          float x1, float y1, float z1,
          float x2, float y2, float z2 );

    mat4( float x0, float y0, float z0, float w0, 
          float x1, float y1, float z1, float w1,
          float x2, float y2, float z2, float w2,
          float x3, float y3, float z3, float w3 );

    explicit mat4( float* const v );

    mat4();
   ~mat4();
};





// External operators
mat4 operator * ( const mat4& m, const mat4&  f ); // Order matters!

mat4 operator * ( const mat4&  m, const float& f ); // Order doesn't matter (scalar multiply)
mat4 operator * ( const float& f, const mat4&  m ); // Order doesn't matter (scalar multiply)

vec3 operator * ( const mat4& m, const vec3&  v ); // Order matters, but only the right-hand one is defined anyway.
vec2 operator * ( const mat4& m, const vec2&  v ); // "





// External functions
mat4 lerp( const mat4& ma, const mat4& mb, float f );