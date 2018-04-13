#version 330 core
out vec4 FragColor;

in vec2 texCoord;


uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform sampler2D heightMap;
uniform sampler2D curvatureMap;
uniform sampler2D lightMap;
uniform int ymin;
uniform int ymax;
/*
  Select the texture to draw :
  0 - depthMap
  1 - heightMap
  2 - normalMap
  3 - curvatureMap
  4 - lightMap
*/
uniform int selectTexture;
void main()
{

    if(selectTexture == 0)
    {
      float depthValue = texture(depthMap, texCoord).r;
      FragColor += vec4(depthValue,depthValue,depthValue,1.0);
    }
    if(selectTexture == 1){
      float grayValue = texture(heightMap, texCoord).r;
      grayValue = (grayValue - ymin)/(ymax-ymin);
      FragColor = vec4(grayValue,grayValue,grayValue,1.0);
    }
    if(selectTexture == 2){
      FragColor = texture(normalMap,     texCoord);
    }
    if(selectTexture == 3){
      FragColor = texture(curvatureMap,  texCoord);
    }
    if(selectTexture == 4){
      FragColor = texture(lightMap,      texCoord);
    }



}
