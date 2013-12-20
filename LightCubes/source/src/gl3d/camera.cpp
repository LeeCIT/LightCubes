

#include "camera.h"
#include "func.h"
#include <cmath>



void camera :: move( const vec3& delta ) {
    pos += delta.x * u
        +  delta.y * v
        +  delta.z * n;
}



void camera :: roll( float angle ) {
    const float rads = degToRad( angle );
    const float c    = cos( rads );
    const float s    = sin( rads );
    
    u = normalise(  c*u + s*v );
    v = normalise( -s*u + c*v );
}



void camera :: pitch( float angle ) {
    const float rads = degToRad( angle );
    const float c    = cos( rads );
    const float s    = sin( rads );
    
    n = normalise(  c*n + s*v );
    v = normalise( -s*n + c*v );
}



void camera :: yaw( float angle ) {
    const float rads = degToRad( angle );
    const float c    = cos( rads );
    const float s    = sin( rads );
    
    n = normalise(  c*n + s*u );
    u = normalise( -s*n + c*u );
}



void camera :: lookAt( const vec3& posFrom,  const vec3& posTo,  const vec3& up ) {
    pos = posFrom;
    n   = normalise( pos - posTo ); // Normal to the projection plane. (direction of view)
    u   = normalise( cross(up,n) ); // Normal to N and Up: points to the side
    v   = normalise( cross(n, u) ); // Normal to N and U: Relative up vector
}



mat4 camera :: viewMatrix() {
    return mat4( u.x,  u.y,  u.z,  -dot(pos,u),
                 v.x,  v.y,  v.z,  -dot(pos,v),
                 n.x,  n.y,  n.z,  -dot(pos,n),
                   0,    0,    0,   1 );
}





///////////////
// Construct
/////////////
camera :: camera( const vec3& posFrom,  const vec3& posTo,  const vec3& up ) {
    lookAt( posFrom, posTo, up );
}



camera :: camera() {
    lookAt(  vec3(0,0,0),  vec3(0,0,-1),  vec3(0,1,0)  );
}



camera ::~camera() {
    // Do nothing
}