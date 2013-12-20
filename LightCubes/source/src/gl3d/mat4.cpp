

#include "mat4.h"
#include "func.h"
#include <cassert>
#include <cmath>
#include <memory>







/////////////////////////
// Transforms
///////////////////////                      

const mat4 mat4::ident = mat4( 1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1 );

const mat4& mat4::identity() {
    return ident;
}



mat4 mat4::rotateX( float angle ) {
    const float r = degToRad( angle );
    const float c = cos( r );
    const float s = sin( r );

    return mat4( 1, 0, 0, 0,
                 0, c,-s, 0,
                 0, s, c, 0,
                 0, 0, 0, 1 );
}



mat4 mat4::rotateY( float angle ) {
    const float r = degToRad( angle );
    const float c = cos( r );
    const float s = sin( r );

    return mat4( c, 0, s, 0,
                 0, 1, 0, 0,
                -s, 0, c, 0,
                 0, 0, 0, 1 );
}



mat4 mat4::rotateZ( float angle ) {
    const float r = degToRad( angle );
    const float c = cos( r );
    const float s = sin( r );

    return mat4( c,-s, 0, 0,
                 s, c, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1 );
}



// Rotate around an axis defined by a unit vector.
// Source: http://www.opengl.org/sdk/docs/man2/xhtml/glRotate.xml
mat4 mat4::rotate( float angle, const vec3& axis ) {
    vec3 unitAxis = normalise( axis );

    const float r  = degToRad( angle );
    const float c  = cos( r );
    const float s  = sin( r );
    const float ci = 1.0f - c;

    const float x  = unitAxis.x;
    const float y  = unitAxis.y;
    const float z  = unitAxis.z;
    const vec3  sq = unitAxis * unitAxis;
    const vec3  d  = c + (sq * ci);
    
    return mat4( d.x,         x*y*ci-z*s,  x*z*ci+y*s,
                 x*y*ci+z*s,  d.y,         y*z*ci-x*s,
                 x*z*ci-y*s,  z*y*ci+x*s,  d.z         );
}



// Construct a rotation matrix from a unit vector.
// The object's -z axis will be oriented the same as the vector.
mat4 mat4::orient( const vec3& axis ) {
    const vec3 up = vec3(0,1,0);
    const vec3 n  = normalise( axis );        // Forward (given)
    const vec3 u  = normalise( cross(up,n) ); // Side
    const vec3 v  = normalise( cross(n, u) ); // Relative up

    // Transposed
    return mat4( u.x,  v.x,  n.x,   0,
                 u.y,  v.y,  n.y,   0,
                 u.z,  v.z,  n.z,   0,
                   0,    0,    0,   1 );
}



mat4 mat4::scale( const vec3& v ) {
    return mat4( v.x, 0,   0,   0,
                 0,   v.y, 0,   0,
                 0,   0,   v.z, 0,
                 0,   0,   0,   1 );
}



mat4 mat4::translate( const vec3& v ) {
    return mat4( 1, 0, 0, v.x,
                 0, 1, 0, v.y,
                 0, 0, 1, v.z,
                 0, 0, 0, 1 );
}



// Construct orthographic projection matrix.
// Source: http://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
mat4 mat4::ortho( float left, float right, float bottom, float top, float znear, float zfar ) {
    const vec3 pos   = vec3( right, top,    znear ); // Positive edge
    const vec3 neg   = vec3( left,  bottom, zfar  ); // Negative edge
    const vec3 sum   = pos + neg;
    const vec3 delta = pos - neg;
    const vec3 t     = -(sum / delta); // Translation
    const vec3 s     = 2.0f / delta;   // Scaling

    return mat4( s.x, 0,   0,   t.x,
                 0,   s.y, 0,   t.y,
                 0,   0,   s.z, t.z,
                 0,   0,   0,   1 );
}



// Construct perspective projection matrix.
// Source: http://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
mat4 mat4::perspective( float vFov, float aspect, float znear, float zfar ) {
    assert( znear > 0.0f  );
    assert( zfar  > 0.0f  );
    assert( zfar  > znear );

    const float rads = degToRad( vFov );
    const float f    = 1.0f / tan( rads / 2.0f );
    const float fa   = f / aspect;

    const float zdelta = znear - zfar;
    const float zr     = (zfar + znear)        / zdelta;
    const float t2r    = (2.0f * zfar * znear) / zdelta;

    return mat4( fa, 0,  0,  0,
                 0,  f,  0,  0,
                 0,  0,  zr, t2r,
                 0,  0, -1,  0 );
}



// View matrix.  Produces the exact same matrix as gluLookAt() and camera::viewMatrix().
mat4 mat4::lookAt( const vec3& from, const vec3& to, const vec3& up ) {
    assert( distance(from,to) != 0.0f );
    
    const vec3 n = normalise( from - to );
    const vec3 u = normalise( cross(up,n) );
    const vec3 v = normalise( cross(n, u) );

    return mat4( u.x,  u.y,  u.z,  -dot(from,u),
                 v.x,  v.y,  v.z,  -dot(from,v),
                 n.x,  n.y,  n.z,  -dot(from,n),
                   0,    0,    0,   1 );
}



// Swap rows and columns.
// Changes from column-major to row-major or vice-versa.
// Identity matrix is unchanged.
mat4 mat4::transpose( const mat4& f ) {
    return mat4( f[ 0], f[ 1], f[ 2], f[ 3],
                 f[ 4], f[ 5], f[ 6], f[ 7],
                 f[ 8], f[ 9], f[10], f[11],
                 f[12], f[13], f[14], f[15] );
}





/////////////////////////
// Implicit conversion
///////////////////////

mat4 :: operator       float* ()       {  return m;           }
mat4 :: operator const float* ()       {  return m;           }
mat4 :: operator       float* () const {  return (float*) m;  }
mat4 :: operator const float* () const {  return m;           }





/////////////////////////
// Operators
///////////////////////

const mat4& mat4 :: operator = ( const mat4& other ) {
    memcpy( m, other.m, 64 );
    return *this;
}



const float& mat4 :: operator [] ( const int& index ) const {
    assert( index >= 0 && index < 16 );
    return m[ index ];
}



float& mat4 :: operator [] ( const int& index ) {
    assert( index >= 0 && index < 16 );
    return m[ index ];
}





/////////////////////////
// Internal Operators
///////////////////////

const mat4& mat4 :: operator *= ( const mat4& f ) {
    mat4 r;

    for (int i=0; i<16; i+=4) {
        const int a = i + 0;
        const int b = i + 1;
        const int c = i + 2;
        const int d = i + 3;

        r[a] = f[a]*m[0]  +  f[b]*m[4]  +  f[c]*m[ 8]  +  f[d]*m[12];
        r[b] = f[a]*m[1]  +  f[b]*m[5]  +  f[c]*m[ 9]  +  f[d]*m[13];
        r[c] = f[a]*m[2]  +  f[b]*m[6]  +  f[c]*m[10]  +  f[d]*m[14];
        r[d] = f[a]*m[3]  +  f[b]*m[7]  +  f[c]*m[11]  +  f[d]*m[15];
    }

    return *this = r;
}



const mat4& mat4 :: operator *= ( const float& f ) {
    for (int i=0; i<16; i++)
        m[i] *= f;

    return *this;
}



mat4 operator * ( const mat4& m, const mat4& f ) {
    return mat4(m) *= f;
}





/////////////////////////
// External operators
//////////////////////

mat4 operator * ( const mat4& m, const float& f ) {
    return mat4(m) *= f;
}



mat4 operator * ( const float& f, const mat4& m ) {
    return mat4(m) *= f;
}



vec2 operator * ( const mat4& m, const vec2& v ) {
    return vec2( m[0]*v.x  +  m[4]*v.y  +  m[12],  
                 m[1]*v.x  +  m[5]*v.y  +  m[13] ); 
}



vec3 operator * ( const mat4& m, const vec3& v ) {
    return vec3( m[0]*v.x  +  m[4]*v.y  +  m[ 8]*v.z  +  m[12],
                 m[1]*v.x  +  m[5]*v.y  +  m[ 9]*v.z  +  m[13],
                 m[2]*v.x  +  m[6]*v.y  +  m[10]*v.z  +  m[14] );
}



vec4 operator * ( const mat4& m, const vec4& v ) {
    return vec4( m[0]*v.x  +  m[4]*v.y  +  m[ 8]*v.z  +  m[12]*v.w,
                 m[1]*v.x  +  m[5]*v.y  +  m[ 9]*v.z  +  m[13]*v.w,
                 m[2]*v.x  +  m[6]*v.y  +  m[10]*v.z  +  m[14]*v.w,
                 m[3]*v.x  +  m[7]*v.y  +  m[11]*v.z  +  m[15]*v.w );
}





/////////////////////////
// External functions
///////////////////////
mat4 lerp( const mat4& ma, const mat4& mb, float f ) {
    mat4 r;

    for (int i=0; i<16; i++)
        r[i] = lerp( ma[i], mb[i], f );

    return r;
}





/////////////////////////
// Construct 
///////////////////////

mat4 :: mat4( float x0, float y0, float z0, 
              float x1, float y1, float z1,
              float x2, float y2, float z2 ) {
    m[0] = x0;   m[4] = y0;   m[ 8] = z0;   m[12] = 0;
    m[1] = x1;   m[5] = y1;   m[ 9] = z1;   m[13] = 0;
    m[2] = x2;   m[6] = y2;   m[10] = z2;   m[14] = 0;
    m[3] = 0;    m[7] = 0;    m[11] = 0;    m[15] = 1;
}



mat4 :: mat4( float x0, float y0, float z0, float w0, 
              float x1, float y1, float z1, float w1,
              float x2, float y2, float z2, float w2,
              float x3, float y3, float z3, float w3 ) {
    m[0] = x0;   m[4] = y0;   m[ 8] = z0;   m[12] = w0;
    m[1] = x1;   m[5] = y1;   m[ 9] = z1;   m[13] = w1;
    m[2] = x2;   m[6] = y2;   m[10] = z2;   m[14] = w2;
    m[3] = x3;   m[7] = y3;   m[11] = z3;   m[15] = w3;
}



mat4 :: mat4( float* const v ) {
    *this = *((mat4*) v);
}



mat4 :: mat4( const mat4& other ) {
    *this = other;
}



mat4 :: mat4() {
    // Do nothing
}



mat4 ::~mat4() {
    // Do nothing
}