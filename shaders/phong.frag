#version 330 core

out vec4 FragColor;



in VS_OUT {
    vec4 lightDir;
    vec3 Normal;
} fs_in;


uniform sampler2D depthMap;

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




void main()
{
    vec4 color =vec4(1.0,1.0,1.0,1.0);

    float Ka = 0.5;
    float Kd = 1;
    float Ks = .5;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(fs_in.Normal),0.0);
    vec4 l=  normalize(fs_in.lightDir);


    vec4 Ca = Ambientlighting(Ka,color,lightIntensity);
    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    FragColor = Cd;
    //FragColor = vec4(1.0,0.0,0.0,1.0);
}






