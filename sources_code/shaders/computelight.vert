/**
* @file computelight.vert
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief Last shader of the pipeline and only shader with the mesh.
*         Mix the mesh with the shading , the shadows and the color.
*  SHADER NUMBER 11.
*
*
**/

#version 330 core

// The position of the vertex.
layout (location = 0) in vec3 aPos;
// The normal of the vertex.
layout (location = 1) in vec3 aNormal;
// The texture coordinates of the vertex.
layout (location = 2) in vec2 aTexCoord;

// The model matrix.
uniform mat4 modelMat;
// The view matrix.
uniform mat4 mdvMat;
// The projection matrix.
uniform mat4 projMat;
// The normal matrix
uniform mat3 normalMat;

// The light direction , normal vector.
uniform vec3 lightDirection;


// The light direction in the view space.
out vec4 lightDir;
// The projection of the normal of the vertex.
out vec3 normal;
// The texture coordinates of the vertex.
out vec2 texCoord;


void main()
{

    vec4 position = vec4(aPos,1.0);
    texCoord = vec2(aTexCoord.x,(aTexCoord.y -1) * -1);

    lightDir =  mdvMat * normalize(vec4(lightDirection,0));
    normal = normalMat * aNormal;

    gl_Position = projMat * mdvMat  * modelMat * position;
}
