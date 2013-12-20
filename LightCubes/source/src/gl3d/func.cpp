

#include "func.h"
#include "def.h"
#include "fast.h"
#include <cmath>
#include <algorithm>



// Linear interpolation from A to B by fraction F.
float lerp( float a, float b, float f ) {
    return a + ((b-a) * f);
}





// Lerp an existing value toward another one.
// Makes code clearer sometimes.
// Equivalent to: a = lerp( a, b, f );
void lerpTo( float& modify, float to, float f ) {
    modify = lerp( modify, to, f );
}





// Inverse of lerp().  Given the output V and input
// range MINV,MAXV, compute the lerp fraction needed
// to get V.  This can also be used to normalise any
// linear range into (0,1).
float unlerp( float v, float minv, float maxv ) {
    return (v - minv)  /  (maxv - minv);
}





// Clamp to inclusive range.
float clamp( float x, float minv, float maxv ) {
    using std::min;
    using std::max;

    return min( maxv, max(x,minv) );
}





// Square.
float sqr( float x ) {
    return x * x;
}





// Float sign (-1, 0, +1).
// Booleans evaluate to 0 or 1, hence the brevity.
float sign( float x ) {
    return float(  (x > 0) - (x < 0)  );
}





// Euclidean distance squared.
float distanceSqr( float x1, float y1, float x2, float y2 ) {
	return sqr(x1-x2) + sqr(y1-y2);
}





// Euclidean distance.
float distance( float x1, float y1, float x2, float y2 ) {
    return sqrt( distanceSqr(x1,y1, x2,y2) );
}





// Normalised angular difference in range (-180,+180).
// Result is negative if B is anticlockwise with respect to A.
// Order of comparison affects the sign, but the absolute
// value is the same either way.
float angleDiff( float a, float b ) {
    float mod360 = fmod( a-b, 360.0f );
    return fmod( mod360+540.0f, 360.0f ) - 180.0f;
}





// Lerp between angles along the shortest arc between them.
float angleLerp( float a, float b, float f ) {
    return a + (angleDiff(b,a) * f);
}





// Same as before, except the angular change can be constrained.
// This makes it easier to animate rotations.
float angleLerpLim( float a, float b, float f, float maxDelta ) {
    float delta = clamp( angleDiff(b,a), -maxDelta, +maxDelta );
    return a + (delta * f);
}





// Convert degrees to radians.
float degToRad( float degrees ) {
    return degrees * (def::pi / 180.0f);
}





// Convert radians to degrees.
float radToDeg( float radians ) {
    return radians * (180.0f / def::pi);
}





// Transforms a linear sequence into a sinewave.
// Waveform: One dip and rise per period, zero at edges and centre of period.
// Range:    -1 to +1 inclusive.
float sineSync( double input, double period ) {
    double half = period * 0.5;
    double mod  = fmod( input, period ) - half;
    float  pm1  = float( mod / half );

    return approx::sin( pm1 * def::pi );
}





void toggle( bool& b ) {
    b = !b;
}