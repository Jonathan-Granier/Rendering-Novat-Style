#version 330 core
layout(location = 0) out vec4 outBuffer;

in vec2 texCoord;

uniform sampler2D curvatureMap;
uniform vec3 lightPosition;
uniform float yaw;
uniform float pitch;
uniform int lightSelector;
uniform float threshold;

#define PI 3.14159265359
#define PI2 PI/2.2
#define PI4 PI/4.0
float eps = 1e-2;


float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}

float smoothTheta(float theta){


  if(abs(theta) < threshold){
    return 1;
  }
  if(threshold > PI2){
    return 0;
  }

  float f = smoothstep(threshold,PI2,abs(theta));
  return -f+1;

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
  float s,cu,delta;
  if(k1-k2 ==0){
    s = 0;
    maxCurv = normL;
    cu = 0;
    delta = 0;
  }
  else{
    s = atan((k1+k2)/(k1-k2)); //TODO shape index
    cu = sqrt((k1*k1+k2*k2)/2);
    delta = abs(k1-k2);

  }


  float delta2 = abs(sin(k1*PI));
  //k = (k1-k2)/(k1+k2);

  float det = normL.x * maxCurv.y - normL.y* maxCurv.x;
  float theta = (det/abs(det))*(acos(cosTheta(normL,maxCurv)));
  float newYaw = yaw;

  if(lightSelector == 0)
    newYaw = yaw + s * theta;
  if(lightSelector == 1)
    newYaw = yaw + cu * theta;
  if(lightSelector == 2)
    newYaw = yaw + cu*s * theta;
  if(lightSelector == 3)
    newYaw = yaw + smoothTheta(theta)*theta;
  if(lightSelector == 4)
    newYaw = yaw + cu*s *theta;


  //Rotation
  return Rotation3D(newYaw,pitch);

 // return vec4(s,0,0,0);
}




vec4 computeTheta(in vec4 c,in vec2 l){

  vec2 normL = normalize(l);
  vec2 maxCurv = normalize(vec2(c.x,-c.y)) ;

  if(dot(normL,maxCurv) < 0){
      maxCurv  = -maxCurv;
  }
   maxCurv = normalize(maxCurv);


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

 // theta = LogisticFunction(theta,PI/4.0)*theta;


 //theta = ((theta / (PI/2.0)) +1 )/2.0;

 //float x = (abs(theta/(PI/2.0))- (PI/4.0)) * 2;
  //return vec4(theta,0,0,0);



/*  if(abs(theta) > T -eps && abs(theta) < T + eps){
    return vec4(0,0,1,0);
  }
*/
//  theta = LogisticFunction(theta,PI4)*theta;
 // theta = ((theta / (PI2)) +1 )/2.0;


  float f = smoothTheta(theta);






 // float f = 1/(1+exp(x*7));
   theta = f*theta;
   theta = ((theta / (PI2)) +1 )/2.0;
    return vec4(theta,0,0,0);
}







void main()
{
  vec4 c = texture(curvatureMap,  texCoord);

  vec2 l = lightPosition.xz;
  vec4 newLightDir;

  newLightDir = computeLight(c,l);

  float k1 = c.z;
  float k2 = c.w;
  float cu = sqrt((k1*k1+k2*k2)/2);
   float delta2 = abs(sin(k1));

  // outBuffer =vec4(abs(k1),0,0,0);

  /* if(abs(k1)<0.05){
     outBuffer = vec4(1,0,1,0);
   }*/



  outBuffer = newLightDir;
}
