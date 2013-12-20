

#version 330



// Texture
uniform sampler2D texShine;
uniform sampler2D texColour;

// Material
uniform vec4  mtrAmbient;
uniform vec4  mtrDiffuse;
uniform vec4  mtrSpecular;
uniform float mtrShine;

// Light uniforms
uniform vec4 globalLightAmbient;

uniform vec4 dirLightAmbient;
uniform vec4 dirLightDiffuse;
uniform vec4 dirLightSpecular;

uniform vec4 pointLightAmbient;
uniform vec4 pointLightDiffuse;
uniform vec4 pointLightSpecular;
uniform vec3 pointLightDecay; // [const, linear, quadratic]

uniform float spotLightCone;
uniform float spotLightSoftness;
uniform vec4  spotLightAmbient;
uniform vec4  spotLightDiffuse;
uniform vec4  spotLightSpecular;
uniform vec3  spotLightDecay;

uniform vec4 lineLightAmbient;
uniform vec4 lineLightDiffuse;
uniform vec4 lineLightSpecular;
uniform vec3 lineLightDecay;



// In/out
in  vec4 position;
in  vec3 normal;
in  vec2 texCoord;
in  vec4 dirLightEyeVec;
in  vec4 pointLightEyePos;
in  vec4 spotLightEyePos;
in  vec4 spotLightEyeVec;
in  vec4 lineLightEyePosA;
in  vec4 lineLightEyePosB;
out vec4 fragCol;



///////////////
// Functions
/////////////

float dotZ( in vec3 a, in vec3 b ) {
	return clamp( dot(a,b), 0.0, 1.0 );
}



vec3 nearestPointOnLine( in vec3 point, in vec3 la, in vec3 lb ) {
	vec3  delta   = lb - la;
    float distSqr = dot( delta, delta );
    float t       = dot( point-la, delta ) / distSqr;
	      t       = clamp( t, 0.0, 1.0 );

    return mix( la, lb, vec3(t) );
}



float lightDecay( in float dist, in vec3 decay ) {
	float decayScale = 0.0625;
	dist *= decayScale;

	float factor = (decay.x) + (decay.y * dist) + (decay.z * dist * dist);
	return 1.0 / factor;
}



vec4 computeGlobalLight() {
	return globalLightAmbient * mtrAmbient;
}



vec4 computeDirLight( in vec3 vNorm, in vec3 vView, in float specAmount ) {
	vec3 vLight   = normalize( -dirLightEyeVec.xyz );
	vec3 vHalf    = normalize( vLight + vView );
	
	float dotLN   = dotZ( vLight, vNorm );
	float dotNH   = dotZ( vNorm,  vHalf );
	
	float specIo  = (dotLN > 0.0)  ?  1.0  :  0.0;
	float specPow = pow( dotNH, mtrShine ) * specIo;
	
	vec4 ambient  = dirLightAmbient  * mtrAmbient  * dotLN;
	vec4 diffuse  = dirLightDiffuse  * mtrDiffuse  * dotLN;
	vec4 specular = dirLightSpecular * mtrSpecular * specPow * specAmount;
	vec4 light    = ambient + diffuse + specular;
	
	return light;
}



vec4 computePointLight( in vec3 vNorm, in vec3 vView, in float specAmount ) {
	vec3 vLight   = normalize( pointLightEyePos.xyz - position.xyz );
	vec3 vHalf    = normalize( vLight + vView );
	
	float dotLN   = dotZ( vLight, vNorm );
	float dotNH   = dotZ( vNorm,  vHalf );
	
	float dist    = distance( pointLightEyePos.xyz, position.xyz );
	float decay   = lightDecay( dist, pointLightDecay );
	
	float specIo  = (dotLN > 0.0)  ?  1.0  :  0.0;
	float specPow = pow( dotNH, mtrShine ) * specIo;
	
	vec4 ambient  = pointLightAmbient  * mtrAmbient  * dotLN;
	vec4 diffuse  = pointLightDiffuse  * mtrDiffuse  * dotLN;
	vec4 specular = pointLightSpecular * mtrSpecular * specPow * specAmount;
	vec4 light    = decay * (ambient + diffuse + specular);
	
	return light;
}



vec4 computeSpotLight( in vec3 vNorm, in vec3 vView, in float specAmount ) {
	vec3 vLight    = normalize( spotLightEyePos.xyz - position.xyz );
	vec3 vHalf     = normalize( vLight + vView );
	vec3 vSpot     = normalize( -spotLightEyeVec.xyz );

	float dotLN    = dotZ( vLight, vNorm );
	float dotNH    = dotZ( vHalf,  vNorm );
	float dotLS    = dotZ( vLight, vSpot );
	float dotVS    = dotZ( -vView, vSpot ); // How aligned are the camera and spotlight
	float specSpot = dotLN * dotLS * dotVS; // Spotlight reflects specular proportional to alignment with camera
	// TODO: make the specular take the cone into account
	
	float nhGt     = (dotNH    > 0.0)           ? 1.0 : 0.0;
	float lsGt     = (dotLS    > spotLightCone) ? 1.0 : 0.0;
	float vsGt     = (specSpot > 0.0)	        ? 1.0 : 0.0;
	float spotPow  = pow( dotLS, spotLightSoftness ) * dotLN    * lsGt;
	float specPow  = pow( dotNH, mtrShine )          * specSpot * vsGt * nhGt;

	float dist     = distance( spotLightEyePos.xyz, position.xyz );
	float decay    = lightDecay( dist, spotLightDecay );

	vec4 ambient   = spotLightAmbient  * mtrAmbient  * spotPow;
	vec4 diffuse   = spotLightDiffuse  * mtrDiffuse  * spotPow;
	vec4 specular  = spotLightSpecular * mtrSpecular * specPow * specAmount;
	vec4 light     = decay * (ambient + diffuse + specular);

	return light;
}



vec4 computeLineLight( in vec3 vNorm, in vec3 vView, in float specAmount ) {
	vec3 liPos    = nearestPointOnLine( position.xyz, lineLightEyePosA.xyz, lineLightEyePosB.xyz );
	vec3 vLight   = normalize( liPos - position.xyz );
	vec3 vHalf    = normalize( vLight + vView );
	
	float dotLN   = dotZ( vLight, vNorm );
	float dotNH   = dotZ( vHalf,  vNorm );
	
	float dist    = distance( liPos, position.xyz );
	float decay   = lightDecay( dist, lineLightDecay );
	
	float specIo  = (dotLN > 0.0)  ?  1.0  :  0.0;
	float specPow = pow( dotNH, mtrShine ) * specIo;
	
	vec4 ambient  = lineLightAmbient  * mtrAmbient  * dotLN;
	vec4 diffuse  = lineLightDiffuse  * mtrDiffuse  * dotLN;
	vec4 specular = lineLightSpecular * mtrSpecular * specPow * specAmount;
	vec4 light    = decay * (ambient + diffuse + specular);
	
	return light;
}



void main()
{
	// Sample texture
	vec4  sampColour = texture( texColour, texCoord );
	float sampShine  = texture( texShine,  texCoord * 64.0 ).r;

	// Compute vectors common to each light
	vec3 vNorm = normalize( normal );
	vec3 vView = normalize( -position.xyz );
	
	vec4 liGlobal = computeGlobalLight();
	vec4 liDir    = computeDirLight  ( vNorm, vView, sampShine );
	vec4 liPoint  = computePointLight( vNorm, vView, sampShine );
	vec4 liSpot   = computeSpotLight ( vNorm, vView, sampShine );
	vec4 liLine   = computeLineLight ( vNorm, vView, sampShine );
	vec4 liTotal  = liGlobal + liDir + liPoint + liSpot + liLine;
	
	fragCol = sampColour + liTotal;	
}











