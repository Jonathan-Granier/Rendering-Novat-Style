#version 450 core

out vec4 FragColor;

in vec2 texcoord;

uniform sampler2D normalMap;
uniform sampler2D shadingMap;
uniform mat3 normalMat;
uniform mat4 mdvMat;
uniform bool firstMap;
uniform int shadeSelector;

// Light !
uniform vec3 lightPosition;
uniform sampler2D shadeLightMap;

/**
Compute the diffuse lighting
    k : Coefficient
    c : color of object
    n : normal Vector
    l : light Vector
    I : light intensity
**/
float DiffuseLighting( vec4 n, vec4 l){
    return max(dot(n,l),0);
}


float watercolor(float blur, float detail){
  float b = blur;//*(bmax-bmin) + bmin;
  float d = detail;

  return d-(d-d*d)*((1-2*b));
}



float overlay(float blur, float detail){
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

float softlight(float blur, float detail , float f){
  float b = blur;
  float d = detail;
  if(detail>0.5){
    return 1-(1-b)*(1-(d-0.5));
  }
  return b*(d+0.5);
}



float hardlight(float blur, float detail , float f){
  float b = blur;
  /**
  if(blur <= 0.5)
      b = blur - f*blur + f;
  else
      b = blur - f*blur;
  /**/

  float d = detail;
  if(detail>0.5){
    return 1-2*(1-d)*(1-b);
    //return 1-(1-2*(b-0.5))*(1-t);
  }
  return 2*b*d;
}


void main()
{
    vec4 n = normalize(vec4(normalMat * texture(normalMap,texcoord).xyz,0));
    //vec4 l = normalize(mdvMat * normalize(vec4(lightPosition,0)));
    vec4 l = normalize(mdvMat * normalize(texture(shadeLightMap,texcoord)));
    float Cd;


      Cd = DiffuseLighting(n,l);

/**/


    if(!firstMap && shadeSelector == 0)
    {
      float pCd = texture(shadingMap,texcoord).r;
      Cd = pCd;
      //Cd = overlay(pCd,Cd);
      //Cd = (Cd+pCd/2.0)/2.0;
    }
    else if(!firstMap && shadeSelector == 2)
    {
      float pCd = texture(shadingMap,texcoord).r;
      Cd = overlay(Cd,pCd);
      //Cd = overlay(pCd,Cd);
      //Cd = (Cd+pCd/2.0)/2.0;
    }
    else if(!firstMap && shadeSelector == 3)
    {
      float pCd = texture(shadingMap,texcoord).r;
      Cd =  watercolor(pCd,Cd);
      //Cd = overlay(pCd,Cd);
      //Cd = (Cd+pCd/2.0)/2.0;
    }
/**/
    FragColor = vec4(Cd,Cd,Cd,0);
}
