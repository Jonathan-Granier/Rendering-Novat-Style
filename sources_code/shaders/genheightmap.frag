#version 330 core
layout(location = 0) out float outBuffer;

in vec2 texCoord;
#define PI 3.14159265359

float hash( vec2 p ) {                          // rand in [-1,1]
    p = vec2( dot(p,vec2(127.1,311.7)),
              dot(p,vec2(269.5,183.3)) );
    return -1. + 2.*fract(sin(p+20.)*53758.5453123).x;
}

float noise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );

    vec2 u = f*f*(3.-2.*f);

    return mix( mix( hash( i + vec2(0,0) ),
                     hash( i + vec2(1,0) ), u.x),
                mix( hash( i + vec2(0,1) ),
                     hash( i + vec2(1,1) ), u.x), u.y);
}

// -----------------------------------------------

float perlin(vec2 uv )
{
    float f;

    uv *= 8.0;
    mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );
    f  = 0.5000*noise( uv ); uv = m*uv;
    f += 0.2500*noise( uv ); uv = m*uv;
    f += 0.1250*noise( uv ); uv = m*uv;
    f += 0.0625*noise( uv ); uv = m*uv;
    f = 0.5 + 0.5*f;

    return f;
}


float sinXY(vec2 t){
  return (sin(t.y*t.x*20)*10);
}

float gaussienne(float x){
  return 2/(sqrt(2*PI)) * exp(-(x*x)/(0.2));
}

float sinYF(vec2 t){
  float r = 1024;
  float y0 = 0;
  float x0 = 0;
  float x1 = 0;
  float xy0 = 0;
  float xy1 = 0;
  if (t.x*r > 300 && t.x*r < 600 && t.y*r >= 500 && t.y*r <= 600){

    float y = t.y- 550.0/r;
    y0 = gaussienne(y*30.0)*30;
  }

  if (t.x*r > 200 && t.x*r < 300 && t.y*r >= 500 && t.y*r <= 800){

    float x = t.x - 250.0/r;
    x0 = gaussienne(x*50)*30;
  }
  if (t.x*r > 600 && t.x*r < 700 && t.y*r >= 500 && t.y*r <= 800){

    float x = t.x - 650.0/r;
    x1 = gaussienne(x*50)*30;
  }


  if (t.x*r > 50 && t.x*r < 150 && t.y*r >= 500 && t.y*r <= 700){

    float x = t.x - 100.0/r;
    float y = t.y - 600.0/r;
    xy0 = gaussienne((x+y)*50)*30;
  }

  if (t.x*r > 750 && t.x*r < 850 && t.y*r >= 500 && t.y*r <= 700){

    float x = t.x - 800.0/r;
    float y = t.y - 600.0/r;
    xy1 = gaussienne((x-y)*50)*30;
  }



  return (sin((t.y)*5)*300) + y0 + x0 + x1 + xy0+xy1;
}

float sinY(vec2 t){
    return sin((t.y+cos(t.x))*5)*300;
}


float anneau(vec2 t){

  vec2 center = vec2(0.5,0.5);
  vec2 s = t-center;
  float distance =  sqrt(s.x*s.x + s.y*s.y);

  return sin(distance*20)*100;

}





void main()
{
  float p = perlin(texCoord);
  outBuffer = anneau(texCoord);
}


