
// GL 3
#version 330

uniform mat4 matProj  = mat4(1.0);
uniform mat4 matView  = mat4(1.0);
uniform mat4 matModel = mat4(1.0);

in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;
in vec4 inDiffuse;
in vec4 inSpecular;

out vec4 position;
out vec3 normal;
out vec2 texCoord;
out vec4 diffuse;
out vec4 specular;

void main()
{
	mat4 matMV     = matView * matModel;
	mat4 matMVP    = matProj * matMV;
	mat3 matNormal = inverse( transpose( mat3(matMV) ) );

    position = matMVP    * vec4( inPosition, 1.0 );
	normal   = matNormal * inNormal;
	texCoord = inTexCoord;
	diffuse  = inDiffuse;
	specular = inSpecular;

	gl_Position = position; // Mandatory.
}
