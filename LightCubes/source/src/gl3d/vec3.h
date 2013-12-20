

// 3D vector class.
// Can be used directly with OpenGL 3fv functions.
// Floats can be implicitly widened to vec3, so a float can be used for vec3 parameters.
// Vec2s can be 

#pragma once
#include "vec2.h"



class vec3
{
  public:
    float x,y,z;

    operator       float* ();
    operator const float* ();
    operator       float* () const;
    operator const float* () const;

    bool operator == ( const vec3& v ) const;
    bool operator != ( const vec3& v ) const;

    const vec3& operator += (  const vec3& b  );
    const vec3& operator -= (  const vec3& b  );
    const vec3& operator *= (  const vec3& b  );
    const vec3& operator /= (  const vec3& b  );
          vec3  operator  - () const; // Unary negate
    
    
    vec3( float f );
    vec3( float x, float y, float z );
    vec3( const vec2& v, float f );
    vec3( float f, const vec2& v );
    vec3();

    explicit vec3( const vec2& v );
};



// Non-member overloads.
vec3 operator + (  const vec3& a,  const vec3& b  );
vec3 operator - (  const vec3& a,  const vec3& b  );
vec3 operator * (  const vec3& a,  const vec3& b  );
vec3 operator / (  const vec3& a,  const vec3& b  );