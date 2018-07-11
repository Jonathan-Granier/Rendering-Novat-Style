/**
* @file normalmap.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Compute the normals of a height map.
*
* Input texture :
*     The edit height map..
* Output :
*     A 3D vector, z up (for have the same orthonormal coordinate system with the light vector).
*
*  SHADER NUMBER 2.
**/


#version 330 core
// Output : A 3D normal vector.
out vec4 FragColor;
// The texture coordinate
in vec2 texCoord;
// TEXTURE NUMBER 1. The edit height Map (Output of the Laplacian pyramid)
uniform sampler2D editHeightMap;
// The resolution of the OpenGL Widget.
uniform vec2 resolution;
// The offset of the DEM loaded .
uniform float offset;




/*-------------------------------------
* COMPUTENORMAL
*
* Compute the normal of a polygon
*
* Input
*   v1      A 3D point.
*   v2      A 3D point.
*   v3      A 3D point.
*
* Ouput
*   vec3    The normal of the polygon form by v1,v2 and v3.
*           (if one point is null , the ouput is null)
*/
vec3 computeNormal(vec3 v1, vec3 v2, vec3 v3){
    if(v1 == vec3(0,0,0) || v2 == vec3(0,0,0) || v3 == vec3(0,0,0))
      return vec3(0);
    vec3 v12 = v2 - v1;
    vec3 v13 = v3 - v1;
    return normalize(cross(v12,v13));
}

/*-------------------------------------
* BUILDPOS
*
* Build a position of a point from his texture coordinate and the offset.
*
* Input
*     x       a texture coordinate.
*     y       a texture coordinate.
*
* Ouput
*     vec3    a 3D point.
*/
vec3 buildPos(float x, float y){
  if(x < 0 || x > 1 || y < 0 || y > 1)
    return vec3(0.0,0.0,0.0);

  float px = offset*x*resolution.x;
  float py = texture(editHeightMap,vec2(x,y)).r;
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

    normal += computeNormal(v11,v20,v10);
    normal += computeNormal(v11,v21,v20);
    normal += computeNormal(v11,v12,v21);
    normal += computeNormal(v11,v02,v12);
    normal += computeNormal(v11,v01,v02);
    normal += computeNormal(v11,v10,v01);
    normal = normalize(normal);

    FragColor = vec4(normal.x,normal.y,-normal.z,0); // For oriente z up .

}
