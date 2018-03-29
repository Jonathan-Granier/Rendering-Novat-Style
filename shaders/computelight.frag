#version 330 core
layout(location = 0) out vec4 outBuffer;

in vec2 texCoord;

uniform sampler2D curvatureMap;
uniform vec3 lightPosition;

void main()
{
  //outBuffer = texture(curvatureMap,  texCoord);

  //vec3 lightDir = normalize(lightPosition);

  outBuffer = vec4(lightPosition,0.0);
}
