#version 330 core

/*Les question lumière
  Hauteur
  Inversion pente
  Paralax : multi echelle ? Même hauteur ?
  */

















layout(location = 0) out vec4 outBufferDir;
layout(location = 1) out vec4 outBufferAngles;

in vec2 texCoord;

uniform sampler2D curvatureMap;
uniform sampler2D slantMap;
uniform sampler2D shadeLightMap;
uniform sampler2D shadeAnglesMap;

uniform vec3 lightPosition;
uniform float yaw;
uniform float pitch;
uniform int lightSelector;
uniform float threshold;
uniform bool doMerge;
uniform bool none;



#define PI 3.14159265359
#define PI2 PI/2.0
#define PI4 PI/4.0
float eps = 1e-2;


float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}



float modulo(float y){
  return y - 2*PI*floor(y/(2.0 * PI));
}


float averageAngle(float y1, float y2){
   float aveC = (cos(y1)+cos(y2))/2.0;
   float aveS = (sin(y1)+sin(y2))/2.0;
   return modulo(atan(aveS,aveC));
}


float smoothTheta(float theta){



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




float smoothReverse(float dot){
  float edgeMin = 0.0;
  float edgeMax = 0.0;

  float s = smoothstep(edgeMin,edgeMax,dot);

  return s*PI;

}


vec4 computeLight(in vec4 s,in vec2 l, inout float newYaw){
  vec2 normL = normalize(l);
  vec2 slint = normalize(vec2(s.x,-s.y)) ; // Because the light and the curve have not the same Y axis


  /**/
  if(cosTheta(normL,slint) < 0){
     slint = -slint;
     //return vec4(0,1,0,1);
  }
  /**/
  //slint = normalize(slint);


  float normS = s.z;

  if(normS <= 0){
    slint = normL;
  }


  float det = normL.x * slint.y - normL.y* slint.x;
  float thetaSign = (det/abs(det));

  if(isnan(thetaSign)){

    thetaSign = 1;
  }
  float theta = thetaSign* (acos(cosTheta(normL,slint)));

  //if(isnan((acos(cosTheta(normL,slint))))){
    //return vec4(1,0,0,0);
    //thetaSign = 1;rr
  //}

  theta = theta *normS * smoothTheta(theta);
  newYaw += theta;
  newYaw = modulo(newYaw);
  //return vec4(theta,0,0,1);
  return Rotation3D(newYaw,pitch);

}



void main()
{
  //vec4 c = texture(curvatureMap,  texCoord);
  vec4 s = texture(slantMap,texCoord);
  //vec2 l = lightPosition.xz;
  vec4 newLightDir;
  float currentYaw;



  vec2 l = lightPosition.xz;
  currentYaw = yaw;
  //newLightDir = Rotation3D(yaw,pitch);
  newLightDir = computeLight(s,l,currentYaw);
  float newYaw = currentYaw;


/**/
  if(lightSelector != 0 && doMerge){
    float previousYaw = texture(shadeAnglesMap,texCoord).r;
    newYaw = averageAngle(currentYaw,previousYaw);
    newLightDir = Rotation3D(newYaw,pitch);
  }
/**/





  if(none){
    outBufferDir = vec4(lightPosition,0);
  }else
  {
    outBufferDir = newLightDir;
  }
  //outBufferDir = vec4(previousYaw,0,0,0);
  outBufferAngles = vec4(newYaw,pitch,0.0,0.0);

}
