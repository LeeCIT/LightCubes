

// General-purpose functions

#pragma once



float lerp  ( float a, float b, float f );
void  lerpTo( float& modify, float to, float f );
float unlerp( float v, float minv, float maxv );
float clamp ( float x, float minv, float maxv );
float clamp ( float x, float minv, float maxv );
float sqr   ( float x );
float sign  ( float x );

float distanceSqr( float x1, float y1, float x2, float y2 );
float distance   ( float x1, float y1, float x2, float y2 );

float angleDiff   ( float a, float b );
float angleLerp   ( float a, float b, float f );
float angleLerpLim( float a, float b, float f, float maxDelta );

float degToRad( float degrees );
float radToDeg( float radians );

float sineSync( double input, double period );



void toggle( bool& ref );