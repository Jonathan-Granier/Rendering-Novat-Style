#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 mdvMat;
uniform mat4 projMat;
uniform mat3 normalMat;
uniform mat4 ligthSpaceMat;

uniform vec3 lightPosition;

uniform sampler2D normalMap;

// declare an interface block; see 'Advanced GLSL' for what these are.

out vec4 lightDir;
out vec3 Normal;
out vec4 FragPosLightSpace;
out vec2 texCoord;


mat4 DepthBiasMVP = mat4(0.5, 0.0, 0.0, 0.0,
                         0.0, 0.5, 0.0, 0.0,
                         0.0, 0.0, 0.5, 0.0,
                         0.5, 0.5, 0.5, 1.0
                         );



void main()
{

    vec4 position = vec4(aPos,1.0);
    lightDir = normalize(mdvMat * vec4(lightPosition,0.0));
    texCoord = vec2(aTexCoord.x,(aTexCoord.y -1) * -1);
    Normal = normalMat * texture(normalMap,texCoord).xyz;
   // vs_out.Normal = normalMat * aNormal;
    FragPosLightSpace = ligthSpaceMat * position;

    gl_Position = projMat * mdvMat  * modelMat * position;



}
