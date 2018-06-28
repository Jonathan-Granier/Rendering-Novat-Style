#version 330 core






out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D normalMap;

void main()
{
    vec4 n = texture(normalMap,texCoord);
    vec2 slant = n.xz;
    FragColor = vec4(slant.x,-slant.y,length(slant),0);
}

