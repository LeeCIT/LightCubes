

#include "vec2.h"



////////////////////////////
// Cast operators for OpenGL *2fv functions
//////////////////////////

vec2 :: operator       float* ()       { return                &(this->x); }
vec2 :: operator const float* ()       { return (const float*) &(this->x); }
vec2 :: operator       float* () const { return (float*)       &(this->x); }
vec2 :: operator const float* () const { return (const float*) &(this->x); }







/////////////////////////////////////////
// Elementary mathematical operators
//////////////////////////////////////

bool vec2 :: operator == ( const vec2& v ) const {
    return x == v.x
        && y == v.y;
}



bool vec2 :: operator != ( const vec2& v ) const {
    return ! (*this == v);
}



const vec2&  vec2 :: operator += ( const vec2& b ) {
    x += b.x;
    y += b.y;
    return *this;
}



const vec2&  vec2 :: operator -= ( const vec2& b ) {
    x -= b.x;
    y -= b.y;
    return *this;
}



const vec2&  vec2 :: operator *= ( const vec2& b ) {
    x *= b.x;
    y *= b.y;
    return *this;
}



const vec2&  vec2 :: operator /= ( const vec2& b ) {
    x /= b.x;
    y /= b.y;
    return *this;
}



vec2 vec2 :: operator - () const {
    return vec2( -x, -y );
}







////////////////////////
// Construct
//////////////////////

vec2 :: vec2( float f ) {
    this->x = f;
    this->y = f;
}



vec2 :: vec2( float x, float y ) {
    this->x = x;
    this->y = y;
}



vec2 :: vec2() {
    // Do nothing
}







////////////////////////////
// Non-member overloads
//////////////////////////

vec2 operator + ( const vec2 &a, const vec2 &b ) { return vec2(a) += b; }
vec2 operator - ( const vec2 &a, const vec2 &b ) { return vec2(a) -= b; }
vec2 operator * ( const vec2 &a, const vec2 &b ) { return vec2(a) *= b; }
vec2 operator / ( const vec2 &a, const vec2 &b ) { return vec2(a) /= b; }