#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform vec2 resolution;
uniform sampler2D shadowMap;
uniform int operator;
uniform bool doMorpho;

float morphoFilter(int type){
  int min = -5;
  int max = 5;

  float shadow = 1;

  int numberType = 0;


  vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
  for(int x = min; x <= max; x++){
    for(int y = min ; y <= max; y++){
      if(texture(shadowMap,texcoord + vec2(x,y)*texelSize).r == type)
        return type;
    }
  }


  return type==0?1:0;
}



void main()
{
    float shadow = texture(shadowMap, texcoord).r;

/**/
    // Erosion
    if(operator == 1 && doMorpho){
      if(shadow == 0){
        shadow = morphoFilter(1);
      }
    }
    //Dilation
    else if(operator == 0 && doMorpho){
      if(shadow == 1){
        shadow = morphoFilter(0);
      }
    }
/**/

    FragColor = vec4(shadow,0.0,0.0,0);
}

// Faire erosion puis dilatation dans 2eme passe . Orientation rectangle dans le sens de la lumière.
