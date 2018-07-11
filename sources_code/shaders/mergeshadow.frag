/**
* @file mergeshadow.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Merge two shadows maps with a lineare interpolation.
*
* Input texture :
*     Shadow map of the current scale.
*     Merge shadow map from a another scale.
* Output :
*     A Value in red chanel between 0 and 1.
*
*  SHADER NUMBER 9.
**/

#version 330 core
// Output, a value in the red chanel between 0 and 1.
out vec4 FragColor;

in vec2 texCoord;
// TEXTURE NUMBER 8. The shadow map of the current scale edit by a mathematical morphology.
uniform sampler2D currentShadowMap;
// TEXTURE NUMBER 9. The merge shadow map of the previous scale.
uniform sampler2D previousShadowMap;

// If currentShadow is the first map, just copy the shadow to the ouput.
uniform bool firstMap;


// Do a lineare interpolation between the two shadows maps.
void main()
{
    float currentShadow = texture(currentShadowMap, texCoord).r;
    float previousShadow = texture(previousShadowMap, texCoord).r;
    float shadow;

    if(firstMap)
      shadow = currentShadow;
    else
      shadow = (previousShadow + currentShadow) / 2.0;

    FragColor = vec4(shadow,0.0,0.0,1.0);
}
