/**
* @file slant.frag
* @author Jonathan Granier
* @date
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*
* @brief  Compute the slant map of a height Map. It's just the normal projected.
*
* Input texture :
*     The normal map.
* Output :
*     A 2D vecor on chale red and green , the size of the vector in the chanel blue.
*
*  SHADER NUMBER 3.
**/



#version 330 core
//Output : A 2D vecor on chale red and green , the size of the vector in the chanel blue.
out vec4 FragColor;
//The texture coordinate
in vec2 texCoord;
//TEXTURE NUMBER 2. The normal map.
uniform sampler2D normalMap;

void main()
{
    vec4 n = texture(normalMap,texCoord);
    vec2 slant = n.xz;
    FragColor = vec4(slant.x,slant.y,length(slant),0);
}
