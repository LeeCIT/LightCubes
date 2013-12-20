

#include "vertex.h"



vertex :: vertex( const vec3& p, const vec3& n, const vec2& t, const colour& d, const colour& s ) {
    pos      = p;
    norm     = n;
    tex      = t;
    diffuse  = d;
    specular = s;
}



vertex :: vertex() {
     // Do nothing
 }