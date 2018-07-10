#version 330 core
layout(location = 0) out vec4 outBufferDir;

in vec2 texCoord;

uniform sampler2D slantMap;

uniform vec3 lightDirection;
uniform float yaw;
uniform float pitch;
uniform float threshold;
uniform bool doEdit;


#define PI 3.14159265359
#define PI2 PI/2.0



float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}

float modulo(float y){
  return y - 2*PI*floor(y/(2.0 * PI));
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


vec4 computeLight(in vec4 s,in vec2 l, inout float newYaw){
  vec2 normL = normalize(l);
  vec2 slant = normalize(vec2(s.x,-s.y)) ; // Because the light and the slant have not the same Y axis


  if(cosTheta(normL,slant) < 0){
     slant = -slant;
  }
  float normS = clamp(s.z,0,1);

  if(normS <= 0){
    slant = normL;
  }


  float det = normL.x * slant.y - normL.y* slant.x;
  float thetaSign = (det/abs(det));

  if(isnan(thetaSign)){

    thetaSign = 1;
  }
  float theta = thetaSign* (acos(cosTheta(normL,slant)));


  theta = theta * smoothTheta(theta)*normS;
  newYaw += theta;
  newYaw = modulo(newYaw);
  return Rotation3D(newYaw,pitch);

}



void main()
{
  vec4 s = texture(slantMap,texCoord);
  vec4 newLightDir;

  vec2 l = lightDirection.xz;
  float newYaw = yaw;
  if(doEdit)
    newLightDir = computeLight(s,l,newYaw);
  else
    newLightDir = Rotation3D(yaw,pitch);


  outBufferDir = newLightDir;

}
