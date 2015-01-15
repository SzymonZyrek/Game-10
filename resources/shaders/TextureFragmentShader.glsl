#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
	vec3 shade = vec3(0.23,0.23,0.23);
	// Output color = color of the texture at the specified UV
	color = texture2D( myTextureSampler, UV ).rgb;
	color -= shade;
}