#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
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

    /**
     * @brief Draw the i th texture with the shader.
     * @param shader :  the shader where to send the texture.
     * @param i : the number of the texture.
     */
    void draw(Shader *shader, unsigned int i);
private :

    unsigned int _ID;  /*!< ID of the texture assign by glGenTextures().*/
    std::string _name; /*!< The name of the texture. */

};

#endif // TEXTURE_H
