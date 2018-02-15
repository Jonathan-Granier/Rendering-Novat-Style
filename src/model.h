#ifndef MODEL_H
#define MODEL_H



#include <string>
#include <vector>

#include "lib/stb_image.h"

#include "vertexLoader.h"
#include "mesh.h"
#include "vertex.h"

class Model
{
public:

    enum TYPE_FILE { OBJ, MNT, NONE };

    Model(TYPE_FILE typeFile=NONE, std::string const &path="");
    void draw(Shader shader);

private:
    unsigned int loadTexture(const std::string &path);

    const int NB_TEX = 2;
    Mesh *_mesh;

    //TODO delete
    std::vector<unsigned int> _indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

};

#endif // MODEL_H
