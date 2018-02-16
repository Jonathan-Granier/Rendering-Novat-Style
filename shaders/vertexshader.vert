#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 mdvMat;
uniform mat4 projMat;
uniform mat4 normalMat;

out vec2 TexCoord;

void main()
{
    //gl_Position = vec4(aPos,1.0);
    //gl_Position = projection * view * model * vec4(aPos,1.0);
    gl_Position = projMat * mdvMat * vec4(aPos,1.0);
    TexCoord = aTexCoord;
}
