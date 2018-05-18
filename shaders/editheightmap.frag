#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D currentHeightMap;
uniform sampler2D previousHeightMap;
uniform bool firstMap;

void main()
{
    float currentHeight = texture(currentHeightMap, texcoord).r;
    float previousHeight = texture(previousHeightMap, texcoord).r;
    float height;
    if(firstMap)
      height = currentHeight;
    else
      height = currentHeight - previousHeight;

    FragColor = vec4(height,height,height,0);
}

