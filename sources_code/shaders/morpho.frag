/**
* @file morpho.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Make a mathematical morphology on a shadow map.
*
* Input texture :
*     A shadow map
*
* Output :
*     A boolean value in red chanel. 0 -> shadow , 1-> no shadow.
*
*  SHADER NUMBER 7 and 8.
**/









#version 330 core
// Output A boolean value in red chanel. 0 -> shadow , 1-> no shadow.
out vec4 FragColor;
// The texture coordinates
in vec2 texCoord;
// TEXTURE NUMBER 6 or 7. The current shadow map.
uniform sampler2D shadowMap;

/**
* The mathematical morphology operator :
*     0. Erosion.
*     1. Dilation.
*/
uniform int operator;
// If false , just copy the shadow map in the ouput.
uniform bool doMorpho;


/*-------------------------------------
* MORPHOFILTER
*
* Do the morphology
* If one pixel around the current pixel (in a 5x5 quad) is equal to type , return type.
* Return the reverse otherwise (type = 0 , return 1. type = 1, return 0)
*
* Input
*   type    0 or 1.
*
* Output
*   float   0 or 1.
*/
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

    FragColor = vec4(shadow,0.0,0.0,0);
}
