#version 430

in layout(location=0) vec3 position;

out vec3 Position;

/* Import the coordinate matrices */

uniform mat4 view;
uniform mat4 proj;

void main(){
	Position = position;
	vec4 pos =  proj * view * vec4(position, 1.0);	
	gl_Position = pos.xyww;
}