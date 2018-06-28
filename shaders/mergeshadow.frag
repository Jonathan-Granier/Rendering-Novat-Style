#version 330 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D currentShadowMap;
uniform sampler2D previousShadowMap;
uniform bool firstMap;

void main()
{
    float currentShadow = texture(currentShadowMap, texCoord).r;
    float previousShadow = texture(previousShadowMap, texCoord).r;
    float shadow;
    if(firstMap)
      shadow = currentShadow;
    else
      shadow = (previousShadow+ currentShadow) / 2.0;

    FragColor = vec4(shadow,0.0,0.0,1.0);
}

