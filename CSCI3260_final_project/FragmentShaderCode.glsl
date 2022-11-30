#version 430

in vec3 Position;
in vec2 UV;
in vec3 Normal;

out vec3 Color;

uniform sampler2D texSamp;
uniform sampler2D normalSamp;
uniform bool normMap;

// for lighting
struct PointLight {
    vec3 position;
    float intensity;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight ptLight;
// For specular reflection
uniform vec3 viewPos; 
uniform float shininess;

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 objectColor = vec3(texture(texSamp, UV));
    vec3 ambient = light.ambient * objectColor;
    vec3 diffuse = light.diffuse * diff * objectColor;
    vec3 specular = light.specular * spec ;
    // ambient *= attenuation; // PIM doesn't have this
    diffuse *= attenuation;
    specular *= attenuation;
    return ambient + light.intensity * (diffuse + specular);
}


void main()
{
    // Normalization
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - Position);
	Color = CalcPointLight(ptLight, norm, Position, viewDir);
}
