#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform vec2 resolution;
uniform float offset;


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

vec3 computeNormal(vec3 v1, vec3 v2, vec3 v3){
    vec3 v12 = v2 - v1;
    vec3 v13 = v3 - v1;
    return normalize(cross(v12,v13));
}

vec3 buildPos(float x, float y){
  float px = offset*x*resolution.x;
  float py = getTex(x,y);
  float pz = offset*y*resolution.y;

  return vec3(px,py,pz);
}






void main()
{
    vec4 n = texture(normalMap,texcoord);
    /**
    float dx = dFdxFine(height);
    float dy = dFdyFine(height);
    /**/
    float dx = DX();
    float dy = DY();
    /**/
    float dz = sqrt(1-dx*dx+dy*dy);


    if(abs(dx) <= eps){
      dx = 0;
    }
    if(abs(dy) <= eps){
      dy = 0;
    }





    vec2 slant = normalize(vec2(dx,dy));
    slant = n.xz;
    FragColor = vec4(slant.x,-slant.y,length(slant),0);
    //FragColor = vec4(length(slant),0,0,0);
}

