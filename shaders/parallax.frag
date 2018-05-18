#version 450 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D heightMap;
uniform sampler2D shadowLightMap;
uniform vec3 lightPosition;

uniform float ymin;
uniform float ymax;
uniform float step;
uniform vec2 resolution;

bool castRay( const vec2 origin, const vec2 dir, const float originHeight,float stepH){
  const float delt =0.001f;
  const float mint = 0.001f;
  const float maxt = 1.0f;

  float currentH = originHeight;
  vec2 p = origin;
  vec2 d = dir;

  /*p += dir;
  currentH += stepH;
  */
  //for(float t = mint; t< maxt; t +=delt){
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
   // vec3 l = normalize(lightPosition);

    vec2 l2D = vec2(l.x/resolution.x, -l.z/resolution.y);
    float stepH = step * sqrt(1*1-length(l.xz)*length(l.xz));
    if(isnan(stepH)){
      stepH = 0;
    }
   /**
    if(castRay(texCoord,l2D,h,stepH))
      FragColor = vec4(1,0,0,0);
    else/**/
      FragColor = vec4(0,0,0,0);


    //float c = castRay(texCoord,l2D,h,stepH);

   // FragColor = vec4(stepH,0,0,0);


}
