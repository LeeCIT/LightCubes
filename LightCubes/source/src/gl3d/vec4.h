

// 4D vector class.

#pragma once
#include "vec2.h"
#include "vec3.h"



class vec4
{
  public:
    float x,y,z,w;

    operator       float* ();
    operator const float* ();
    operator       float* () const;
    operator const float* () const;

    bool operator == ( const vec4& v ) const;
    bool operator != ( const vec4& v ) const;

    const vec4& operator += (  const vec4& b  );
    const vec4& operator -= (  const vec4& b  );
    const vec4& operator *= (  const vec4& b  );
    const vec4& operator /= (  const vec4& b  );
          vec4  operator  - () const;
    
    vec4();
    vec4( float f );
    vec4( float x, float y, float z, float w );
    vec4( const vec3& v, float w );
    vec4( const vec2& v, float z, float w );
    

    explicit vec4( const vec2& v );
    explicit vec4( const vec3& v );
    explicit vec4( const vec2& xy, const vec2& zw );
};



// Non-member overloads.
vec4 operator + (  const vec4& a,  const vec4& b  );
vec4 operator - (  const vec4& a,  const vec4& b  );
vec4 operator * (  const vec4& a,  const vec4& b  );
vec4 operator / (  const vec4& a,  const vec4& b  );