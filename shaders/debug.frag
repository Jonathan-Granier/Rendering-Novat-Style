#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec4 lightDir;
    vec3 Normal;
    vec4 FragPosLightSpace;
    vec2 texCoord;
} fs_in;


uniform sampler2D depthMap;
uniform sampler2D container;
uniform sampler2D awesomeface;

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



float ShadowCalculation(vec4 fragPosLightSpace,vec4 normal,vec4 lightDir){

  // perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords = projCoords * 0.5 + 0.5;



  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  //float closestDepth = texture(depthMap, projCoords.xy).r;
  // get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;
  // check whether current frag pos is in shadow
  float bias = max(0.05 * (1.0 - dot(normal,lightDir)),0.005);


  float shadow = 0;
  vec2 texelSize = 1.0 / textureSize(depthMap, 0);
  for(int x = -1; x <= 1; x++){
    for(int y = -1 ; y <= 1; y++){
      float pcfDepth = texture (depthMap,projCoords.xy + vec2(x,y) * texelSize).r;
      shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    }
  }
  shadow /= 9.0;

  if(projCoords.z > 1.0)
          shadow = 0.0;
  return shadow;

//  return texture(depthMap,fragPosLightSpace.xy).z < fragPosLightSpace.z ? 1.0 : 0.0;


}




void main()
{
//    vec4 color =vec4(0.5,0.5,0.5,1.0);

    vec4 color = mix(texture(container,fs_in.texCoord),texture(awesomeface,fs_in.texCoord),0.4);

    float Ka = 0.5;
    float Kd = 1;
    float Ks = .5;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(fs_in.Normal),0.0);
    vec4 l=  normalize(fs_in.lightDir);


    float shadow = ShadowCalculation(fs_in.FragPosLightSpace,n,l);
    vec4 Ca = Ambientlighting(Ka,color,lightIntensity);
    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);

/**
    if(shadow == 1.0){
        FragColor = vec4(1.0,0,0,1.0);
    }
    else
    {
        FragColor = Ca+(Cd * (1.0-shadow));
    }
/**/
    FragColor = color;
}


