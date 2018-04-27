#ifndef LIGHTTEXTURES_H
#define LIGHTTEXTURES_H

#include "generatedtexture.h"
#include <memory>
class LightTextures : public GeneratedTexture
{
public:
    LightTextures(std::string name, const int &width, const int &height, std::shared_ptr<Shader> shader);
    void initialize();
    void sendToShader(std::shared_ptr<Shader> shader);
    void draw(std::shared_ptr<Shader> shader);
private:
    unsigned int _ID_Angles;
};

#endif // LIGHTTEXTURES_H
