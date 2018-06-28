/**
  Created by Jonathan Granier
  The seconde part of the Laplacian pyramid , do the difference beetween two heightMap.
**/



#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;




out vec2 texCoord;

void main()
{
    texCoord = aTexCoord;
    gl_Position = vec4(aPos, 1.0);
}

