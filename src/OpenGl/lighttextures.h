#ifndef LIGHTTEXTURES_H
#define LIGHTTEXTURES_H

#include "generatedtexture.h"
#include <memory>
class LightTextures : public GeneratedTexture
{
public:
    LightTextures(std::string name,std::string nameAngleMap, const int &width, const int &height, std::shared_ptr<Shader> shader);
    void initialize();
    void generate(int widthViewport, int heightViewport);
    void sendToShader(std::shared_ptr<Shader> shader);
    void draw(std::shared_ptr<Shader> shader);
    void resize(int width, int height);
    unsigned int ID_Angles() const;




private:
    std::string nameAnglesMap;
    unsigned int _ID_Angles;

};

#endif // LIGHTTEXTURES_H
