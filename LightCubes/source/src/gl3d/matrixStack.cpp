

#include "matrixStack.h"
#include <cassert>



/////////////////
// Stack ops
///////////////

void matrixStack::push() {
    assert( ! core.empty() );
    core.push( core.top() );
}



void matrixStack::pop() {
    assert( core.size() > 1 );
    core.pop();
}



mat4& matrixStack::top() {
    assert( !core.empty() );
    return core.top();
}





//////////////////////
// Operators
////////////////////

matrixStack :: operator mat4& () {
    return top();
}



const mat4& matrixStack :: operator *= ( const mat4& mat ) {
    return top() *= mat;
}



const mat4& matrixStack :: operator = ( const mat4& mat ) {
    return top() = mat;
}





///////////////////
// Transform ops
/////////////////

void matrixStack::identity() {
    top() = mat4::identity();
}



void matrixStack::rotateX( float angle ) {
    top() *= mat4::rotateX( angle );
}



void matrixStack::rotateY( float angle ) {
    top() *= mat4::rotateY( angle );
}



void matrixStack::rotateZ( float angle ) {
    top() *= mat4::rotateZ( angle );
}



void matrixStack::rotate( float angle, const vec3& unitAxis ) {
    top() *= mat4::rotate( angle, unitAxis );
}



void matrixStack::orient( const vec3& unitAxis ) {
    top() *= mat4::orient( unitAxis );
}



void matrixStack::scale( const vec3& v ) {
    top() *= mat4::scale( v );
}



void matrixStack::translate( const vec3& v ) {
    top() *= mat4::translate( v );
}



void matrixStack::scale( float x, float y, float z ) {
    top() *= mat4::scale( vec3(x,y,z) );
}



void matrixStack::translate( float x, float y, float z ) {
    top() *= mat4::translate( vec3(x,y,z) );
}





/////////////////
// Construct
///////////////

// Initialise to identity.
matrixStack::matrixStack() {
    core.push( mat4::identity() );
}



matrixStack::~matrixStack() {
    // Do nothing
}