#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;
flat in int material;

// Ouput data
out vec3 color;

uniform sampler2DArray myTextureSampler;
uniform sampler2DArray normalMap;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;


void main(){
	// TODO: uniform that
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 80.0f;
	vec3 ambientOcclusion = vec3(0.03,0.03,0.03);

	vec3 materialDiffuseColor = texture( myTextureSampler, vec3(UV, material) ).rgb;
	vec3 test = texture(normalMap, vec3(UV, material)).rgb;
	vec3 materialAmbientColor = ambientOcclusion * materialDiffuseColor*test;
	vec3 materialSpecularColor = 3*ambientOcclusion;
	// Local normal, in tangent space
	vec3 TextureNormal_tangentspace = normalize(texture(normalMap, vec3(UV, material)).rgb*2.0 - 1.0);

	float distanceToLight = length( LightPosition_worldspace - Position_worldspace );
	vec3 fragmentNormal = normalize(TextureNormal_tangentspace);
	vec3 directionToLight = normalize(LightDirection_tangentspace);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( fragmentNormal,directionToLight ), 0,1 );
	vec3 eyeVector = normalize(EyeDirection_cameraspace);
	vec3 reflectDirection = reflect(-directionToLight,fragmentNormal);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( eyeVector,reflectDirection ), 0,1 );
	// finally:
	float minDistanceToLight = 7.2;
	float clampedDistenceToLight;

	if (distanceToLight<minDistanceToLight) {
		clampedDistenceToLight = minDistanceToLight;
	}
	else{
		clampedDistenceToLight = distanceToLight;
	}
	color =
		// Ambient : simulates indirect lighting
		materialAmbientColor
		// Diffuse : "color" of the object
		+ (materialDiffuseColor * lightColor * lightPower * cosTheta / (clampedDistenceToLight*clampedDistenceToLight))
		// Specular : reflective highlight, like a mirror
		+ materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (clampedDistenceToLight*clampedDistenceToLight);

	//color = 
	//(materialDiffuseColor * lightColor * (lightPower/100)/(distanceToLight*distanceToLight)) +
	//(ambientOcclusion * materialDiffuseColor );

}