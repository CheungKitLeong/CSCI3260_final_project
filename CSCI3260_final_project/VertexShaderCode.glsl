#version 430

in layout(location=0) vec3 position;
in layout (location = 1) vec2 vertexUV;
in layout (location = 2) vec3 normal;


/* Import the coordinate matrices */
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;



void main()
{
	vec4 v = vec4(position, 1.0);
	v = proj * view * model * v;
	gl_Position = v;	
}
