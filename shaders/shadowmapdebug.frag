#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D depthMap;

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(depthValue,depthValue,depthValue,1.0);
    //FragColor = texelFetch(depthMap,ivec2(gl_FragCoord.xy),0);
}
