#include "model.h"



Model::Model(TYPE_FILE typeFile, const string &path)
{
    vector<Vertex> vertices;
    vector<Texture> textures;
    vertexLoader vL;
    switch (typeFile){
        case OBJ:   vertices = vL.vertexFromObj(path);
        break;
        case MNT:   vertices = vL.vertexFromMNT(path);
        break;
        case NONE:  vertices = vL.vertexFromHardCode();
        break;
        default:    vertices = vL.vertexFromHardCode();
        break;
    }

    Texture texture1,texture2;
    texture1.id = loadTexture("textures/container.jpg");
    texture1.type = "texture_normal";
    textures.push_back(texture1);
    texture2.id = loadTexture("textures/awesomeface.png");
    texture2.type = "texture_normal";
    textures.push_back(texture2);

    // Create mesh
    _mesh = new Mesh(vertices,_indices,textures);
    _mesh->setupMesh();


}

void Model::draw(Shader shader)
{
    _mesh->Draw(shader);
}

unsigned int Model::loadTexture(const std::string &path)
{
    int width, height, nrComponents;
    unsigned char *data;

    unsigned int textureID;
    glGenTextures(1, &textureID);


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

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Texture failed to load at path :" << path <<  std::endl;

    }
    stbi_image_free(data);

    return textureID;
}
