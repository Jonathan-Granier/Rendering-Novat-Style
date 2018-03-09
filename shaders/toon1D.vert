#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;



uniform mat4 mdvMat;
uniform mat4 projMat;
uniform mat3 normalMat;
uniform vec3 lightPosition;

out vec2 TexCoord;
out vec4 Normal;
out vec4 lightVector;


void main()
{
    TexCoord = aTexCoord;
    vec4 position = vec4(aPos,1.0);

    Normal = vec4(normalize(normalMat*aNormal),0.0);
    lightVector = normalize( vec4(lightPosition,0.0) - mdvMat*position);
    gl_Position = projMat * mdvMat * position;
}
