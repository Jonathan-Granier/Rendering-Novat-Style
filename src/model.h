#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

#include <string>
#include <vector>

#include "lib/stb_image.h"

#include "meshloader.h"
#include "mesh.h"
#include "vertex.h"

// TODO : make a type
struct Texture {
    unsigned int id;
    std::string type;
};


class Model
{
public:

    enum TYPE_FILE { OBJ, MNT, NONE };

    Model(MeshLoader ml, std::vector<std::string> const &filepaths,TYPE_FILE typeFile=NONE);
    ~Model();

    void draw(Shader *shader);

    glm::vec3 center() const;
    float radius() const;

private:
    unsigned int loadTexture(const std::string &path);

    const int   NB_TEX = 2;
    Mesh        *_mesh;

    glm::vec3   _center;
    float       _radius;

    std::vector<Texture> _textures;


};

#endif // MODEL_H
