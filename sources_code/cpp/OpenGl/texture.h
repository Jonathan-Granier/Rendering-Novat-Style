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
 * @brief Texture define by a name and a id.
 */
class Texture
{
protected:
    /**
    * @brief Default constructor for the childs of this class.
    * @param name : The name of the texture.
    */
    Texture(std::string name);
public:

    /**
    *   @brief Active, bind and send the texture to the shader in param.
    *   @param shader : The shader that receives the texture.
    */
    void sendToShader(std::shared_ptr<Shader> shader);

    /**
    *   @brief Active, bind and send the texture to the shader in param.
    *   @param shader : The shader that receives the texture.
    *   @param name : The name of the texture in the shader.
    */
    void sendToShader(std::shared_ptr<Shader> shader,std::string name);

    /**
    * @brief Send the texture to the shader and draw a quad.
    * @param shader : The shader that receives the texture.
    */
    void draw(std::shared_ptr<Shader> shader);

    /**
    * @brief Get all red value of the texture.
    * @return Red value of the texture.
    */
    std::vector<float> getDataRED();

    /**
    * @brief Only for heightMap. Get the value of the Offset (the distance between two point in a heightMap)
    * @return The heightMap offset.
    */
    int getHeightMapOffset() const;

    /**
    * @brief Only for heightMap. set the value of the Offset (the distance between two point in a heightMap)
    * @param heightMapOffset : The heightMap offset.
    */
    void setHeightMapOffset(int heightMapOffset);


    /*
    * @brief Get the width of the texture.
    * @return The width of the texture.
    */
    int getWidth() const;

    /*
    * @brief Get the height of the texture.
    * @return The height of the texture.
    */
    int getHeight() const;

protected:
    unsigned int _id;       /*!< ID of the texture assign by glGenTextures().*/
    std::string _name;      /*!< The name of the texture. */
    int _width, _height;    /*!< Size of the texture.      */



    int _heightMapOffset;        /*!< Used just for the heightMap. it's the distance between two point in a heightMap. */


    /**
    * @brief Render a quad for draw a texture.
    */
    void renderQuad();

};

#endif // TEXTURE_H
