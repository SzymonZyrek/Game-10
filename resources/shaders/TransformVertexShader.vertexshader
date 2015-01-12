#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 position;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	vec3 final_position;
	//final_position.x = vertexPosition_modelspace.x + position.x;
	//final_position.y = vertexPosition_modelspace.y + position.y;
	//final_position.z = vertexPosition_modelspace.z + position.z;
	final_position = vertexPosition_modelspace + position;
	gl_Position =  MVP * vec4(final_position,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

