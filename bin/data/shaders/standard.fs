#version 330 core
out vec4 FragColor;
  
in VS_OUT
{
    vec3 Normal;
    vec3 FragPos; 
    vec2 TexCoords;
} fs_in;

uniform vec4 color;
uniform vec3 specColor;
uniform float specGloss;
uniform sampler2D diffuseTex;
uniform vec3 viewPos;
uniform vec3 ambient;

struct DirLight {
    vec3 direction;
    vec3 color;
};  
uniform DirLight dirLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float NdotL = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specGloss);
    vec3 specular = specColor * spec;


    return (light.color  * NdotL) + specular; 
}  

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec4 diffuse = vec4(calcDirLight(dirLight, fs_in.Normal, viewDir), 1.0);
    vec4 ambient = vec4(ambient, 1.0);

    FragColor = color * (diffuse + ambient) * texture(diffuseTex, fs_in.TexCoords);
}
