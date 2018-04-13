#version 330 core
layout(location = 0) out float outBuffer;

in vec2 texCoord;


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

float sinY(vec2 t){
  return (sin(t.y*20)*10);
}


float anneau(vec2 t){

  vec2 center = vec2(0.5,0.5);
  vec2 s = t-center;
  float distance =  sqrt(s.x*s.x + s.y*s.y);

  return sin(distance*20)*10;

}



void main()
{
  float p = perlin(texCoord);
  outBuffer = anneau(texCoord);
}


