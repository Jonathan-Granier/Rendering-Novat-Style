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
#include "maps.h"
/**
 * @brief A Scene is defined by his mesh and his textures. It can load and draw a mesh and textures.
 */
class Scene
{
public:


    enum TYPE_MESH {
                    LOADED,
                    GAUSSLOADED,
                    GENERATED,
                    GAUSSGENERATED,
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

    void drawSlantMap(std::shared_ptr<Shader> shader);

    void drawCurvatureMap(std::shared_ptr<Shader> shader);

    void drawCorrectCurvatureMap(std::shared_ptr<Shader> shader);

    void drawLightMap(std::shared_ptr<Shader> shader);

    void drawParallaxMap(std::shared_ptr<Shader> shader);

    void drawAsciiTex(std::shared_ptr<Shader> shader);

    void initializeGaussMap();
    void computeCurvatureMap();
    void computeLightMap(glm::vec3 lightPosition, float lightYaw, float lightPitch);
    void computeParallaxMap(glm::vec3 lightPosition);

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



    int getGaussBlurFactor() const;
    void setGaussBlurFactor(int gaussBlurFactor);

    void reloadGaussHeightMap();


private:
/*
    struct MAPS{
        std::shared_ptr<Mesh>               mesh;
        std::shared_ptr<LoadTexture>        heightMap;
        std::shared_ptr<GeneratedTexture>   gaussMap;
        std::shared_ptr<GeneratedTexture>   interGaussMap;
        std::shared_ptr<LoadTexture>        normalMap;
        std::shared_ptr<GeneratedTexture>   slantMap;
        std::shared_ptr<GeneratedTexture>   curvatureMap;
        std::shared_ptr<GeneratedTexture>   correctCurvatureMap;
        std::shared_ptr<GeneratedTexture>   lightMap;
    };
*/


    struct HeightMapGauss{
        std::shared_ptr<GeneratedTexture>   gaussMap;
        std::shared_ptr<GeneratedTexture>   interGaussMap;
    };




    std::shared_ptr<Maps>         _loadedMaps;
    std::shared_ptr<Maps>         _loadedMapsGauss;
    std::shared_ptr<Maps>         _generatedMaps;
    std::shared_ptr<Maps>         _generatedMapsGauss;
    std::shared_ptr<Maps>         _currentMaps;

    std::shared_ptr<HeightMapGauss> _loadedHeightMapGauss;
    std::shared_ptr<HeightMapGauss> _generatedHeightMapGauss;


    std::shared_ptr<GenShaders> _genShaders;



    std::shared_ptr<Mesh>                               _meshSphere;
    std::vector<std::shared_ptr<LoadTexture>>           _textures;
    std::shared_ptr<LoadTexture>                        _asciiTex;


    float        _sigma;
    int          _gaussBlurFactor;
    int          _lightSelector;
    float        _lightThreshold;
    const int           _MAXLIGHTSELECTOR = 5;
    const float         _MAXLIGHTTRESHOLD = M_PI/2.2;
    const float         _MINLIGHTRESHOLD = 0;
    const float         _WIDTHGENTEX = 1024;
    const float         _HEIGHTGENTEX = 1024;
    const std::string   _HEIGHTMAPNAME = "heightMap" ;


    TYPE_MESH _typeMeshUsed;
    int _widthViewport;
    int _heightViewport;
    bool _isComputeCurvatureMap;
    bool _isInitializedGaussMap;


    void initializeGenShader();
    void initializeMaps(const std::vector<std::string> &filepaths);
    void initializeTexture();
    void initializeHeightMapGauss(std::shared_ptr<HeightMapGauss> gauss, std::shared_ptr<Texture> ref);
    std::shared_ptr<Texture> computeGenHeightMap();
    void computeGaussBlur(std::shared_ptr<Maps> gaussMaps, std::shared_ptr<HeightMapGauss> gaussHeightMap,std::shared_ptr<Texture> refHeightMap);
    void majCurrentMap();


};

#endif // SCENE_H
