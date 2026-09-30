#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
flat in int material;

uniform sampler2DArray myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

out vec3 color;

vec3 debugFloat(float value, float max){
	if (value!=0.0f){
		float ratio = (value/max);
		float nV = ratio*0.5f;
		return vec3(0.5f+nV,0.0f,0.5f-nV);
	}else{
		return vec3(0.0f,0.0f,0.0f);
	}
}
vec3 debugInt(int value, int max){
	if (value!=0){
		float ratio = (value/max);
		float nV = ratio*0.5f;
		return vec3(0.5f+nV,0.0f,0.5f-nV);
	}else{
		return vec3(0.0f,0.0f,0.0f);
	}
}

void main(){
  //------------ DEBUGGING ------------//
    vec3 debugColor = vec3(0,0,0);
    debugColor = debugInt(material, -2147483647);
	if (debugColor.x>0||debugColor.y>0||debugColor.z>0)
	color = debugColor;
  //------------ DEBUGGING ------------//
}