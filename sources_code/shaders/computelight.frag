/**
* @file computelight.frag
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief Last shader of the pipeline and only shader with the mesh.
*         Mix the mesh with the shading , the shadows and the color.
*
*
* Input texture :
*     Final shadow map.
*     Final shading map.
* Output :
*     A Color.
*
* SHADER NUMBER 11.
**/

#version 330 core

// The output, a color
out vec4 FragColor;

// The global light direction
in vec4 lightDir;
// The normal of the mesh
in vec3 normal;
// The texture coordinates of the mesh
in vec2 texCoord;
// If true, the shadows are add to the shading.
uniform bool doShadow;
// If true, do a classic lambertien with the native normal and the global light direction instead of our methode.
uniform bool doDefaultShading;

// TEXTURE NUMBER 9. The final shadow map after the merge between the scales.
uniform sampler2D mergeShadowMap;
// TEXTURE NUMBER 10. The final shading map after the merge between the scales.
uniform sampler2D shadingMap;

// Color map texture. (a color gradient)
uniform sampler2D colorMapTex;
// cel-shading texture
uniform sampler2D celShadingTex;
// The native height Map. (For know the altitude)
uniform sampler2D heightMap;

// The color for plain color colorization method.
uniform vec4      plainColor;
// The color for watercolor colorization method.
uniform vec4      waterColor;

/** The colorization methode selected:
  *       0: plain color.
  *       1: water color.
  *       2: color map.
  *       3: cel-shading.
  */
uniform int       colorSelector;

// The max altitude of the heightMap.
uniform float     ymax;
// The min altitude of the heightMap.
uniform float     ymin;


/*-------------------------------------
  SHADOW
    Compute the value of shadow of the current pixel.

  Output
    value of shadow between 0 and 1 with antialiasing
*/
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

/*-------------------------------------
  WATERCOLOR
  Show report for more information (p. 21-22) or the paper watercolor by [Bousseau et al].
  TLDR : just a overlay function that mix 2 values.

  Input
    vec4 color      a constante color.
    float density   a value between 0 and 1.

  Output
    vec3            a color.
*/
vec4 watercolor(vec4 color,float density ){
  float d = density;
  vec4 c = color;

  return c-(c-c*c)*((1-2*d));
}

/*-------------------------------------
  HSV2RGB
  Convert a hsv value to a rgb value
  Input
    vec3 hsv :
      h angle in degrees
      s a value between 0 and 1
      v a value between 0 and 1


  Output
    vec3 : rgb value between 0 and 1.
*/
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
    i = int(hh);
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


/*-------------------------------------
  Color with a xtoon , scale on shading (cd) and current height.

  h between 220 - 195 scale on height
  s between 0 - 1
  v between 0.5 - 1.0 scale on shading

  Input
    float cd : shading value

  Output
    vec4 : a color.
*/


vec4 xtoon(float cd){
  float height = texture(heightMap,texCoord).r;
  height = (height - ymin)/(ymax-ymin);

  vec3 hsv;
  hsv.x = 220.0 - 25.0*height;
  hsv.y = 1-cd;
  hsv.z = 0.4 + cd*0.6;


  //hsv = vec3(220,0.6,0.7);
  vec3 rgb = hsv2rgb(hsv);
  return vec4(rgb,1);

}

/**
Compute the Lambertien
    Input :
      n : normal Vector
      l : light Vector
    Output :
      A value between 0 and 1.
**/
float Lambertien( vec4 n, vec4 l){
    return max(dot(n,l),0);
}


void main()
{


  vec4 n = vec4(normalize(normal),0.0);
  vec4 l = normalize(lightDir);

  float Cd;
  if(doDefaultShading)
    Cd = Lambertien(n,l);
  else
    Cd = texture(shadingMap,texCoord).r;


  float shadow = (shadow()+1) * 0.5;


  if(doShadow)
    Cd = shadow*Cd;


  // Select the color methode
  vec4 color;
  if(colorSelector == 0){
    color = plainColor *Cd;
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


  //FragColor = xtoon(Cd);
  FragColor = color;
}
