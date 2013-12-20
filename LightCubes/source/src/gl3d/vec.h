

// Vector functions
// Include to get all vector types and their functionality.

#pragma once
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"



vec2  lerp     ( const vec2& a, const vec2& b, const vec2& f );
float length   ( const vec2& v );
float distance ( const vec2& a, const vec2& b );
float dot      ( const vec2& a, const vec2& b );
vec2  normalise( const vec2& v );



vec3  lerp     ( const vec3& a, const vec3& b, const vec3& f );
float length   ( const vec3& v );
float distance ( const vec3& a, const vec3& b );
float dot      ( const vec3& a, const vec3& b );
vec3  cross    ( const vec3& a, const vec3& b );
vec3  normalise( const vec3& v );



vec4  lerp     ( const vec4& a, const vec4& b, const vec4& f );
float length   ( const vec4& v );
float distance ( const vec4& a, const vec4& b );
float dot      ( const vec4& a, const vec4& b );
vec4  normalise( const vec4& v );