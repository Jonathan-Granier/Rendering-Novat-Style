/**
* @file loadtexture.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/


#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include<string>
#include<vector>
#include "shader.h"
#include "texture.h"

/**
* @brief This class is a child of Texture with only two constructor for load a texture from a file or a data vector.
* This class have the same use that the Texture class.
*/
class LoadTexture : public Texture
{
public:
    /**
    * @brief Constructor for load a texture from a file.
    *
    * @param name               The name of the texture.
    * @param path               The file path of the texture to load.
    */
    LoadTexture(const std::string &name, const std::string &path);

    /**
    * @brief Constructor for load a texture from a data vector.
    *
    * @param name               The name of the texture.
    * @param data               The data of the texture.
    * @param internalFormat     The internalFormat of the texture, see glTexImage2D documation for more information.
    * @param internalFormat     The format of the texture, see glTexImage2D documation for more information.
    * @param width              The width of the texture.
    * @param height             The height of the texture.
    */
    LoadTexture(const std::string &name, std::vector<float> data, GLint internalFormat , GLenum format , const int &width, const int &height);

};

#endif // LOADTEXTURE_H
