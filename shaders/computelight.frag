#version 330 core

out vec4 FragColor;


in vec4 lightDir;
in vec3 normal;
in vec2 texCoord;
uniform sampler2D parallaxMap;

/**
Compute the diffuse lighting
    k : Coefficient
    c : color of object
    n : normal Vector
    l : light Vector
    I : light intensity
**/
vec4 DiffuseLighting(float k, vec4 c, vec4 n, vec4 l, float I){
    return k*c*max(dot(n,l),0.0) * I;
}


float shadow(){
  int min = -0;
  int max = 0;


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

    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);


    //FragColor = vec4(p,0,0,0);
    float shadow = pow((shadow() + 1) * 0.5,(1.0/2.2));
    FragColor = shadow*Cd;
    //FragColor = shadow()*color;
}


