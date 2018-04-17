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
    void sendToShader(std::shared_ptr<Shader> shader,std::string name);
    void draw(std::shared_ptr<Shader> shader);

    std::vector<float> getDataRED();


    int meshOffset() const;
    void setMeshOffset(int meshOffset);



    int getWidth() const;
    int getHeight() const;

protected:
    unsigned int _ID;       /*!< ID of the texture assign by glGenTextures().*/
    std::string _name;      /*!< The name of the texture. */
    int _width, _height;    /*!< Size of the texture      */



    int _meshOffset;        /*!< Used just for the heightMap*/

    void renderQuad();

};

#endif // TEXTURE_H
