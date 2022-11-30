#version 430

in vec3 Position;

out vec4 Color;

uniform samplerCube skybox;

void main(){
	Color = texture(skybox, Position);
}