#version 450 core

out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D editHeightMap;
uniform vec2 resolution;
uniform float offset;


float getTex(float x,float y){
  return texture(editHeightMap,vec2(x,y)).r;
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
        /*
         10
      01 11 21
         12

    */
    vec3 v11 = buildPos(texcoord.x,texcoord.y);
    vec3 v21 = buildPos(texcoord.x+1.0/resolution.x,texcoord.y);
    vec3 v01 = buildPos(texcoord.x-1.0/resolution.x,texcoord.y);
    vec3 v12 = buildPos(texcoord.x,texcoord.y+1.0/resolution.y);
    vec3 v10 = buildPos(texcoord.x,texcoord.y-1.0/resolution.y);

    vec3 normal = vec3(0,0,0);
    normal += computeNormal(v11,v10,v01);
    normal += computeNormal(v11,v21,v10);
    normal += computeNormal(v11,v12,v21);
    normal += computeNormal(v11,v01,v12);
    normal = normalize(normal);

   // FragColor = vec4(height,height,height,0);
    FragColor = vec4(normal.x,normal.y,-normal.z,0); // For oriente z up .
}

