#version 330 core
out vec4 FragColor;
  
in VS_OUT
{
    vec3 Normal;
    vec3 FragPos; 
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTex;

void main()
{
    //error color
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
