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

vec4 watercolor(float density, vec4 color){
  float d = density;
  vec4 c = color;

  return c-(c-c*c)*((1-2*d));
}



void main()
{

  vec4 color;
  float Kd = 1;
  float lightIntensity = 1.0;

  vec4 n = vec4(normalize(normal),0.0);
  vec4 l = normalize(lightDir);

  float Cd;




  Cd = texture(shadingMap,texCoord).r;


  //float shadow = pow((shadow() + 1) * 0.5,(1.0/2.2));
  float shadow = (shadow()+1) * 0.5; // Watercolor



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
  if(doShadow)
     color = shadow*color;

  FragColor = color;
}


