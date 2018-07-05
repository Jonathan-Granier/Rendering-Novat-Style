#version 330 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D shadowMap;
uniform int operator;
uniform bool doMorpho;

float morphoFilter(float type){
  int min = -5;
  int max = 5;

  vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
  for(int x = min; x <= max; x++){
    for(int y = min ; y <= max; y++){
      if(texture(shadowMap,texCoord + vec2(x,y)*texelSize).r == type)
        return type;
    }
  }


  return type==0.0?1.0:0.0;
}



void main()
{
    float shadow = texture(shadowMap, texCoord).r;

/**/
    //Dilation
    if(operator == 1 && doMorpho){
      if(shadow == 1.0){
        shadow = morphoFilter(0.0);
      }
    }
    //Erosion
    else if(operator == 0 && doMorpho){
      if(shadow == 0.0){
        shadow = morphoFilter(1.0);
      }
    }
/**/

    FragColor = vec4(shadow,0.0,0.0,0);
}

// Faire erosion puis dilatation dans 2eme passe . Orientation rectangle dans le sens de la lumière.
