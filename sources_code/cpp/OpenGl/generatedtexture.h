/**
* @file generatedtexture.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/


#ifndef GENERATEDTEXTURE_H
#define GENERATEDTEXTURE_H

#include <memory>
#include <string>


#include "texture.h"


/**
* @brief This class is a child of the Texture class. It is used to generate a texture in a FBO with a shader.
* Use :
*   First call initiliaze for initialize the FBO.
*   When you want generate the texture. First call start generate that will use the shader.
*   After send all uniform to your shader.
*   Finally call generate for generate the texture
*
*   After it's the same use that the Texture class
*/

class GeneratedTexture : public Texture
{
public:
    /**
    * @brief Basic Constructor
    *
    * @param name           The name of the texture.
    * @param width          The width of the texture.
    * @param height         The height of the texture.
    * @param shader         The shader used to generate the texture.
    */
    GeneratedTexture(std::string name, const int &width, const int &height, std::shared_ptr<Shader> shader);

    /**
    * @brief Initialize the framebuffer object.
    */
    void initialize();

    /**
    * @brief use the shader.
    * Between startGenerate and generate, you can send all uniform to the shader.
    */
    void startGenerate();

    /**
    * @brief Generate the texture in the fbo with the shader.
    *
    * @param widthViewport      The width of the openGL widget.
    * @param heightViewport     The height of the openGL widget.
    */
    void generate(int widthViewport, int heightViewport);

    /**
    * @brief resize the texture.
    */
    void resize(int width, int height);

    /**
    * @return get the shader used to generate the texture. Use to set uniform to the shader.
    */
    std::shared_ptr<Shader> getGeneratorShader() const;




protected:
    /** The shader for generate the texture    */
    std::shared_ptr<Shader> _generatorShader;
    /** Frame Buffer Object for the generate texture  */
    GLuint _fbo;
    /** Frame buffer Object for save the FBO of QT, see QT doc for more information */
    GLint _qtfbo;



};

#endif // GENERATEDTEXTURE_H
