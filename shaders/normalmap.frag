#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D normalMap;



void main()
{
    vec4 normal = texture(normalMap, TexCoords);
    FragColor = normal;
}
