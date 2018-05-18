#version 330 core

out vec4 FragColor;


in vec4 lightDir;
in vec3 normal;
in vec2 texCoord;
uniform bool doShadow;
uniform int typeShading;
uniform sampler2D parallaxMap;
uniform sampler2D shadingMap;
uniform sampler2D degrade_neige;
/**
Compute the diffuse lighting
    k : Coefficient
    c : color of object
    n : normal Vector
    l : light Vector
    I : light intensity
**/
// Lambertien
vec4 DiffuseLighting(float k, vec4 c, vec4 n, vec4 l, float I){
    return k*c*max(dot(n,l),0.0) * I;
}

//Cosin Shading
vec4 DiffuseLighting2(float k,vec4 c, vec4 n , vec4 l, float I){
  return k*c*(dot(n,l)*0.5 + 0.5) * I;
}
//????
vec4 DiffuseLighting3(float k,vec4 c, vec4 n , vec4 l, float I){
  return k*c*(abs(dot(n,l))) * I;
}

float shadow(){
  int min = -1;
  int max = 1;


  float shadow = 0;
  vec2 texelSize = 1.0 / textureSize(parallaxMap, 0);
  for(int x = min; x <= max; x++){
    for(int y = min ; y <= max; y++){
      shadow +=  texture(parallaxMap,texCoord + vec2(x,y)*texelSize).r;
    }
  }
  shadow /= pow(max+abs(min)+1,2.0);

  return shadow;

}



void main()
{
    vec4 color =vec4(1.0,1.0,1.0,1.0);


    float Kd = 1;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(normal),0.0);
    vec4 l = normalize(lightDir);

    vec4 Cd;
    if(typeShading == 0){
      Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    }
    if(typeShading == 1){
      Cd = DiffuseLighting2(Kd,color,n,l,lightIntensity);
    }
    if(typeShading == 2){
       Cd = DiffuseLighting3(Kd,color,n,l,lightIntensity);
    }
    //FragColor = vec4(p,0,0,0);



    Cd = texture(shadingMap,texCoord).r * color;

    //Cd = Cd*color;
    //float shadow = pow((shadow() + 1) * 0.5,(1.0/2.2));
   // float shadow = shadow()/2.0;
    if(doShadow)
       FragColor = shadow()*Cd;
    else
       //FragColor = texture(degrade_neige,vec2(texture(shadingMap,texCoord).r ,0.5));
      FragColor = Cd;

    //FragColor = shadow()*color;
}


