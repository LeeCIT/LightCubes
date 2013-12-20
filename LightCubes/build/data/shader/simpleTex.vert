
// GL 3
#version 330

uniform mat4 modelView  = mat4(1.0);
uniform mat4 projection = mat4(1.0);

in vec3 inPosition;
in vec2 inTexCoord;
in vec4 inDiffuse;

out vec4 position;
out vec2 texCoord;
out vec4 diffuse;

void main()
{
	mat4 matMVP = projection * modelView;

    position = matMVP * vec4( inPosition, 1.0 );
	texCoord = inTexCoord;
	diffuse  = inDiffuse;

	gl_Position = position;
}
