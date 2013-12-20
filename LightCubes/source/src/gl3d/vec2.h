

// 2D vector class.
// Same properties as vec3.  Can be used with GL 2fv functions etc.

#pragma once



class vec2
{
  public:
    float x,y;

    operator       float* ();
    operator const float* ();
    operator       float* () const;
    operator const float* () const;

    bool operator == ( const vec2& v ) const;
    bool operator != ( const vec2& v ) const;

    const vec2& operator += (  const vec2& b  );
    const vec2& operator -= (  const vec2& b  );
    const vec2& operator *= (  const vec2& b  );
    const vec2& operator /= (  const vec2& b  );
          vec2  operator  - () const;
    
    vec2( float f );
    vec2( float x, float y );
    vec2();
};



// Non-member overloads.
vec2 operator + (  const vec2& a,  const vec2& b  );
vec2 operator - (  const vec2& a,  const vec2& b  );
vec2 operator * (  const vec2& a,  const vec2& b  );
vec2 operator / (  const vec2& a,  const vec2& b  );