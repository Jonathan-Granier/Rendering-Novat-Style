#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D heightMap;
uniform int ymin;
uniform int ymax;



void main()
{
    float grayValue = texture(heightMap, TexCoords).r;
    grayValue = (grayValue - ymin)/(ymax-ymin);
    FragColor = vec4(grayValue,grayValue,grayValue,1.0);
}
