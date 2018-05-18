#version 330 core

out vec4 FragColor;



in vec4 lightDir;
in vec3 Normal;
in vec2 texCoord;

uniform bool doShadow;
uniform int typeShading;
uniform sampler2D depthMap;
uniform sampler2D parallaxMap;
/**
Compute the ambient lighting
    k : Coefficient
    c : color of object
    I : light intensity
**/
vec4 Ambientlighting(float k, vec4 c, float I){
    return k*c*I;
}


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

vec4 DiffuseLighting2(float k,vec4 c, vec4 n , vec4 l, float I){
  return k*c*(dot(n,l)*0.5 + 0.5) * I;
}

vec4 DiffuseLighting3(float k,vec4 c, vec4 n , vec4 l, float I){
  return k*c*(abs(dot(n,l))) * I;
}



float ShadowCalculation(vec4 fragPosLightSpace){
  // perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;
  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(depthMap, projCoords.xy).r;
  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

  return shadow;
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

    float Ka = 0.5;
    float Kd = 1;
    float Ks = .5;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(Normal),0.0);
    vec4 l=  normalize(lightDir);


    vec4 Ca = Ambientlighting(Ka,color,lightIntensity);
    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    //vec4 Cd2 = DiffuseLighting2(Kd,color,n,l,lightIntensity);

    if(typeShading == 0){
      Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    }
    if(typeShading == 1){
      Cd = DiffuseLighting2(Kd,color,n,l,lightIntensity);
    }
    if(typeShading == 2){
       Cd = DiffuseLighting3(Kd,color,n,l,lightIntensity);
    }
    float shadow = pow((shadow() + 1) * 0.5,(1.0/2.2));

    if(doShadow)
       FragColor = shadow*Cd;
    else
       FragColor = Cd;

    //FragColor = vec4(1.0,0.0,0.0,1.0);
}






