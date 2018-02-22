#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
in vec4 Normal;
in vec3 eyeVector;
in vec4 NormalTest;


uniform vec3 lightPosition;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;


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


void main()
{


  vec4 colorObj = mix(texture(texture_normal1,TexCoord),texture(texture_normal2,TexCoord),0.2);

  float Ka = 0.5;
  float Kd = 0.5;
  float lightIntensity = 1.0;

  vec4 n = normalize(Normal);
  vec4 l= vec4(normalize(lightPosition),0.0);

  vec4 Ca = Ambientlighting(Ka,colorObj,lightIntensity);
  vec4 Cd = DiffuseLighting(Kd,colorObj,n,l,lightIntensity);

  //FragColor = Ca+Cd;
  //FragColor = vec4(0.4,0.1,0.7,1.0);
  FragColor = n;
}
