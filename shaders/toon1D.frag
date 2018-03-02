#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
in vec4 Normal;
in vec3 eyeVector;
in vec4 NormalTest;


uniform vec3 lightPosition;
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


void main()
{

  vec4 n = normalize(Normal);
  vec4 l= vec4(normalize(lightPosition),0.0);
    float intensity;

    intensity = dot(l,n);
    vec4 color = vec4(intensity,intensity,intensity,1.0);
    if(intensity > 0.20 && intensity < 0.30){
        color = vec4(0.7,0.7,0.7,1.0f);
        //color = vec4(1.0,0,0,1.0);
    }

    FragColor = color;
}
