#version 330 core

out vec4 FragColor;


in vec2 texCoord;

uniform sampler2D curvatureMap;
uniform sampler2D normalMap;

#define PI 3.14159265359
float eps = 1e-2;


float cosTheta(vec2 v1, vec2 v2){
  return dot(v1,v2)/(length(v1) * length(v2));
}



void main()
{
  vec4 c = texture(curvatureMap,  texCoord);
  vec4 n = texture(normalMap,     texCoord);

  vec2 c1 = c.xy;
  vec2 c2 = vec2(c1.y,-c1.x);
  float k1 = c.z;
  float k2 = c.w;



 // c = vec4(c2.x,c2.y,k1,k2);

  float t = cosTheta(n.xy,c1);

 // FragColor = c;
  //test 1
 //if((abs(t) >= 1-eps && abs(t) <= 1+eps) || length(n.xy)<=0.1){
  if((abs(t) >= cos(PI/4.0)) || length(n.xy)<=0.1){
    //FragColor = vec4(0,1,0,0);
    FragColor = vec4(c1.x,c1.y,k1,k2);
  }
  else
  {
    FragColor = vec4(c2.x,c2.y,k1,k2);
    //FragColor = vec4(1,0,0,1);
  }
  /*if(length(n.xy) <= .1){
    FragColor = vec4(0,0,1,1);
  }*/
   //FragColor = c;
}




