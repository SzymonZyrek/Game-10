#version 330 core
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 position;
uniform vec3 LightPosition_worldspace;
uniform float TestValue;

out float testFloat;

void main(){
	vec3 transformedPosition;
	transformedPosition = vertexPosition_modelspace + position;
	gl_Position =  MVP * vec4(transformedPosition,1);
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
    EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
    vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
    LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

 
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
	testFloat = TestValue;
}

