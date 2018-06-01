#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D currentShadowMap;
uniform sampler2D previousShadowMap;
uniform bool firstMap;

void main()
{
    float currentShadow = texture(currentShadowMap, texcoord).r;
    float previousShadow = texture(previousShadowMap, texcoord).r;
    float shadow;
    if(firstMap)
      shadow = currentShadow;
    else
      //shadow = previousShadow;
      shadow = (previousShadow+ currentShadow) / 2.0;
    FragColor = vec4(shadow,0.0,0.0,1.0);
}

