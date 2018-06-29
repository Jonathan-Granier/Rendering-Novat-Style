/**
  Created by Jonathan Granier
  The seconde part of the Laplacian pyramid , do the difference beetween two heightMap.
  Do nothing if it's the lastMap of the pyramid.
**/


#version 330 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D currentHeightMap;
uniform sampler2D previousHeightMap;
uniform bool lastMap;

void main()
{
    float currentHeight = texture(currentHeightMap, texCoord).r;
    float previousHeight = texture(previousHeightMap, texCoord).r;
    float height;
    if(lastMap)
      height = currentHeight;
    else
      height = currentHeight - previousHeight;

    FragColor = vec4(height,height,height,0);
}

