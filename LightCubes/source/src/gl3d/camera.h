

// Camera - Defines the first person camera and generates a view matrix.
// NOTE: I fixed a bug in the given code.  The camera axes must be
//       renormalised once in a while or cumulative floating point
//       rounding errors will denormalise them and distort the view.

#pragma once
#include "mat4.h"



class camera
{
  public:
    vec3 pos; // Viewpoint origin
    vec3 n;   // z/Forward (Normal to projection plane)
    vec3 u;   // x/Side    (Normal to constructor's look/up vectors
    vec3 v;   // y/Up      (Normal to N,U)


  public:
    void move  ( const vec3& delta );
    void roll  ( float angle );
    void pitch ( float angle );
    void yaw   ( float angle );
    void lookAt( const vec3& posFrom,  const vec3& posAt,  const vec3& up );

    mat4 viewMatrix();

    camera( const vec3& posFrom,  const vec3& posAt,  const vec3& up );
    camera();
   ~camera();
};