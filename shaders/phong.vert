#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 mdvMat;
uniform mat4 projMat;
uniform mat3 normalMat;


uniform vec3 lightPosition;


// declare an interface block; see 'Advanced GLSL' for what these are.
out VS_OUT {
    vec4 lightDir;
    vec3 Normal;
} vs_out;


void main()
{

    vec4 position = vec4(aPos,1.0);
    vs_out.lightDir =mdvMat *  normalize(vec4(lightPosition,0.0) );
    vs_out.Normal = normalMat * aNormal;
    gl_Position = projMat * mdvMat * modelMat * position;
}
