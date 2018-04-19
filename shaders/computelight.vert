#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 mdvMat;
uniform mat4 projMat;
uniform mat3 normalMat;


uniform vec3 lightPosition;
uniform sampler2D lightMap;

// declare an interface block; see 'Advanced GLSL' for what these are.

out vec4 lightDir;
out vec3 normal;
out vec2 texCoord;


void main()
{

    vec4 position = vec4(aPos,1.0);
    texCoord = vec2(aTexCoord.x,(aTexCoord.y -1) * -1);

    lightDir = mdvMat * normalize(vec4(texture(lightMap,texCoord)));
  //lightDir = mdvMat * normalize(vec4(lightPosition,1.0) - position);
    normal = normalMat * aNormal;

    gl_Position = projMat * mdvMat * modelMat * position;
}