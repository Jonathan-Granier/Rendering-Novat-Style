#version 330 core
layout(location = 0) out vec4 outBuffer;

in vec2 texCoord;

uniform sampler2D curvatureMap;
uniform vec3 lightPosition;
uniform float yaw;
uniform float pitch;
uniform int lightSelector;


#define PI 3.14159265359

float eps = 1e-5;


float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}



vec4 Rotation3D(in float localYaw,in float localPitch){
  vec4 v;

  v.x = cos(localPitch) * cos(localYaw);
  v.y = sin(localPitch);
  v.z = cos(localPitch) * sin(localYaw);
  v.w = 0.0;
  v = normalize(v);


  return v;
}





vec4 computeLight(in vec4 c, in vec2 l){
  vec2 normL = normalize(l);
  vec2 maxCurv =normalize(vec2(c.x, -c.y));
/**/
  if(dot(normL,maxCurv)< 0){
    maxCurv  = -maxCurv;
  }
  maxCurv = normalize(maxCurv);
/**/

  float k1 = c.z;
  float k2 = c.w;


  // See 18 - Shape Curvature (koenderink) page 9.
  float s,cu;
  if(k1-k2 ==0){
    s = 0;
    maxCurv = normL;
    cu = 0;
  }
  else{
    s = atan((k1+k2)/(k1-k2)); //TODO shape index
    cu = sqrt((k1*k1+k2*k2)/2);
  }

  //k = (k1-k2)/(k1+k2);

  float det = normL.x * maxCurv.y - normL.y* maxCurv.x;
  float theta = (det/abs(det))*(acos(cosTheta(normL,maxCurv)));
  float newYaw = yaw;

  if(lightSelector == 0)
    newYaw = yaw + s *cu * theta;
  if(lightSelector == 1)
    newYaw = yaw + s * abs(theta);
  if(lightSelector == 2)
    newYaw = yaw + cu * theta;
  if(lightSelector == 3)
    newYaw = yaw + cu * abs(theta);


  //Rotation
  return Rotation3D(newYaw,pitch);

 // return vec4(s,0,0,0);
}




vec4 computeTheta(in vec4 c,in vec2 l){

  vec2 normL = normalize(l);
  vec2 maxCurv = normalize(vec2(c.x,-c.y)) ;

  /**
  if(dot(normL,maxCurv) < 0){
      maxCurv  = -maxCurv;
  }
   maxCurv = normalize(maxCurv);
  /**/


  float k1 = c.z;
  float k2 = c.w;

  float s,cu;
  if(k1-k2 ==0){
    s =1;
    maxCurv = normL;
    cu = 0;
  }
  else{
    s = atan((k1+k2)/(k1-k2));
    cu = sqrt((k1*k1+k2*k2)/2);
  }




  float det = normL.x * maxCurv.y - normL.y* maxCurv.x;
  float theta = (det/abs(det))* (acos(cosTheta(normL,maxCurv)));

//TODO print theta en remap . entre (0,1)
  return vec4(theta*s*cu/(PI/2.0),0,0,0);
}




void main()
{
  vec4 c = texture(curvatureMap,  texCoord);

  vec2 l = lightPosition.xz;
  vec4 newLightDir;

  newLightDir = computeLight(c,l);

  float k1 = c.z;
  float k2 = c.w;

  float s,cu;
  if(k1-k2 ==0){
    s = 0;
    cu = 0;
  }
  else{
    s = atan((k1+k2)/(k1-k2));
    cu = sqrt((k1*k1+k2*k2)/2);
  }


  outBuffer = newLightDir;



}
