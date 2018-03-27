#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 mdvMat;
uniform mat4 projMat;

uniform mat3 normalMat;


uniform vec3 lightPosition;
uniform vec3 cameraPosition;


// declare an interface block; see 'Advanced GLSL' for what these are.
out VS_OUT {
    vec4 lightDir;
    vec3 Normal;
    vec4 cameraDir;
} vs_out;


void main()
{

    vec4 position = vec4(aPos,1.0);
    vs_out.lightDir = mdvMat * normalize(vec4(lightPosition,1.0) - position);
    vs_out.Normal = normalMat * aNormal;
    vs_out.cameraDir =  vec4(cameraPosition,1.0) - mdvMat*position;
    gl_Position = projMat * mdvMat * modelMat * position;
}
