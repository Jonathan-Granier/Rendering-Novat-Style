/**
* @file shadowlight.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Directs localy the light with the slant. Compute the light for the shading only
*
* Input texture :
*     The slant map.
* Output :
*     A 3D vector (Same orthonormal coordinate system with the normal).
*
*  SHADER NUMBER 4. (It's the same shader that shadowlight.frag (Number 5) but the separation allows to make different computation. )
**/






#version 330 core
// The Output : 3D normal vector
layout(location = 0) out vec4 outBufferDir;
// The texture coordinate
in vec2 texCoord;
// TEXTURE NUMBER 3. Slant map.
uniform sampler2D slantMap;

// The global light direction.
uniform vec3 lightDirection;
// The yaw angle of the global light.
uniform float yaw;
// The pitch angle of the global light.
uniform float pitch;
// The maximum angle of correction of the light (between 0 and PI/2).
uniform float threshold;
// If false, just copy the global light direction in the ouput.
uniform bool doEdit;


#define PI 3.14159265359
#define PI2 PI/2.0


/*-------------------------------------
* COSTHETA
*
* Compute the cosinus of two 2D vector
* Input
*   v1    2D vector.
*   v2    2D vector.
* Ouput
*   The cosinus between v1 and v2.
*/
float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}

/*-------------------------------------
* MODULO
*
* Compute the modulo 2 PI of a angle.
* Input
*   y     A angle in radian.
* Ouput
*   float     y mod 2PI.
*/
float modulo(float y){
  return y - 2*PI*floor(y/(2.0 * PI));
}


/*-------------------------------------
* SMOOTHTHETA
*
* Do a smoothThete , but reverse the value. Show p.19 and p.20 of the report for more information.
* Input
*   theta     A angle in radian.
* Ouput
*   float     theta but smoothed.
*/
float smoothTheta(float theta){

  float f = smoothstep(threshold,PI2,abs(theta));
  return -f+1;

}

/*-------------------------------------
* ROTATION3D
*
* Compute the direction of the light from the two euler angle (yam and pitch)
* Input
*     localYaw      A angle in radian.
*     localPitch    A angle in radian between 0 and PI/2.
*
* Ouput
*     vec4        A 3D normal vector that is the local direction of the light.
*/
vec4 Rotation3D(in float localYaw,in float localPitch){
  vec4 v;

  v.x = cos(localPitch) * cos(localYaw);
  v.y = sin(localPitch);
  v.z = cos(localPitch) * sin(localYaw);
  v.w = 0.0;
  v = normalize(v);

  return v;
}

/*-------------------------------------
* COMPUTELIGHT
*
* Directs localy the light with the slant
* Show p.18 to p.20 of the report to have more information.
* Input
*   s       The slant.
*   l       The global light projected on the plan XY.
*
* Ouput
*   vec4    The local light directs by the slant.
*/
vec4 computeLight(in vec4 s,in vec2 l){
  vec2 normL = normalize(l);
  vec2 slant = normalize(vec2(s.x,s.y));

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
  float newYaw = yaw + theta;
  newYaw = modulo(newYaw);
  return Rotation3D(newYaw,pitch);

}



void main()
{
  vec4 s = texture(slantMap,texCoord);
  vec4 newLightDir;

  vec2 l = lightDirection.xz;
  if(doEdit)
    newLightDir = computeLight(s,l);
  else
    newLightDir = vec4(lightDirection,0);


  outBufferDir = newLightDir;
}
