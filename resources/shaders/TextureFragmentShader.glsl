#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

varying float testFloat;

vec3 debugFloat(float value, float max){
	if (value!=0.0f){
		float ratio = (value/max);
		
		float nV = ratio*0.5f;
		return vec3(0.5f+nV,0.0f,0.5f-nV);
	}else{
		return vec3(0.0f,1.0f,0.0f);
		//return vec3(0.0f,0.0f,0.0f);
	}
}

void main(){
	// TODO: uniform that
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 7.0f;
	vec3 ambientOcclusion = vec3(0.01,0.01,0.01);

	vec3 materialDiffuseColor = texture2D( myTextureSampler, UV ).rgb;
	vec3 materialAmbientColor = ambientOcclusion * materialDiffuseColor;
	vec3 materialSpecularColor = 3*ambientOcclusion;

	float distanceToLight = length( LightPosition_worldspace - Position_worldspace );
	vec3 fragmentNormal = normalize( Normal_cameraspace );
	vec3 directionToLight = normalize( LightDirection_cameraspace );
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
	color = 
		// Ambient : simulates indirect lighting
		materialAmbientColor +
		// Diffuse : "color" of the object
		materialDiffuseColor * lightColor * lightPower * cosTheta / (distanceToLight*distanceToLight) +
		// Specular : reflective highlight, like a mirror
		materialSpecularColor * lightColor * lightPower * pow(cosAlpha,5) / (distanceToLight*distanceToLight);

	//color = 
	//(materialDiffuseColor * lightColor * (lightPower/100)/(distanceToLight*distanceToLight)) +
	//(ambientOcclusion * materialDiffuseColor );

  //------------ DEBUGGING ------------//
    vec3 debugColor = vec3(0,0,0);
   //debugColor = debugFloat(testFloat, 1.0);
    if (debugColor.x>0||debugColor.y>0||debugColor.z>0)
	color = debugColor;
  //------------ DEBUGGING ------------//
}