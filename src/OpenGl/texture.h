#ifndef TEXTURE_H
#define TEXTURE_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>


#include <string>
#include <vector>
#include <memory>
#include "shader.h"



/**
 * @brief The name and the ID of a texture.
 */
class Texture
{
public:
    Texture(std::string name);
    void sendToShader(std::shared_ptr<Shader> shader);
    void sendToShader(std::shared_ptr<Shader> shader,std::string name);
    void draw(std::shared_ptr<Shader> shader);

    std::vector<float> getDataRED();
    void printValueRED();

    int meshOffset() const;
    void setMeshOffset(int meshOffset);



    int getWidth() const;
    int getHeight() const;


    std::string getName() const;

    unsigned int getID() const;

protected:
    unsigned int _ID;       /*!< ID of the texture assign by glGenTextures().*/
    std::string _name;      /*!< The name of the texture. */
    int _width, _height;    /*!< Size of the texture      */



    int _meshOffset;        /*!< Used just for the heightMap*/

    void renderQuad();

};

#endif // TEXTURE_H
