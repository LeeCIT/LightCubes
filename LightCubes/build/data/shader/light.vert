

#version 330



// Matrices
uniform mat4 matProj  = mat4(1.0);
uniform mat4 matView  = mat4(1.0);
uniform mat4 matModel = mat4(1.0);

// Light uniforms
uniform vec3 dirLightWorldVec;
uniform vec3 pointLightWorldPos;
uniform vec3 spotLightWorldPos;
uniform vec3 spotLightWorldVec;
uniform vec3 lineLightWorldPosA;
uniform vec3 lineLightWorldPosB;

// Attribs
in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;

// Interp -> FS
out vec4 position;
out vec3 normal;
out vec2 texCoord;
out vec4 dirLightEyeVec;
out vec4 pointLightEyePos;
out vec4 spotLightEyePos;
out vec4 spotLightEyeVec;
out vec4 lineLightEyePosA;
out vec4 lineLightEyePosB;





void main()
{
	mat4 matMV   = matView * matModel;
	mat4 matMVP  = matProj * matMV;
	mat3 matNorm = inverse( transpose( mat3(matMV) ) );
	
	normal   = matNorm * normalize( inNormal );
    position = matMV   * vec4( inPosition, 1.0 );
	texCoord = inTexCoord;

	dirLightEyeVec   = matView * vec4( dirLightWorldVec,   0.0 ); // No translation for orientations!
	pointLightEyePos = matView * vec4( pointLightWorldPos, 1.0 );
	spotLightEyePos  = matView * vec4( spotLightWorldPos,  1.0 );
	spotLightEyeVec  = matView * vec4( spotLightWorldVec,  0.0 );
	lineLightEyePosA = matView * vec4( lineLightWorldPosA, 1.0 );
	lineLightEyePosB = matView * vec4( lineLightWorldPosB, 1.0 );
	
	gl_Position = matMVP * vec4( inPosition, 1.0 ); // To clip-space
}

















