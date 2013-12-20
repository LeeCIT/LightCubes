

#include "colour.h"
#include "func.h"
#include "vec.h"



// Implicit conversion for OpenGL 3fv and 4fv functions.
colour :: operator const float* () const { return (const float*) &(this->r); }
colour :: operator float*       () const { return (float*)       &(this->r); }
colour :: operator const float* ()       { return (const float*) &(this->r); }
colour :: operator float*       ()       { return                &(this->r); }



// Arithmetic operators
const colour& colour::operator += ( const colour &c ) {
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

const colour& colour::operator -= ( const colour &c ) {
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

const colour& colour::operator *= ( const colour &c ) {
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

const colour& colour::operator /= ( const colour &c ) {
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
    return *this;
}

colour operator + ( const colour &a, const colour &b ) { return colour(a) += b; }
colour operator - ( const colour &a, const colour &b ) { return colour(a) -= b; }
colour operator * ( const colour &a, const colour &b ) { return colour(a) *= b; }
colour operator / ( const colour &a, const colour &b ) { return colour(a) /= b; }





// Construct
colour :: colour( float r, float g, float b, float a ) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}



colour :: colour( const vec4& v ) {
    this->r = v.x;
    this->g = v.y;
    this->b = v.z;
    this->a = v.w;
}



colour :: colour() {
    // Do nothing
}





// Predefined colours
const colour  colour::white   = colour( 1.00f, 1.00f, 1.00f );
const colour  colour::gray    = colour( 0.50f, 0.50f, 0.50f );
const colour  colour::black   = colour( 0.00f, 0.00f, 0.00f );
const colour  colour::red     = colour( 1.00f, 0.00f, 0.00f );
const colour  colour::green   = colour( 0.00f, 1.00f, 0.00f );
const colour  colour::blue    = colour( 0.00f, 0.00f, 1.00f );
const colour  colour::lime    = colour( 0.80f, 1.00f, 0.20f );
const colour  colour::orange  = colour( 1.00f, 0.50f, 0.00f );
const colour  colour::yellow  = colour( 1.00f, 1.00f, 0.00f );
const colour  colour::marine  = colour( 0.00f, 0.50f, 1.00f );
const colour  colour::purple  = colour( 0.40f, 0.10f, 0.95f );
const colour  colour::fuschia = colour( 1.00f, 0.00f, 1.00f );





// Functions
colour lerp(  const colour& a,  const colour& b,  float f  ) {
    return a + (b-a) * colour(f,f,f,f);
}