#include "model.h"



Model::Model(TYPE_FILE typeFile, const std::string &path)
{
    meshLoader mL;
    glm::vec3 c = glm::vec3(0.0f,0.0f,0.0f);
    float r;
    unsigned int i;


    switch (typeFile){
        case OBJ:   _mesh = mL.vertexFromObj(path);
        break;
        case MNT:   _mesh = mL.vertexFromMNT(path);
        break;
        case NONE:  _mesh = mL.vertexFromHardCode();
        break;
        default:    _mesh = mL.vertexFromHardCode();
        break;
    }






    Texture texture1,texture2;
    texture1.id = loadTexture("textures/container.jpg");
    texture1.type = "texture_normal";
    _textures.push_back(texture1);
    texture2.id = loadTexture("textures/awesomeface.png");
    texture2.type = "texture_normal";
    _textures.push_back(texture2);




    // computing center
    for(i=0;i<_mesh->_vertices.size();i++) {
      c += _mesh->_vertices[i].Position;
    }
    _center = c/(float)_mesh->_vertices.size();

    // computing radius
    _radius = 0.0;
    for(i=0;i<_mesh->_vertices.size();i++) {
      c = _mesh->_vertices[i].Position-_center;

      r = sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
      _radius = r>_radius ? r : _radius;
    }
}

Model::~Model()
{
    delete _mesh;
}

void Model::draw(Shader *shader)
{

    unsigned int normalNr=1;

    for(unsigned int i=0;i<_textures.size();i++){
        std::string number;
        std::string name=_textures[i].type;

        if(name == "texture_normal"){
            number = std::to_string(normalNr++);
        }
        glActiveTexture(GL_TEXTURE0 + i);
        shader->setInt((name + number).c_str(),i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }

    _mesh->Draw();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        std::cout << "Texture failed to load at path :" << path <<  std::endl;

    }
    stbi_image_free(data);

    return textureID;
}

float Model::radius() const
{
    return _radius;
}

glm::vec3 Model::center() const
{
    return _center;
}
