#ifndef MODEL_H
#define MODEL_H



#include <string>
#include <vector>

#include "meshloader.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
// TODO : make a type

/**
 * @brief A model is defined by his mesh and his textures. It can load and draw a mesh and textures.
 */
class Model
{
public:

    enum TYPE_FILE { OBJ, /*!< (.obj) : classic mesh. */
                     MNT, /*!< (.asc) : a height map of a mountains. */
                     NONE /*!< Just for load a hard code mesh (DEBUG).*/
                   };

    /**
     * @brief Loads a mesh with ml , loads the differents textures and compute the center and the radius of the model
     * @param ml : a mesh loader for load a mesh
     * @param filepaths : the path of the mesh
     * @param typeFile : the type of the mesh
     */
    Model(MeshLoader ml, std::vector<std::string> const &filepaths,TYPE_FILE typeFile=NONE);
    ~Model();

    /**
     * @brief Draw the model from an shader
     * @param shader :  the shader to use for draw the model
     */
    void draw(Shader *shader,glm::vec3 lightPosition);

    /**
     * @brief get _center
     * @return the center of the model
     */
    glm::vec3 center() const;
    /**
     * @brief get _radius
     * @return the radius of the model
     */
    float radius() const;

    void initShadowMap();

    glm::mat4 RenderFromLight(glm::vec3 lightPosition, Shader *shader, float width, float height);

    glm::mat4 getLightSpaceMatrix() const;

    void DebugShadowMap(Shader *shader);
private:

    Mesh        *_mesh; /** < the mesh of the model */
    Mesh        *_meshPlane;
    Mesh        *_meshSphere;
    std::vector<Texture> _textures; /** < the textures of the model*/
    unsigned int _depthMapFBO;
    const unsigned int _SHADOW_WIDTH =1024, _SHADOW_HEIGHT = 1024;
    glm::mat4 _lightSpaceMatrix;




    GLint _oldFBO;

    void renderQuad();
};

#endif // MODEL_H
