/**
* @file editheightmap.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief    The seconde part of the Laplacian pyramid , do the difference beetween two heightMap (a heightMap and his blur).
*           Do nothing if it's the lastMap of the pyramid.
*
*
* Input texture :
*     A height map.
*     The blur of the height map.
* Output :
*     A height in level of gray.
*
* SHADER NUMBER 1.
**/

#version 330 core
// Output, a height in level of gray
out vec4 FragColor;
//The texture coordinates
in vec2 texCoord;
//TEXTURE NUMBER 0. The height map of the scale
uniform sampler2D currentHeightMap;
//TEXTURE NUMBER 0. The height map of the next scale (It's a blur of currentHeightMap).
uniform sampler2D nextHeightMap;
//If the currentHeightMap is the last map of the Laplacian pyramid (true), the shader just copy the currentHeightMap in the output.
uniform bool lastMap;


void main()
{
    float currentHeight = texture(currentHeightMap, texCoord).r;
    float nextHeight = texture(nextHeightMap, texCoord).r;
    float height;
    if(lastMap)
      height = currentHeight;
    else
      height = currentHeight - nextHeight;

    FragColor = vec4(height,height,height,0);
}
