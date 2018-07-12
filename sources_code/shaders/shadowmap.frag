/**
* @file shadowmap.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Compute the shadow map with a raymarching.
*
* Input texture :
*     The edit height map.
*     The shadow light map.
* Output :
*     A boolean value in the red chanel. 0--> shadow , 1--> no shadow.
*
*
*  SHADER NUMBER 6.
**/

#version 330 core
// The output , a boolean value in the red chanel. 0--> shadow , 1--> no shadow.
out vec4 FragColor;
//The textire coordinates
in vec2 texCoord;

// TEXTURE NUMBER 1. The edit height Map.
uniform sampler2D heightMap;
// TEXTURE NUMBER 5. The shadow light Map.
uniform sampler2D shadowLightMap;

// The max altitude of the editHeightMap.
uniform float     ymax;
// The min altitude of the editHeightMap.
uniform float     ymin;
// The offset of the DEM loaded.
uniform float step;
// The resolution of the DEM.
uniform vec2 resolution;

/*-------------------------------------
* CASTRAY.
*
* Do a raymarching on the editheightMap from the current pixel , with the local light as direction.
*
* Input
*     origin          The texture coordinates of the current pixel.
*     dir             The local direction of the light projected on the XY plan.
*     originHeight    The height of the current pixel.
*     stepH           The height add when you add dir to origin.
*
* Output
*     bool            True : No shadow, False : shadow.
*/
bool castRay( const vec2 origin, const vec2 dir, const float originHeight,float stepH){
  const float delt =0.001f;
  const float mint = 0.001f;
  const float maxt = 1.0f;

  float currentH = originHeight;
  vec2 p = origin;
  vec2 d = dir;


  while(p.x >= 0 && p.x <= 1.0 && p.y >= 0 && p.y <= 1.0 && currentH>=ymin && currentH <=ymax){
    vec4 l = texture(shadowLightMap,p);
    d =  vec2(l.x/resolution.x, -l.z/resolution.y);
    p += dir;
    currentH += stepH;
    if(currentH < texture(heightMap,p).r){
      return false;
    }
  }
  return true;
}



void main()
{
    float h = texture(heightMap, texCoord).r;
    vec4 l = texture(shadowLightMap,texCoord);

    vec2 l2D = vec2(l.x/resolution.x, -l.z/resolution.y);
    float stepH = step * sqrt(1*1-length(l.xz)*length(l.xz));
    if(isnan(stepH)){
      stepH = 0;
    }

    if(castRay(texCoord,l2D,h,stepH))
      FragColor = vec4(1,0,0,0);
    else
      FragColor = vec4(0,0,0,0);
}
