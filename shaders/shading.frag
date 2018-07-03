#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D normalMap;
uniform sampler2D shadingMap;
uniform mat3 normalMat;
uniform mat4 mdvMat;
uniform bool firstMap;
uniform int shadeSelector;

// Light !
uniform sampler2D shadeLightMap;

/**
Compute the Lambertien
    n : normal Vector
    l : light Vector
**/
float Lambertien( vec4 n, vec4 l){
    return max(dot(n,l),0);
}


float watercolor(float detail, float blur ){
  float b = blur;//*(bmax-bmin) + bmin;
  float d = detail;

  return d-(d-d*d)*((1-2*b));
}



float overlay(float detail, float blur){
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


void main()
{
    vec4 n = normalize(vec4(normalMat * texture(normalMap,texCoord).xyz,0));
    vec4 l = normalize(mdvMat * normalize(texture(shadeLightMap,texCoord)));
    float cCd;


      cCd = Lambertien(n,l);

/**/


    if(!firstMap && shadeSelector == 0)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd = pCd;
    }
    else if(!firstMap && shadeSelector == 2)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd = overlay(pCd,cCd);

    }
    else if(!firstMap && shadeSelector == 3)
    {
      float pCd = texture(shadingMap,texCoord).r;
      cCd =  watercolor(cCd,pCd);
      //Cd = overlay(pCd,Cd);
      //Cd = (Cd+pCd/2.0)/2.0;
    }
/**/
    FragColor = vec4(cCd,cCd,cCd,0);

}
