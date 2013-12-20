

#include "vec.h"
#include "fast.h"
#include <cmath>



///////////////////////
// 3D
////////////////////

// Component-wise lerp.
vec2 lerp(  const vec2& a,  const vec2& b,  const vec2& f  ) {
    return a + ((b-a) * f);
}



// Vector magnitude.
float length(  const vec2& v  ) {
    return sqrt( dot(v,v) );
}



// Euclidean distance.
float distance(  const vec2& a,  const vec2& b  ) {
    return length( a - b );
}



// Dot product.
float dot(  const vec2& a,  const vec2& b  ) {
    return (a.x * b.x)
         + (a.y * b.y);
}



// Scale a vector to unit length.
vec2 normalise(  const vec2& v  ) {
    return v * approx::rsqrtzero( dot(v,v) );
}







///////////////////////
// 3D
////////////////////

vec3 lerp(  const vec3& a,  const vec3& b,  const vec3& f  ) {
    return a + ((b-a) * f);
}



float length(  const vec3& v  ) {
    return sqrt( dot(v,v) );
}



float distance(  const vec3& a,  const vec3& b  ) {
    return length( a - b );
}



float dot(  const vec3& a,  const vec3& b  ) {
    return (a.x * b.x)
         + (a.y * b.y)
         + (a.z * b.z);
}



vec3 cross(  const vec3& a,  const vec3& b  ) {
    return vec3( (a.y * b.z) - (a.z * b.y),
                 (a.z * b.x) - (a.x * b.z),
                 (a.x * b.y) - (a.y * b.x) );
}



vec3 normalise(  const vec3& v  ) {
    return v * approx::rsqrtzero( dot(v,v) );
}








///////////////////////
// 4D
////////////////////

vec4 lerp(  const vec4& a,  const vec4& b,  const vec4& f  ) {
    return a + ((b-a) * f);
}



float length(  const vec4& v  ) {
    return sqrt( dot(v,v) );
}



float distance(  const vec4& a,  const vec4& b  ) {
    return length( a - b );
}



float dot(  const vec4& a,  const vec4& b  ) {
    return (a.x * b.x)
         + (a.y * b.y)
         + (a.z * b.z)
         + (a.w * b.w);
}



vec4 normalise(  const vec4& v  ) {
    return v * approx::rsqrtzero( dot(v,v) );
}