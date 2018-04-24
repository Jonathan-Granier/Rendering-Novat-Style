#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform vec2 resolution;

const float eps = 1e-15;





float getTex(float x,float y){
  return texture(heightMap,vec2(x,y)).r;
}



float DX(){

  float x0,x1,x2;
  x0 = getTex(texcoord.x-1.0/resolution.x,texcoord.y);
  x1 = getTex(texcoord.x,texcoord.y);
  x2 = getTex(texcoord.x+1.0/resolution.x,texcoord.y);

  float dx10 = x1 - x0;
  float dx21 = x2 - x1;
  return (dx21+dx10)/2.0;


}

float DY(){
  float y0,y1,y2;
  y0 = getTex(texcoord.x,texcoord.y-1.0/resolution.y);
  y1 = getTex(texcoord.x,texcoord.y);
  y2 = getTex(texcoord.x,texcoord.y+1.0/resolution.y);

  float dy10 = y1 - y0;
  float dy21 = y2 - y1;
  return (dy21+dy10)/2.0;
}


void main()
{
    float height = texture(heightMap, texcoord).r;
    vec4 n = texture(normalMap,texcoord);
    /**
    float dx = dFdxFine(height);
    float dy = dFdyFine(height);
    /**/
    float dx = DX();
    float dy = DY();
    /**/


    if(abs(dx) <= eps){
      dx = 0;
    }
    if(abs(dy) <= eps){
      dy = 0;
    }

    vec2 slant = normalize(vec2(dx,dy));
    slant = n.xy;
    FragColor = vec4(slant.x,slant.y,length(slant),0);
    //FragColor = vec4(height,height,height,1);
}

