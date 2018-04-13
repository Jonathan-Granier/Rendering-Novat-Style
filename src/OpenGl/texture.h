#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <memory>
#include "shader.h"
#include <QOpenGLFunctions_4_4_Core>

// TODO : generer le debug shader.

/**
 * @brief The name and the ID of a texture.
 */
class Texture : protected QOpenGLFunctions_4_4_Core
{
public:
    Texture(std::string name);
    void sendToShader(std::shared_ptr<Shader> shader);
    void draw(std::shared_ptr<Shader> shader);

protected:
    unsigned int _ID;       /*!< ID of the texture assign by glGenTextures().*/
    std::string _name;      /*!< The name of the texture. */
    int _width, _height;    /*!< Size of the texture      */

    void renderQuad();

};

#endif // TEXTURE_H
