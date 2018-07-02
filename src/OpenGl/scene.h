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




    /**
     * @brief Loads a mesh with ml , loads the differents textures and compute the center and the radius of the Scene
     * @param filepaths : the path of the mesh
     * @param typeFile : the type of the mesh
     */
    Scene(int widthViewport, int heightViewport);


    void createScene(const std::vector<std::string> &filepaths);

    /**
     * @brief Draw the Scene from an shader
     * @param shader :  the shader to use for draw the Scene
     */
    void draw(std::shared_ptr<Shader> shader, glm::vec3 lightDirection);

    /**
     * @brief Draw only the mesh in the Scene, not the texture
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

    void drawEditHeightMap(std::shared_ptr<Shader> shader);
    void drawNormalMap(std::shared_ptr<Shader> shader);
    void drawSlantMap(std::shared_ptr<Shader> shader);
    void drawShadeLightMap(std::shared_ptr<Shader> shader);
    void drawShadowLightMap(std::shared_ptr<Shader> shader);
    void drawShadowMap(std::shared_ptr<Shader> shader);
    void drawMorphoErosionMap(std::shared_ptr<Shader> shader);
    void drawMorphoDilationMap(std::shared_ptr<Shader> shader);
    void drawMergeShadowMap(std::shared_ptr<Shader> shader);
    void drawShadingMap(std::shared_ptr<Shader> shader);
    void drawAsciiTex(std::shared_ptr<Shader> shader);


    void generateGaussHeightMap();
    void generateEditHeightAndNormalMap();
    void generateSlantLightAndParalaxMaps(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightPos, float pitch, float yaw);

    void reloadGenerateTexturesShader();


   // void switchTypeMeshUsed();


    /**
     * @brief get _center
     * @return the center of the Scene
     */
    glm::vec3 getCenter() const;
    /**
     * @brief get _radius
     * @return the radius of the Scene
     */
    float getRadius() const;




    void selectCurrentMaps(int id);
    void nextMaps();
    void previousMaps();

    void setLightThreshold(unsigned int id, float t);



//    int getGaussBlurFactor() const;
    void setGaussBlurFactor(unsigned int id, int g);

    void setEnabledMaps(unsigned int id, bool enabled);

    void reloadGaussHeightMap();


    void addGaussMaps(unsigned int id, bool enabled = false);




    unsigned int getCurrentMapsIndex() const;



    void setDoShadow(bool doShadow);
    void setShadeSelector(int s);
    void setPitchLightShadow(float pitchLightShadow);

    void setDoEditShadeLightDir(bool doEditShadeLightDir);
    void setDoEditShadowLightDir(bool doEditShadowLightDir);

    void setDoShadowMorpo(bool doShadowMorpo);

    void setPlainColor(const glm::vec4 &plainColor);
    glm::vec4 getPlainColor() const;
    void setWaterColor(const glm::vec4 &waterColor);
    glm::vec4 getWaterColor() const;

    void loadColorMapTex(std::string filepaths);
    void loadCelShadingTex(std::string filepaths);

    void setColorSelector(int colorSelector);

    void setDoDefaultShading(bool doDefaultShading);

private:




    struct MapsManager{
        unsigned int ID;
        bool enabled;
        std::shared_ptr<Maps>   maps;
    };



    std::vector<std::shared_ptr<MapsManager>>           _mapsManagers;
    std::shared_ptr<GenShaders>                         _genShaders;
    std::shared_ptr<Mesh>                               _mountains;


    std::vector<std::shared_ptr<Maps>>                  _supplyMaps;   /**< There is conflig between glew and QT , and it's impossible to create a new FBO in the paintGL context without break the QT's FBOs.
                                                                            So i instanciate a stack of map in the initializeGL contexte.*/


    std::shared_ptr<Mesh>                               _meshSphere;
    std::shared_ptr<LoadTexture>                        _asciiTex;
    std::shared_ptr<LoadTexture>                        _celShadingTex;
    std::shared_ptr<LoadTexture>                        _colorMapTex;

    glm::vec4                                           _plainColor;
    glm::vec4                                           _waterColor;

    unsigned int _currentIndex;

    bool _doShadow;
    bool _doEditShadeLightDir;
    bool _doEditShadowLightDir;
    bool _doShadowMorpo;
    bool _doDefaultShading;

    int _shadeSelector;
    int _colorSelector;
    float _pitchLightShadow;


    std::shared_ptr<ViewportSize> _viewportSize;
    bool _reloadEditHeightMap;


    void initializeGenShader();
    void initializeMaps(std::shared_ptr<Texture> heightMap);
    void initializeGenMaps();
    std::shared_ptr<Texture> computeGenHeightMap();
    void initializeTexture();


    std::shared_ptr<MapsManager> findFromID(unsigned int id);
    void printMapsManagers();
    void initStackMaps();
    std::shared_ptr<Maps> getMapsFromSupply();

};

#endif // SCENE_H
