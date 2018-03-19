#include "texture.h"

#include <GL/glew.h>
// OpenGL library
#include <GL/gl.h>
// OpenGL Utility library
#include <GL/glu.h>

#include <iostream>
#include "lib/stb_image.h"

using namespace std;

Texture::Texture(const string &path, const string &name) :
    _name(name)
{
    int width, height, nrComponents;
    unsigned char *data;


    glGenTextures(1, &_ID);


    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, _ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //TODO test

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        cout << "Texture failed to load at path :" << path <<  endl;

    }
    stbi_image_free(data);

}

Texture::Texture(unsigned int id, const string name)
{
    _ID = id;
    _name = name;
}

void Texture::draw(Shader *shader,unsigned int i)
{
    glActiveTexture(GL_TEXTURE0 + _ID);
    shader->setInt(_name,_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
}

unsigned int Texture::ID() const
{
    return _ID;
}
