/**
  Created by Jonathan Granier
  Shader for draw a texture select by selectTexture
  Show the value pointed by the mousse.

**/





#version 330 core


out vec4 FragColor;

in vec2 texCoord;


uniform sampler2D heightMap;
uniform sampler2D editHeightMap;
uniform sampler2D normalMap;
uniform sampler2D slantMap;
uniform sampler2D shadeLightMap;
uniform sampler2D shadowLightMap;
uniform sampler2D parallaxMap;
uniform sampler2D morphoErosionMap;
uniform sampler2D morphoDilationMap;
uniform sampler2D mergeShadowMap;
uniform sampler2D shadingMap;

uniform sampler2D asciiTex;

uniform float ymin;
uniform float ymax;
uniform vec2 moussePos;
/*
  Select the texture to draw :
  0 - heightMap
  1  - editHeightMap
  2  - normalMap
  3  - slantMap
  4  - shadeLightMap
  5  - shadowLightMap
  6  - parallaxMap
  7  - morphoErosionMap
  8  - morphoDilationMap
  9  - mergeShadowMap
  10 - shadingMap
*/

uniform int selectTexture;

/* API to diplay text from Astor Bizard
  https://www.shadertoy.com/view/MdycDK
*/

#define BLACK		vec3(0)
#define WHITE		vec3(1)
#define GREY(A)		vec3(A)
#define RED  		vec3(1,0,0)
#define GREEN		vec3(0,1,0)
#define BLUE 		vec3(0,0,1)
#define TURQUOISE 	vec3(0,1,1)
#define PURPLE		vec3(1,0,1)
#define YELLOW 		vec3(1,1,0)
#define VIOLET 		vec3(.5,0,1)
#define LIGHT_BLUE	vec3(0,.5,1)
#define LIGHT_GREEN	vec3(.5,1,0)
#define LAGOON		vec3(0,1,.5)
#define ORANGE		vec3(1,.5,0)
#define MAGENTA		vec3(1,0,.5)
#define PINK		vec3(1,.3,.7)


#define POW2(A) ((A)*(A))
#define POW3(A) (POW2(A)*(A))
#define POW4(A) (POW3(A)*(A))

#define PI 3.141593

#define R vec3(1146.0,751.0,0)



int intLogBase(float base, float x){
    if(x<1.) return 0;
    int res = 0;
    while(x>=base){
        res++;
        x = floor(x/base);
    }
    return res;
}

// Periodic function __|__|__|__|__
// s : dirac compression
float periodicDirac(float x, float period, float s){
  return pow(abs(cos(x*(PI/period))),s);
}

////////////////////////////////

#define setDisplayUV(pos,scale) ((gl_FragCoord.xy-pos*(R.xy/vec2(640,360)))/(scale*R.x))
#define nextLine(uv,pos,scale)	pos = vec2(pos.x,pos.y-scale*500.);\
                uv = setDisplayUV(pos,scale);

#define DEF_CHAR_WIDTH .8
#define DEF_CHAR_HEIGHT 1.
#define DEF_CHAR_OFFSET .3

void writeChar(int character, vec3 char_color,
               float w, float h, float x_offset, // Dimensions of the bbox of the char
               inout vec2 uv, sampler2D font_tex, inout vec3 color){
      #define getFont(uv,character) texture(font_tex, (uv+vec2(mod(character,16.),15.-floor(character/16.)))/16.).r
    uv.x += x_offset;
      if(uv.x>0. && uv.x<w && uv.y<h && uv.y>0.)
            // We are inside the bbox, display the char
            color = mix(color,char_color, getFont(uv,float(character)) );
    uv.x -= w; // move uv for next char
}

#define writeNormalChar(character, char_color, uv, font_tex, color)\
      writeChar(character,char_color,DEF_CHAR_WIDTH,DEF_CHAR_HEIGHT,DEF_CHAR_OFFSET,uv,font_tex,color)

#define writeText(text, text_size, text_color, uv, font_tex, color,pos,scale)\
  for(int i=0;i<text_size;i++){\
        writeNormalChar(text[i],text_color,uv,font_tex,color);\
        int chars_per_line = int((1.-pos.x/640.)/(scale*(DEF_CHAR_WIDTH-DEF_CHAR_OFFSET)));\
        if((i+1)%chars_per_line==0){\
            nextLine(uv,pos,scale);\
        }\
    }

#define writeWord(word, word_size, word_color, uv, font_tex, color)\
  for(int i=0;i<word_size;i++)\
        writeNormalChar(word[i],word_color,uv,font_tex,color);

void writeNumber(float number, int min_int_digits, int dec_digits, vec3 num_color,
                 inout vec2 uv, sampler2D font_tex, inout vec3 color){


    if(isnan(number)){
      int[] nan = int[](78,97,78);
        writeWord(nan,3,RED,uv,font_tex,color);
    }
    else if(isinf(number)){
      int[] inf = int[](73,110,102);
        writeWord(inf,3,RED,uv,font_tex,color);
    }
    else{
        float x;
        #define WRITE_INTEGER_NUMBER(NUMBER)\
          x = pow(10.,digits-1.);\
            while(digits>0.){\
                writeNormalChar(48+int(floor(NUMBER/x)),num_color,uv,font_tex,color);\
                NUMBER=mod(NUMBER,x);\
                digits--;\
                x /= 10.;\
            }
        bool neg = number<0.;
        number = abs(number);
        float p = floor(number);
        float f = fract(number);

        // Display the sign
        if(neg)
            writeNormalChar(45,num_color,uv,font_tex,color);

        // Round the number to the right number of decimal digits
        float decimal_digits_factor = pow(10.,float(dec_digits));
        f = round(f*decimal_digits_factor);
        if(f == decimal_digits_factor){
            f = 0.;
            p += 1.;
        }

        // Display the integer part
        float digits = float(intLogBase(10.,p)+1);
          // Fill with zeros to match min digits
        for(int i=0;i<min_int_digits-int(digits);i++)
            writeNormalChar(48,num_color,uv,font_tex,color);
        WRITE_INTEGER_NUMBER(p);

        if(dec_digits>0){
          // Display the dot
          writeChar(46,num_color,.65,1.,.45,uv,font_tex,color);

            // Display the decimal part
            digits = float(dec_digits);
            WRITE_INTEGER_NUMBER(f);
        }
    }

}





#define WriteNumber(number,min_int_digits,dec_digits,number_color) writeNumber(number,min_int_digits,dec_digits,number_color,uv,asciiTex,color)
#define WriteChar(char,char_color) writeNormalChar(char,char_color,uv,asciiTex,color)


// Display the value of a pixel
void displayVec4(inout vec3 color, vec4 v){
/**/
  vec3 fontColor = TURQUOISE;
  vec2 pos = vec2(10,350);
  float scale = 1./50.;
  vec2 uv = setDisplayUV(pos,scale);
  int comma = 44;
  WriteNumber(v.x,1,5,fontColor);
  WriteChar(comma,fontColor);
  WriteNumber(v.y,1,5,fontColor);
  WriteChar(comma,fontColor);
  WriteNumber(v.z,1,5,fontColor);
  WriteChar(comma,fontColor);
  WriteNumber(v.a,1,5,fontColor);
/**/
}

















void main()
{
    vec4 valueDisplay;
    vec2 texCoordDisplay = vec2(moussePos.x/1171.0,moussePos.y/760.0);



    if(selectTexture == 0){
      float grayValue = texture(heightMap, texCoord).r;
      grayValue = (grayValue - ymin)/(ymax-ymin);
      FragColor = vec4(grayValue,grayValue,grayValue,1.0);

      float grayValueDisplay = texture(heightMap, texCoordDisplay).r;
      valueDisplay = vec4(grayValueDisplay,grayValueDisplay,grayValueDisplay,1.0);

    }
    if(selectTexture == 1){
      float grayValue = texture(editHeightMap, texCoord).r;
      grayValue = (grayValue - ymin)/(ymax-ymin);
      FragColor = vec4(grayValue,grayValue,grayValue,1.0);

      float grayValueDisplay = texture(editHeightMap, texCoordDisplay).r;
      valueDisplay = vec4(grayValueDisplay,grayValueDisplay,grayValueDisplay,1.0);

    }
    if(selectTexture == 2){
      FragColor = texture(normalMap,     texCoord);
      valueDisplay = texture(normalMap, texCoordDisplay);
    }
    if(selectTexture == 3){
      FragColor = texture(slantMap,  texCoord);
      valueDisplay = texture(slantMap, texCoordDisplay);
    }
    if(selectTexture == 4){
      FragColor = texture(shadeLightMap,      texCoord);
      valueDisplay = texture(shadeLightMap, texCoordDisplay);
    }
    if(selectTexture == 5){
      FragColor = texture(shadowLightMap,      texCoord);
      valueDisplay = texture(shadowLightMap, texCoordDisplay);
    }
    if(selectTexture == 6){
      FragColor = texture(parallaxMap,      texCoord);
      valueDisplay = texture(parallaxMap, texCoordDisplay);
    }
    if(selectTexture == 7){
      FragColor = texture(morphoErosionMap,      texCoord);
      valueDisplay = texture(morphoErosionMap, texCoordDisplay);
    }
    if(selectTexture == 8){
      FragColor = texture(morphoDilationMap,      texCoord);
      valueDisplay = texture(morphoDilationMap, texCoordDisplay);
    }
    if(selectTexture == 9){
      FragColor = texture(mergeShadowMap,      texCoord);
      valueDisplay = texture(mergeShadowMap, texCoordDisplay);
    }
    if(selectTexture == 10){
      FragColor = texture(shadingMap,      texCoord);
      valueDisplay = texture(shadingMap, texCoordDisplay);
    }
    displayVec4(FragColor.xyz,valueDisplay);

}
