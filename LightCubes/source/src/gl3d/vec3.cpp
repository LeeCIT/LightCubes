

#include "vec3.h"



////////////////////////////
// Cast operators for OpenGL *3fv functions
//////////////////////////

vec3 :: operator       float* ()       { return                &(this->x); }
vec3 :: operator const float* ()       { return (const float*) &(this->x); }
vec3 :: operator       float* () const { return (float*)       &(this->x); }
vec3 :: operator const float* () const { return (const float*) &(this->x); }







/////////////////////////////////////////
// Elementary mathematical operators
//////////////////////////////////////

bool vec3 :: operator == ( const vec3& v ) const {
    return x == v.x
        && y == v.y
        && z == v.z;
}



bool vec3 :: operator != ( const vec3& v ) const {
    return ! (*this == v);
}



const vec3&  vec3 :: operator += ( const vec3& b ) {
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
}



const vec3&  vec3 :: operator -= ( const vec3& b ) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
}



const vec3&  vec3 :: operator *= ( const vec3& b ) {
    x *= b.x;
    y *= b.y;
    z *= b.z;
    return *this;
}



const vec3&  vec3 :: operator /= ( const vec3& b ) {
    x /= b.x;
    y /= b.y;
    z /= b.z;
    return *this;
}



vec3 vec3 :: operator - () const {
    return vec3( -x, -y, -z );
}







////////////////////////
// Construct
//////////////////////

vec3 :: vec3( float f ) {
    this->x = f;
    this->y = f;
    this->z = f;
}



vec3 :: vec3( float x, float y, float z ) {
    this->x = x;
    this->y = y;
    this->z = z;
}



vec3 :: vec3( const vec2& v, float f ) {
    this->x = v.x;
    this->y = v.y;
    this->z = f;
}



vec3 :: vec3( const vec2& v ) { // explicit
    this->x = v.x;
    this->y = v.y;
    this->z = 0.0f;
}



vec3 :: vec3() {
    // Do nothing
}







////////////////////////////
// Non-member overloads
//////////////////////////

vec3 operator + ( const vec3 &a, const vec3 &b ) { return vec3(a) += b; }
vec3 operator - ( const vec3 &a, const vec3 &b ) { return vec3(a) -= b; }
vec3 operator * ( const vec3 &a, const vec3 &b ) { return vec3(a) *= b; }
vec3 operator / ( const vec3 &a, const vec3 &b ) { return vec3(a) /= b; }