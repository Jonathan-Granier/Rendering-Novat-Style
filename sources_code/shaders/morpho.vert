/**
* @file morpho.vert
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Shader just for draw a quad for print the texture on this quad.
*
*
*  SHADER NUMBER 7 and 8.
**/





#version 330 core
// The postion of the vertex.
layout (location = 0) in vec3 aPos;
// The texture coordinates of the vertex.
layout (location = 1) in vec2 aTexCoord;

// The texture coordinates.
out vec2 texCoord;

void main()
{
    texCoord = aTexCoord;
    gl_Position = vec4(aPos, 1.0);
}
