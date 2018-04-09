#version 330 core

out vec4 FragColor;


in vec4 lightDir;
in vec3 normal;
in vec2 texCoord;


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
    vec4 color =vec4(1.0,1.0,1.0,1.0);


    float Kd = 1;
    float lightIntensity = 1.0;

    vec4 n = vec4(normalize(normal),0.0);
    vec4 l = normalize(lightDir);

    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    FragColor = vec4(0,1,0,0);
    if(l==0){
      FragColor = vec4(1,0,0,0);
    }

    FragColor = Cd;
}


