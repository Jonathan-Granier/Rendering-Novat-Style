#version 330 core
out vec4 FragColor;


in vec2 TexCoord;

uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;


void main()
{
  //FragColor = texture(texture_normal1,TexCoord);
  //FragColor = vec4(1,0,0,1);
  FragColor = mix(texture(texture_normal1,TexCoord),texture(texture_normal2,TexCoord),0.2);
}
