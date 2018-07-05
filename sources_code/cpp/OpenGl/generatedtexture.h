#ifndef GENERATEDTEXTURE_H
#define GENERATEDTEXTURE_H

#include <memory>
#include <string>


#include "texture.h"

class GeneratedTexture : public Texture
{
public:
    GeneratedTexture(std::string name, const int &width, const int &height, std::shared_ptr<Shader> shader);
    void initialize();
    void startGenerate();
    void generate(int widthViewport, int heightViewport);
    void resize(int width, int height);

    void reloadShader();

    std::shared_ptr<Shader> getGeneratorShader() const;




protected:
    std::shared_ptr<Shader> _generatorShader;                   /** < The shader for generate the texture    */
    GLuint _fbo;                         /** < Frame Buffer Object for the generate texture  */
    GLint _qtfbo;                       /** < Frame buffer Object for save the FBO of QT, see QT doc for more information */



};

#endif // GENERATEDTEXTURE_H