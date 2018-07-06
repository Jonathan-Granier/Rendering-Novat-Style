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
#include "scale.h"
/**
 * @brief This class manage the stack of Scale ( on set of texture) , the mesh and all the texture.
 * The goal of this class is manage the multi-scale rendering (it's a Laplacian pyramid).
 *  So the main object of this class is _scaleManagers . It's a vector that contains scale , their ID and if they are enabled.
 * Show Scale description for more details about the scale.
 * First , We have to create a scene with a set of DEM (.asc) with createScene. This will instanciate a scale object and a mesh of the DEM.
 *  Use :

        addScale : add scale object , this add a step of the Laplacian pyramid.
 *      selectCurrentScale Select the current scale object. This scale will be draw after call a "draw" Functions
 *      Enabled/disable scale : Only enabled scale are use to create the Laplacien pyramid.
 *
 * There is a conflict with the FBO of QT. So we need to instanciate all FBO before the initialize of QT. Thus we create 10 Scale object in the stack ( = 130 textures 1024*1024).
 */
class Scene
{
public:




    /**
     * @brief constructor that instanciate all shaders for the scale , load texture and create the scale' stack (_scaleManager)
     * @param widthViewport : the width of the openGL widget
     * @param heightViewport : the height of the openGL widget
     */
    Scene(int widthViewport, int heightViewport);

    /**
    * @brief create the scene from a stack of DEM (.asc) . Can be empty , this will generate a heightMap from the heightMap class.
    * @param filepaths :  the paths of the DEM files.
    *
    */
    void createScene(const std::vector<std::string> &filepaths);

    /**
     * @brief Draw the current scale, the mesh and the texture. Add a sphere for display the sun.
     * @param shader :  the shader to use for draw the Scene
     * @param lightDirection : the direction of the light. (normalize vector)
     */
    void draw(std::shared_ptr<Shader> shader, glm::vec3 lightDirection);


    /**
     * @brief Draw only the current height map with the shader in parameter
     * @param shader to draw
     */
    void drawHeightMap(std::shared_ptr<Shader> shader);


    /**
     * @brief Draw only the current Edit Height Map with the shader in parameter
     * @param shader to draw
     */
    void drawEditHeightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Normal Map with the shader in parameter
     * @param shader to draw
     */
    void drawNormalMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Slant Map with the shader in parameter
     * @param shader to draw
     */
    void drawSlantMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shade Light Map with the shader in parameter
     * @param shader to draw
     */
    void drawShadeLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shadow Light Map with the shader in parameter
     * @param shader to draw
     */
    void drawShadowLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shadow Map with the shader in parameter
     * @param shader to draw
     */
    void drawShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Morpho Erosion Map with the shader in parameter
     * @param shader to draw
     */
    void drawMorphoErosionMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Morpho Dilation Map with the shader in parameter
     * @param shader to draw
     */
    void drawMorphoDilationMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Merge Shadow Map with the shader in parameter
     * @param shader to draw
     */
    void drawMergeShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shading Map with the shader in parameter
     * @param shader to draw
     */
    void drawShadingMap(std::shared_ptr<Shader> shader);


    /**
     * @brief Draw the ascii texture for draw number in the shader
     * @param shader to draw
     */
    void drawAsciiTex(std::shared_ptr<Shader> shader);


    /**
    * @brief Generate the laplacien pyramide with all enabled scale in three step :
    * 1. for each scale make a gauss blur with the previous map except the first map.
    * 2. for each scale make the difference with the next scale except the last map..
    * 3. for each scale generate the normal map and slant map.
    * Do something only if reloadLaplacienPyramid function was call before and do the stuff only once.
    */
    void generateLaplacienPyramid();

    /**
    * @brief Generate all Intermediate scale. It's compose the orientation light for the shading and the shadow, all shadow Map and the final shading.
    * @param mdvMat : the view Matrice for compute the shading.
    * @param normalMat : the normal matrice for compute the shading.
    * @param lightDir : the global light direction which will be modified locally.
    * @param pitch : the pitch angle of the light.
    * @param yaw : the yaw angle of the light.
    */
    void generateIntermediateScale(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightDir, float pitch, float yaw);

    /**
    * @brief Reload all the shader used by the Scale class.
    * Allow a regenerate of the Laplacien Pyramid.
    */
    void reloadGenerateTexturesShader();


    /**
     * @brief get _center
     * @return the center of the Scene which is the center of the DEM/Mesh.
     */
    glm::vec3 getCenter() const;
    /**
     * @brief get _radius
     * @return the radius of the Scene which is the radius of the DEM/Mesh.
     */
    float getRadius() const;

    /**
    * @brief select the current Scale . This current scale will be the drawn scale when a draw function will be call.
    * @param id : The ID of the current Scale.
    */
    void selectCurrentScale(int id);

    /**
    * @brief Set the light Threshold that is the threshold for the smoothstep for the light correction, for a scale.
    * @param id: The ID of the scale where the threshold is to change.
    * @param t : the threshold between pi/10 and pi/2.
    */
    void setLightThreshold(unsigned int id, float t);



//    int getGaussBlurFactor() const;
    void setGaussBlurFactor(unsigned int id, int g);

    void setEnabledScale(unsigned int id, bool enabled);

    void reloadLaplacienPyramid();


    void addScale(unsigned int id, bool enabled = false);




    unsigned int getCurrentScaleIndex() const;



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




    struct ScaleManager{
        unsigned int ID;
        bool enabled;
        std::shared_ptr<Scale>   scale;
    };



    std::vector<std::shared_ptr<ScaleManager>>           _scaleManagers;
    std::shared_ptr<GenShaders>                         _genShaders;
    std::shared_ptr<Mesh>                               _mountains;


    std::vector<std::shared_ptr<Scale>>                  _supplyScale;   /**< There is conflig between glew and QT , and it's impossible to create a new FBO in the paintGL context without break the QT's FBOs.
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
    bool _doReloadLaplacienPyramid;

    int _shadeSelector;
    int _colorSelector;
    float _pitchLightShadow;


    std::shared_ptr<ViewportSize> _viewportSize;


    void initializeGenShader();
    void initializeScale(std::shared_ptr<Texture> heightMap);
    void initializeGenScale();
    std::shared_ptr<Texture> computeGenHeightMap();
    void initializeTexture();


    std::shared_ptr<ScaleManager> findFromID(unsigned int id);
    void printScaleManagers();
    void initStackScale();
    std::shared_ptr<Scale> getScaleFromSupply();

};

#endif // SCENE_H
