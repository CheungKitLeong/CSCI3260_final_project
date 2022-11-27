#version 430

in layout(location=0) vec3 position;
in layout (location = 1) vec2 vertexUV;
in layout (location = 2) vec3 normal;

out vec3 Position;
out vec2 UV;
out vec3 Normal;

/* Import the coordinate matrices */
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;



void main()
{
	Position = vec3(model * vec4(position, 1.0));
	gl_Position =  proj * view * vec4(Position, 1.0);	
	UV = vertexUV;
	Normal = mat3(transpose(inverse(model))) * normal;
}
