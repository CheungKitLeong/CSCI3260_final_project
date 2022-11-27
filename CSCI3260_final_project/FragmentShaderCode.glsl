#version 430

in vec3 Position;
in vec2 UV;
in vec3 Normal;

out vec4 Color;

uniform sampler2D texSamp;

void main()
{
	vec3 objectColor = vec3(texture(texSamp, UV));
	Color = vec4(objectColor, 1.0);
}
