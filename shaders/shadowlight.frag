#version 330 core

/*Les question lumière
  Hauteur
  Inversion pente
  Paralax : multi echelle ? Même hauteur ?
  */

layout(location = 0) out vec4 outBufferDir;
layout(location = 1) out vec4 outBufferAngles;

in vec2 texCoord;


uniform sampler2D slantMap;
uniform sampler2D shadowLightMap;
uniform sampler2D shadowAnglesMap;

uniform vec3 lightPosition;
uniform float yaw;
uniform float pitch;
uniform int lightSelector;
uniform float threshold;
uniform bool doEdit;

#define PI 3.14159265359
#define PI2 PI/2.2
#define PI4 PI/4.0
float eps = 1e-2;


float modulo(float y){
  return y - 2*PI*floor(y/(2.0 * PI));
}



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




vec4 computeLight(in vec4 s,in vec2 l, inout float newYaw){
  vec2 normL = normalize(l);
  vec2 slint = normalize(vec2(s.x,-s.y)) ; // Because the light and the curve have not the same Y axis

  if(cosTheta(normL,slint) < 0){
     slint = -slint;
  }

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


  theta = theta *normS * smoothTheta(theta);
  newYaw += theta;
  newYaw = modulo(newYaw);
  return Rotation3D(newYaw,pitch);

}


void main()
{
  vec4 s = texture(slantMap,texCoord);
  vec4 newLightDir;
  float newYaw;

  vec2 l = lightPosition.xz;
  newYaw = yaw;
  if(doEdit)
    newLightDir = computeLight(s,l,newYaw);
  else
    newLightDir = Rotation3D(yaw,pitch);


  outBufferDir = newLightDir;
  outBufferAngles = vec4(newYaw,pitch,0.0,0.0);
}
