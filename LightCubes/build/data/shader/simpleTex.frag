
// GL 3
#version 330

uniform sampler2D tex;

in  vec2 texCoord;
in  vec4 diffuse;
out vec4 fragCol;



void main()
{
	vec4 texCol = texture( tex, texCoord );

	fragCol = diffuse * texCol;
}
