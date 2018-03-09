#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D depthMap;

void main()
{
    //float depthValue = texture(depthMap, TexCoords).r;
    FragColor = texelFetch(depthMap,ivec2(gl_FragCoord.xy),0);
}
