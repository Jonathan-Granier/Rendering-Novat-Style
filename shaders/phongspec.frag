#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec4 lightDir;
    vec3 Normal;
    vec4 cameraDir;
} fs_in;


/**
Compute the half vector between 2 vectors
    v1 : a vector
    v2 : a another vector
**/
vec4 vecH(vec4 v1, vec4 v2)
{
    return normalize(v1+v2);
}

/**
Compute the cosinus of theta between v1 and v2
    v1 : a vector
    v2 : a another vector
**/
float Cos_Theta(vec4 v1, vec4 v2){
    return dot(v1,v2);
}

/**
Compute tan(theta)^2
    cos_Theta : cosinus of theta
**/
float Tan_Theta_2(float cos_Theta){
    return 1/pow(cos_Theta,2.0)-1;
}

/**
Compute F(theta) the Fresnel Coefficient
    cos_Theta : cosinus of theta
    eta : index of refraction
**/
float FresnelCoef(float cos_Theta,float eta){

    float Sin_theta2 = 1 - pow(cos_Theta,2.0);
    float c= pow((pow(eta,2.0)-Sin_theta2),0.5);
    float Fs = pow(abs((cos_Theta - c)/(cos_Theta + c)),2.0);
    float Fp = pow(abs((pow(eta,2.0)*cos_Theta - c)/(pow(eta,2.0)*cos_Theta + c)),2.0);
    return (Fs+Fp)/2.0;
}



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

/**
Compute Specular Lighting
    c : color of object
    n : normal Vector
    l : light Vector
    e : eye Vector
    I : light intensity
    eta : index of refraction
    s : shininess
**/
vec4 Specularlighting(vec4 c, vec4 n, vec4 l, vec4 e, float I,float eta, float s){


    vec4 H=vecH(e,l);
    float cos_Theta = Cos_Theta(H,l);

    float F=FresnelCoef(cos_Theta,eta);

    return F*c*pow(max(dot(n,H),0.0),s)*I;
}







void main()
{
    vec4 color =vec4(0.5,0.5,0.5,1.0);

    float Ka = 0.5;
    float Kd = 1;
    float Ks = .5;
    float lightIntensity = 1.0;
    float eta = 5;
    float shininess= 50.0;

    vec4 n = vec4(normalize(fs_in.Normal),0.0);
    vec4 l=  normalize(fs_in.lightDir);
    vec4 v=  normalize(fs_in.cameraDir);



    vec4 Ca = Ambientlighting(Ka,color,lightIntensity);
    vec4 Cd = DiffuseLighting(Kd,color,n,l,lightIntensity);
    vec4 Cs = Specularlighting(color,n,l,v,lightIntensity,eta,shininess);
    FragColor = Ca+Cd+Cs;
}
