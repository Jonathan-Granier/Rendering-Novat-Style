#version 330 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D editHeightMap;
uniform vec2 resolution;
uniform float offset;


float getTex(float x,float y){
  return texture(editHeightMap,vec2(x,y)).r;
}



vec3 computeNormal(vec3 v1, vec3 v2, vec3 v3){
    if(v1 == 0 || v2 == 0 || v3 == 0)
      return vec3(0);
    vec3 v12 = v2 - v1;
    vec3 v13 = v3 - v1;
    return normalize(cross(v12,v13));
}

vec3 buildPos(float x, float y){
  if(x < 0 || x > 1 || y < 0 || y > 1)
    return vec3(0.0,0.0,0.0);

  float px = offset*x*resolution.x;
  float py = getTex(x,y);
  float pz = offset*y*resolution.y;

  return vec3(px,py,pz);
}






void main()
{

    /*
           10-20
         / | / |
        01-11-21
        | / | /
        02-12

      */
    vec3 v11 = buildPos(texCoord.x,texCoord.y);
    vec3 v10 = buildPos(texCoord.x,texCoord.y-1.0/resolution.y);
    vec3 v20 = buildPos(texCoord.x+1.0/resolution.x,texCoord.y-1.0/resolution.y);
    vec3 v01 = buildPos(texCoord.x-1.0/resolution.x,texCoord.y);
    vec3 v21 = buildPos(texCoord.x+1.0/resolution.x,texCoord.y);
    vec3 v02 = buildPos(texCoord.x-1.0/resolution.x,texCoord.y+1.0/resolution.y);
    vec3 v12 = buildPos(texCoord.x,texCoord.y+1.0/resolution.y);



    vec3 normal = vec3(0,0,0);
    /**/
    normal += computeNormal(v11,v20,v10);
    normal += computeNormal(v11,v21,v20);
    normal += computeNormal(v11,v12,v21);
    normal += computeNormal(v11,v02,v12);
    normal += computeNormal(v11,v01,v02);
    normal += computeNormal(v11,v10,v01);
    normal = normalize(normal);

    FragColor = vec4(normal.x,normal.y,-normal.z,0); // For oriente z up .

    //FragColor = vec4(v10,0);
}

