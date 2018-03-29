#ifndef SCENE_H
#define SCENE_H



#include <string>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "loadtexture.h"
#include "generatedtexture.h"

/**
 * @brief A Scene is defined by his mesh and his textures. It can load and draw a mesh and textures.
 */
class Scene
{
public:

    enum TYPE_FILE { OBJ, /*!< (.obj) : classic mesh. */
                     MNT, /*!< (.asc) : a height map of a mountains. */
                     NONE /*!< Just for load a hard code mesh (DEBUG).*/
                   };

    /**
     * @brief Loads a mesh with ml , loads the differents textures and compute the center and the radius of the Scene
     * @param filepaths : the path of the mesh
     * @param typeFile : the type of the mesh
     */
    Scene( std::vector<std::string> const &filepaths,TYPE_FILE typeFile=NONE);
    ~Scene();

    /**
     * @brief Draw the Scene from an shader
     * @param shader :  the shader to use for draw the Scene
     */
    void draw(std::shared_ptr<Shader> shader, glm::vec3 lightPosition);

    /**
     * @brief draw only the mesh in the Scene, not the texture
     */
    void drawOnlyMesh();


    /**
     * @brief Draw the height map with the shader in parameter
     * @param shader to draw
     */
    void drawHeightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw the normal map with the shader in parameter.
     * @param shader to draw
     */
    void drawNormalMap(std::shared_ptr<Shader> shader);

    void drawCurvatureMap(std::shared_ptr<Shader> shader);

    void drawLightMap(std::shared_ptr<Shader> shader);

    void computeCurvatureMap(int widthViewport, int heightViewport);
    void computeLightMap(glm::vec3 lightPosition,int widthViewport,int heightViewport);

    void reloadGenerateTexturesShader();

    /**
     * @brief get _center
     * @return the center of the Scene
     */
    glm::vec3 center() const;
    /**
     * @brief get _radius
     * @return the radius of the Scene
     */
    float radius() const;




private:

    std::shared_ptr<Mesh>               _mesh;          /** < the main mesh of the Scene */
    std::shared_ptr<Mesh>               _meshPlane;
    std::shared_ptr<Mesh>               _meshSphere;
    std::vector<LoadTexture>            _textures;      /** < the classique textures of the Scene*/
    std::shared_ptr<LoadTexture>        _heightMap;
    std::shared_ptr<LoadTexture>        _normalMap;
    std::shared_ptr<GeneratedTexture>   _curvatureMap;
    std::shared_ptr<GeneratedTexture>   _lightMap;




    void getMapFromMNT();
};

#endif // SCENE_H
