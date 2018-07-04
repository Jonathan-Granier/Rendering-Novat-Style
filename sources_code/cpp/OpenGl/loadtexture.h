#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include<string>
#include<vector>
#include "shader.h"
#include "texture.h"

class LoadTexture : public Texture
{
public:
    
    LoadTexture(const std::string &name, const std::string &path);
    LoadTexture(const std::string &name, std::vector<float> data, GLint internalFormat , GLenum format , const int &width, const int &height);

};

#endif // LOADTEXTURE_H
