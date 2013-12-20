
// GL 3
#version 330

uniform mat4 matProj  = mat4(1.0);
uniform mat4 matView  = mat4(1.0);
uniform mat4 matModel = mat4(1.0);

in vec3 inPosition;
in vec4 inDiffuse;

out vec4 position;
out vec4 diffuse;

void main()
{
	mat4 matMVP = matProj * matView * matModel;

    position = matMVP * vec4( inPosition, 1.0 );
	diffuse  = inDiffuse;

	gl_Position = position;
}
