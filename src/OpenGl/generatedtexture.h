#ifndef GENERATEDTEXTURE_H
#define GENERATEDTEXTURE_H

#include <memory>
#include <string>

#include "texture.h"

class GeneratedTexture : public Texture
{
public:
    GeneratedTexture(std::string name,const int &width, const int &height, const GLchar* genVertex, const GLchar* genFrag);
    void initialize();
    void startGenerate();
    void generate();

    void reloadShader();

protected:
    std::shared_ptr<Shader> _generatorShader;                   /** < The shader for generate the texture    */
    unsigned int _FBO;                  /** < Frame Buffer Object for the generate texture  */
    GLint _QTFBO;                       /** < Frame buffer Object for save the FBO of QT, see QT doc for more information */


};

#endif // GENERATEDTEXTURE_H
