#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
in vec4 Normal;
in vec4 lightVector;

uniform sampler2D container;
uniform sampler2D awesomeface;
uniform sampler2D neige_ombre;
uniform sampler2D degrade_debug;
uniform sampler2D flat_color_debug;
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
    vec4 l = normalize(lightVector);
    float intensity;

    intensity = dot(l,n);
    if(intensity <= 0.0f){
      intensity = 0.001f;
    }
    // ma texture est inversé , TODO la refaire
    intensity = intensity * -1.0f +1.0f;

    //vec4 colorObj = mix(texture(container,TexCoord),texture(awesomeface,TexCoord),0.2);
    vec2 coordToon1D = vec2(intensity,0);


    vec4 color = texture(neige_ombre,coordToon1D);
    //vec4 color = vec4(-1*coordToon1D,0,1.0);
    FragColor = color;
}
