#version 330 core

out vec4 FragColor;



in vec4 lightDir;
in vec3 Normal;
in vec2 texCoord;

uniform bool doShadow;
uniform sampler2D depthMap;
uniform sampler2D mergeShadowMap;
uniform sampler2D colorMapTex;
uniform sampler2D celShadingTex;
uniform vec4      plainColor;
uniform vec4      waterColor;
uniform int       colorSelector;

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
float DiffuseLighting(vec4 n, vec4 l){
    return max(dot(n,l),0.0);
}

vec4 watercolor(float density, vec4 color){
  float d = density;
  vec4 c = color;

  return c-(c-c*c)*((1-2*d));
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
  vec2 texelSize = 1.0 / textureSize(mergeShadowMap, 0);
  for(int x = min; x <= max; x++){
    for(int y = min ; y <= max; y++){
      shadow +=  texture(mergeShadowMap,texCoord + vec2(x,y)*texelSize).r;
    }
  }
  shadow /= pow(max+abs(min)+1,2.0);

  return shadow;

}



void main()
{

    float Ka = 0.5;
    float Kd = 1;
    float Ks = .5;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(Normal),0.0);
    vec4 l=  normalize(lightDir);


  //  vec4 Ca = Ambientlighting(Ka,color,lightIntensity);
    float Cd = DiffuseLighting(n,l);
    //vec4 Cd2 = DiffuseLighting2(Kd,color,n,l,lightIntensity);
    float shadow = (shadow()+1) * 0.5;
   vec4 color;

    if(doShadow)
       Cd = shadow*Cd;
    if(colorSelector == 0){
      color = Cd*plainColor;
    }
    else if(colorSelector == 1){
      color = watercolor(Cd,waterColor);
    }
    else if(colorSelector == 2){
      color = texture(colorMapTex,vec2(Cd ,0.5));
    }
    else if(colorSelector == 3){
      color = texture(celShadingTex,vec2(Cd,0.5));
    }


    FragColor = color;
}






