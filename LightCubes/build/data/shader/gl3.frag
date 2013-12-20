
// GL 3
#version 330

uniform sampler2D tex;

in vec3 normal;
in vec2 texCoord;
in vec4 diffuse;
in vec4 specular;

out vec4 fragCol;



void main()
{
	// Sample texture
	vec4 texCol = texture( tex, texCoord );

	// Compute simple lighting: light from eye
	vec3  unitNormal = normalize( normal );
	vec3  unitEye    = vec3( 0.0, 0.0, -1.0 );
	float dotNormEye = dot( -unitEye, unitNormal );
	float dotClamp   = max( dotNormEye, 0.0 );

	// Different colours for front and back
	vec4 front = (diffuse * texCol);
	vec4 back  = vec4( 0.2, 0.2, 0.4, 1.0 );

	// Finally, output the colour.
	fragCol  = (dotNormEye>=0.0) ? front : back;
	fragCol *= vec4(dotClamp);
}
