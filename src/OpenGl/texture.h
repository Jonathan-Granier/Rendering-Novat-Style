#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include "shader.h"
/**
 * @brief The name and the ID of a texture.
 */
class Texture
{
public:

    /**
     * @brief Load a texture from a file, generates a ID, and load it in the GPU.
     * @param path :  the path of the texture file.
     * @param name : the name of the texture in the shader.
     * @return the texture ID generates by glGenTextures().
     */
    Texture(const std::string &path, const std::string &name);

    Texture(std::vector<float> data, GLint internalFormat , GLenum format, const int &width, const int &height,std::string name);

    Texture(unsigned int id, const std::string name);


    /**
     * @brief Draw the i th texture with the shader.
     * @param shader :  the shader where to send the texture.
     * @param i : the number of the texture.
     */
    void draw(Shader *shader);


    void print(Shader *shader);

    /**
     * @brief get the id of the texture.
     * @return The id of the texture.
     */
    unsigned int ID() const;

private :

    unsigned int _ID;       /*!< ID of the texture assign by glGenTextures().*/
    std::string _name;      /*!< The name of the texture. */
    int _width, _height;    /*!< Size of the texture      */



    void renderQuad();

};

#endif // TEXTURE_H
