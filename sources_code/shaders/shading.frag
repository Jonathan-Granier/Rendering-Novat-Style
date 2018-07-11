/**
* @file shading.vert
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Compute the shading from the normalMap and the local light. Merge this result with a another shading if firstMap is false.
*
* Input texture :
*     The  normal Map.
*     The shade light Map.
*     The shading map of a different scale.
* Output :
*     A value between 0 and 1 in gray level.
*
*  SHADER NUMBER 10.
**/




#version 330 core
// Ouput : A value between 0 and 1 in gray level.
out vec4 FragColor;

in vec2 texCoord;
// TEXTURE NUMBER 2. The normal map.
uniform sampler2D normalMap;
// TEXTURE NUMBER 4. The shade light map.
uniform sampler2D shadeLightMap;
// TEXTURE NUMBER 10. The shading mao of a different scale.
uniform sampler2D shadingMap;
// The normal matrix from the camera.
uniform mat3 normalMat;
// The view matrix from the camera.
uniform mat4 mdvMat;
// If true , don't merge the result with shading map.
uniform bool firstMap;
/**
  * The merge method selected :
  *                   0. Only blur (only if we have two scales)
  *                   1. Only details (only if we have two scales)
  *                   2. Overlay standart merge.
  *                   3. WaterColor merge
  */
uniform int shadeSelector;



/**
Compute the Lambertien
    n : normal Vector
    l : light Vector
**/
float Lambertien( vec4 n, vec4 l){
    return max(dot(n,l),0);
}

/*-------------------------------------
  WATERCOLOR
  Show report for more information (p. 21-22) or the paper watercolor by [Bousseau et al].
  TLDR : just a overlay function that mix 2 values.

  Input
    detail    a value between 0 and 1.
    blur      a value between 0 and 1.

  Output
    vec3      a value between 0 and 1.
*/
float watercolor(float detail, float blur ){
  float b = blur;//*(bmax-bmin) + bmin;
  float d = detail;

  return d-(d-d*d)*((1-2*b));
}


/*-------------------------------------
  OVERLAY
  The overlay function from photoshop and gimp.
  Mix two values.
  Input
    detail    a value between 0 and 1.
    blur      a value between 0 and 1.

  Output
    float     a value between 0 and 1.
*/
float overlay(float detail, float blur){
  float bmin = 0.1;
  float bmax = 1-bmin;

  float b = blur*(bmax-bmin) + bmin;
  float d = detail;
  /**/
  if(blur>0.5){
    return 1-2*(1-d)*(1-b);
  }
  return 2*b*d;


}


void main()
{
    vec4 n = normalize(vec4(normalMat * texture(normalMap,texCoord).xyz,0));
    vec4 l = normalize(mdvMat * normalize(texture(shadeLightMap,texCoord)));
    float cCd;


    cCd = Lambertien(n,l);

    if(!firstMap && shadeSelector == 0)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd = pCd;
    }
    else if(!firstMap && shadeSelector == 2)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd = overlay(pCd,cCd);
    }
    else if(!firstMap && shadeSelector == 3)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd =  watercolor(cCd,pCd);
    }
    FragColor = vec4(cCd,cCd,cCd,0);

}
