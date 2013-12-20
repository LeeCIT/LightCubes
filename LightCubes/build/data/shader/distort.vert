
// GL 3
#version 330

uniform mat4 matProj  = mat4(1.0);
uniform mat4 matView  = mat4(1.0);
uniform mat4 matModel = mat4(1.0);

uniform float distortionLevel = 1.0;

in vec3 inPosition;
in vec4 inDiffuse;

out vec4 position;
out vec4 diffuse;



vec3 lerp( in vec3 a, in vec3 b, in float f )
{
	return a + (b-a) * vec3(f);
}



void main()
{
	mat4 matMVP = matProj * matView * matModel;

	vec3 dpos = inPosition;
		 dpos.z *= sin(dpos.y) * sin(dpos.x);
	     dpos.y *= sin(dpos.z) * cos(dpos.x);
		 dpos.x *= sin(dpos.y) * sin(dpos.x);

	vec3 dist = lerp( inPosition, dpos, distortionLevel );

    position = matMVP * vec4( dist, 1.0 );
	diffuse  = inDiffuse;

	gl_Position = position;
}
