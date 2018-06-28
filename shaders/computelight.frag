/**
  Created by Jonathan Granier
  Last shader of the pipeline and only shader with the mesh.
  Mix the mesh with the shading , the shadows and the color.
**/


#version 330 core




out vec4 FragColor;


in vec4 lightDir;
in vec3 normal;
in vec2 texCoord;
uniform bool doShadow;
uniform sampler2D mergeShadowMap;
uniform sampler2D shadingMap;
uniform sampler2D colorMapTex;
uniform sampler2D celShadingTex;
uniform vec4      plainColor;
uniform vec4      waterColor;
uniform int       colorSelector;



// return value of shadow beetween [0,1] with antialiasing
float shadow(){
  int max = 1;
  int min = -max;

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

/* watercolor function  --> show report for more information (p. 21-22) or the paper watercolor by [Bousseau et al].
 TLDR : just a overlay function that mix 2 value.
*/
vec4 watercolor(vec4 color,float density ){
  float d = density;
  vec4 c = color;

  return c-(c-c*c)*((1-2*d));
}


vec3 hsv2rgb(vec3 hsv)
{
    float      hh, p, q, t, ff;
    int        i;
    vec3         rgb;



    if(hsv.y <= 0.0) {
        rgb.r = hsv.y;
        rgb.g = hsv.y;
        rgb.b = hsv.y;
        return rgb;
    }
    hh = hsv.x;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = hh;
    ff = hh - i;
    p = hsv.z * (1.0 - hsv.y);
    q = hsv.z * (1.0 - (hsv.y * ff));
    t = hsv.z * (1.0 - (hsv.y * (1.0 - ff)));

    switch(i) {
    case 0:
        rgb.r = hsv.z;
        rgb.g = t;
        rgb.b = p;
        break;
    case 1:
        rgb.r = q;
        rgb.g = hsv.z;
        rgb.b = p;
        break;
    case 2:
        rgb.r = p;
        rgb.g = hsv.z;
        rgb.b = t;
        break;

    case 3:
        rgb.r = p;
        rgb.g = q;
        rgb.b = hsv.z;
        break;
    case 4:
        rgb.r = t;
        rgb.g = p;
        rgb.b = hsv.z;
        break;
    case 5:
    default:
        rgb.r = hsv.z;
        rgb.g = p;
        rgb.b = q;
        break;
    }
    return rgb;
}


vec3 xtoon(float cd){

}




void main()
{


  vec4 n = vec4(normalize(normal),0.0);
  vec4 l = normalize(lightDir);

  float Cd;
  Cd = texture(shadingMap,texCoord).r;


  float shadow = (shadow()+1) * 0.5;


  if(doShadow)
    Cd = shadow*Cd;


  // Select the color methode

  vec4 color;
  if(colorSelector == 0){
    color = Cd*plainColor;
  }
  else if(colorSelector == 1){
    color = watercolor(waterColor,Cd);
  }
  else if(colorSelector == 2){
    color = texture(colorMapTex,vec2(Cd ,0.5));
  }
  else if(colorSelector == 3){
    color = texture(celShadingTex,vec2(Cd,0.5));
  }


  FragColor = color;
}


