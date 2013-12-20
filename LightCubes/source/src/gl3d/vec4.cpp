

#include "vec4.h"



////////////////////////////
// Cast operators for OpenGL *4fv functions
//////////////////////////

vec4 :: operator       float* ()       { return                &(this->x); }
vec4 :: operator const float* ()       { return (const float*) &(this->x); }
vec4 :: operator       float* () const { return (float*)       &(this->x); }
vec4 :: operator const float* () const { return (const float*) &(this->x); }







/////////////////////////////////////////
// Elementary mathematical operators
//////////////////////////////////////

bool vec4 :: operator == ( const vec4& v ) const {
    return x == v.x
        && y == v.y
        && z == v.z
        && w == v.w;
}



bool vec4 :: operator != ( const vec4& v ) const {
    return ! (*this == v);
}



const vec4&  vec4 :: operator += ( const vec4& b ) {
    x += b.x;
    y += b.y;
    z += b.z;
    w += b.w;
    return *this;
}



const vec4&  vec4 :: operator -= ( const vec4& b ) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    w -= b.w;
    return *this;
}



const vec4&  vec4 :: operator *= ( const vec4& b ) {
    x *= b.x;
    y *= b.y;
    z *= b.z;
    w *= b.w;
    return *this;
}



const vec4&  vec4 :: operator /= ( const vec4& b ) {
    x /= b.x;
    y /= b.y;
    z /= b.z;
    w /= b.w;
    return *this;
}



vec4 vec4 :: operator - () const {
    return vec4( -x, -y, -z, -w );
}







////////////////////////
// Construct
//////////////////////

vec4 :: vec4( float f ) {
    this->x = f;
    this->y = f;
    this->z = f;
    this->w = f;
}



vec4 :: vec4( float x, float y, float z, float w ) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}



vec4 :: vec4( const vec3& v, float fw ) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = fw;
}



vec4 :: vec4( const vec2& v ) {  // explicit
    this->x = v.x;
    this->y = v.y;
    this->z = 0.0f;
    this->w = 1.0f;
}



vec4 :: vec4( const vec3& v ) {  // explicit
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = 1.0f;
}



vec4 :: vec4( const vec2& xy, const vec2& zw ) { // explicit
    this->x = xy.x;
    this->y = xy.y;
    this->z = zw.x;
    this->w = zw.y;
}



vec4 :: vec4() {
    // Do nothing
}







////////////////////////////
// Non-member overloads
//////////////////////////

vec4 operator + ( const vec4 &a, const vec4 &b ) { return vec4(a) += b; }
vec4 operator - ( const vec4 &a, const vec4 &b ) { return vec4(a) -= b; }
vec4 operator * ( const vec4 &a, const vec4 &b ) { return vec4(a) *= b; }
vec4 operator / ( const vec4 &a, const vec4 &b ) { return vec4(a) /= b; }