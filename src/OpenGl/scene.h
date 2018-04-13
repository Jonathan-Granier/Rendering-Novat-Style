#ifndef SCENE_H
#define SCENE_H



#include <string>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "loadtexture.h"
#include "generatedtexture.h"
#include "meshloader.h"
#include <math.h>
/**
 * @brief A Scene is defined by his mesh and his textures. It can load and draw a mesh and textures.
 */
class Scene
{
public:


    enum TYPE_MESH {
                    LOADED,
                    GENERATED
    };

    /**
     * @brief Loads a mesh with ml , loads the differents textures and compute the center and the radius of the Scene
     * @param filepaths : the path of the mesh
     * @param typeFile : the type of the mesh
     */
    Scene(std::vector<std::string> const &filepaths, TYPE_MESH typeMesh, int widthViewport, int heightViewport);
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

    void drawGaussBlur(std::shared_ptr<Shader> shader);

    void drawLightMap(std::shared_ptr<Shader> shader);

    void computeCurvatureMap();
    void computeGaussBlur();
    void computeLightMap(glm::vec3 lightPosition, float lightYaw, float lightPitch);

    void reloadGenerateTexturesShader();


    void switchTypeMeshUsed();


    glm::vec4 getPixel(int xPos, int yPos);



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






    float getSigma() const;
    void setSigma(float sigma);

    void previousLight();
    void nextLight();
    int getLightSelector() const;


    float getLightThreshold() const;
    void setLightThreshold(float lightThreshold);

private:

    std::shared_ptr<Mesh>               _currentMesh;          /** < the main mesh of the Scene */
    std::shared_ptr<Mesh>               _loadedMesh;
    std::shared_ptr<Mesh>               _generatedMesh;

    std::shared_ptr<Mesh>               _meshSphere;
    std::vector<LoadTexture>            _textures;      /** < the classique textures of the Scene*/
    std::shared_ptr<LoadTexture>        _heightMap;
    std::shared_ptr<LoadTexture>        _normalMap;
    std::shared_ptr<GeneratedTexture>   _curvatureMap;
    std::shared_ptr<GeneratedTexture>   _lightMap;
    std::shared_ptr<GeneratedTexture>   _gaussBlur;

    float _sigma;
    bool _curvatureMapIsComputed;
    int _lightSelector;
    float _lightThreshold;
    const int _MAXLIGHTSELECTOR = 5;
    const float _MAXLIGHTTRESHOLD = M_PI/2.2;
    const float _MINLIGHTRESHOLD = 0;
    const float _WIDTHGENTEX = 1024;
    const float _HEIGHTGENTEX = 1024;



    TYPE_MESH _typeMeshUsed;
    int _widthViewport;
    int _heightViewport;



    void initialize();
    void getMapFromMNT();

    void loadingWithLog(MeshLoader ml, const std::vector<std::string> &filepaths);
    std::shared_ptr<Mesh> computeMeshFromGenHeightMap(MeshLoader ml);


};

#endif // SCENE_H
