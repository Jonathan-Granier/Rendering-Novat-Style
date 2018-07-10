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
 *  So the main object of this class is _scalesManager . It's a vector that contains scale , their ID and if they are enabled.
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
     * @param widthViewport         The width of the openGL widget
     * @param heightViewport        The height of the openGL widget
     */
    Scene(int widthViewport, int heightViewport);

    /**
    * @brief create the scene from a stack of DEM (.asc) . Can be empty , this will generate a heightMap from the heightMap class.
    * @param filepaths      The paths of the DEM files.
    *
    */
    void createScene(const std::vector<std::string> &filepaths);

    /**
     * @brief Draw the current scale, the mesh and the texture. Add a sphere for display the sun.
     * @param shader            The shader to use for draw the Scene
     * @param lightDirection    The direction of the light. (normalize vector)
     */
    void draw(std::shared_ptr<Shader> shader, glm::vec3 lightDirection);


    /**
     * @brief Draw only the current height map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawHeightMap(std::shared_ptr<Shader> shader);


    /**
     * @brief Draw only the current Edit Height Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawEditHeightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Normal Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawNormalMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Slant Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawSlantMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shade Light Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadeLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shadow Light Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadowLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shadow Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Morpho Erosion Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMorphoErosionMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Morpho Dilation Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMorphoDilationMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Merge Shadow Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMergeShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the current Shading Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadingMap(std::shared_ptr<Shader> shader);


    /**
     * @brief send the ascii texture for draw number in the shader
     * @param shader    shader to send the texture
     */
    void sendAsciiTexToShader(std::shared_ptr<Shader> shader);


    /**
    * @brief Generate the laplacien pyramid with all enabled scale in three step :
    * 1. for each scale make a gauss blur with the previous map except the first map.
    * 2. for each scale make the difference with the next scale except the last map..
    * 3. for each scale generate the normal map and slant map.
    * Do something only if reloadLaplacienPyramid function was call before and do the stuff only once.
    */
    void generateLaplacienPyramid();

    /**
    * @brief Generate all Intermediate scale. It's compose the orientation light for the shading and the shadow, all shadow Map and the final shading.
    * @param mdvMat         The view Matrice for compute the shading.
    * @param normalMat      The normal matrice for compute the shading.
    * @param lightDir       The global light direction which will be modified locally.
    * @param pitch          The pitch angle of the light.
    * @param yaw            The yaw angle of the light.
    */
    void generateIntermediateScale(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightDir, float pitch, float yaw);

    /**
    * @brief add a scale to the laplacien pyramid. We can't have more than 10 scale.
    * @param id         The id of the new scale.
    * @param enabled    Set if the new scale is enabled or not. By default it is disabled.
    */
    void addScale(unsigned int id, bool enabled = false);

    /**
    * @brief allow the generateLaplacienPyramid function to regenerate the Laplacien pyramid.
    */
    void reloadLaplacienPyramid();

    /**
    * @brief Reload all the shader used by the Scale class.
    * Allow a regenerate of the Laplacien Pyramid.
    */
    void reloadGenerateTexturesShader();

    /**
    * @brief Load a new texture for the colorMap colorization methode.
    * @param filepaths      Path of the texture file.
    */
    void loadColorMapTex(std::string filepaths);

    /**
    * @brief Load a new texture for the cel-shading colorization methode.
    * @param filepaths      Path of the texture file.
    */
    void loadCelShadingTex(std::string filepaths);

    /**
     * @brief Get _center
     * @return The center of the Scene which is the center of the DEM/Mesh.
     */
    glm::vec3 getCenter() const;
    /**
     * @brief Get _radius
     * @return The radius of the Scene which is the radius of the DEM/Mesh.
     */
    float getRadius() const;

    /**
    * @brief Select the current Scale . This current scale will be the drawn scale when a draw function will be call.
    * @param id     The ID of the current Scale.
    */
    void selectCurrentScale(int id);

    /**
    * @brief Return the index of the current scale.
    * @return The index of the current scale
    */
    unsigned int getCurrentScaleIndex() const;

    /**
    * @brief Set the light Threshold that is the threshold for the smoothstep for the light correction, for a scale.
    * @param id     The ID of the scale where the threshold is to change.
    * @param t      The threshold between pi/10 and pi/2.
    */
    void setLightThreshold(unsigned int id, float t);


    /**
    * @brief Set the sigma for the gauss blur of the scale id.
    * @param id      The ID of the scale where the sigma is to change.
    * @param g       The value of sigma, must be positive or null.
    */
    void setGaussBlurFactor(unsigned int id, int g);

    /**
    * @brief Enabled or disabled a scale
    * @param id             The ID of the scale that be enabled/disabled
    * @param enabled        If true, enabled the scale , disabled otherwise.
    */
    void setEnabledScale(unsigned int id, bool enabled);



    /**
    * @brief Enabled or disabled the shadow (compute and draw)
    * @param doShadow       If true, enabled the shadows , disabled otherwise.
    */
    void setDoShadow(bool doShadow);

    /**
    * @brief Select the merge method for the shading.
    * @param s      The merge method selected :
    *                   0. Only blur (only if we have two scale)
    *                   1. Only details (only if we have two scale)
    *                   2. Overlay standart merge.
    *                   3. WaterColor merge
    * Show the shader "shading.frag" for more information
    */
    void setShadeSelector(int s);

    /**
    * @brief Set the pitch of the light for compute the light of the shadows
    * @param p      the pitch in radian between 0 and pi/2.
    */
    void setPitchLightShadow(float p);

    /**
    * @brief Set if the light for compute the shade is the global light or the oriented light.
    * @param b      oriented light used if true, global light otherwise.
    */
    void setDoEditShadeLightDir(bool b);
    /**
    * @brief Set if the light for compute the shadow is the global light or the oriented light.
    * @param b      oriented used if true, global light otherwise.
    */
    void setDoEditShadowLightDir(bool b);

    /**
    * @brief Set if the mathematical morphology on the shadow is done or not.
    * @param p      do the mathematical morphology if true, do nothing otherwise.
    */
    void setDoShadowMorpho(bool b);

    /**
    * @brief Set the color of the colorization methode plain color.
    * @param plainColor     a rgba color between 0 and 1.
    */
    void setPlainColor(const glm::vec4 &plainColor);

    /**
    * @brief Return the actual color of the colorization methode plain color.
    * @return The actual color of the colorization methode plain color.
    */
    glm::vec4 getPlainColor() const;
    /**
    * @brief Set the color of the colorization methode watercolor.
    * @param waterColor     a rgba color between 0 and 1.
    */
    void setWaterColor(const glm::vec4 &waterColor);
    /**
    * @brief return the actual color of the colorization methode watercolor.
    * @return The actual color of the colorization methode watercolor.
    */
    glm::vec4 getWaterColor() const;


    /**
    * @brief Select the colorization methode.
    * @param c       the colorization methode selected.
    *                   0: plain color.
    *                   1: water color.
    *                   2: color map.
    *                   3: cel-shading.
    */
    void setColorSelector(int c);

    /**
    * @brief set if we compute ur shading methode or if we compute a classic lambertien with native normal and the global light.
    * @param b      classic lambertien if true, ur methode otherwise
    */
    void setDoDefaultShading(bool b);

private:


    struct ScaleInfo{
        unsigned int ID;                /** the scale ID */
        bool enabled;                   /** if the scale are enabled or not */
        std::shared_ptr<Scale> scale;   /** The scale */
    };


     /** All active scale (enabled and disabled) */
    std::vector<std::shared_ptr<ScaleInfo>>  _scalesManager;
    /** All shaders used for generate the textures */
    std::shared_ptr<GenShaders>                 _genShaders;
    /** The mesh of the mountains.*/
    std::shared_ptr<Mesh>                       _mountains;

    /** There is conflig between glew and QT , and it's impossible to create a new FBO in the paintGL context without break the QT's FBOs.
        So we instanciate a stack of map in the initializeGL contexte. When addScale is called, he take a scale from this stack. */
    std::vector<std::shared_ptr<Scale>>         _supplyScale;

    /** A mesh for the sphere that use to indicate the position of the sun */
    std::shared_ptr<Mesh>                       _meshSphere;

    /** a texture with the ascii tab for print characters in shader.    */
    std::shared_ptr<LoadTexture>                _asciiTex;

    /** The texture use for the colorization methode cel-shading*/
    std::shared_ptr<LoadTexture>                _celShadingTex;

    /** The texture use for the colorization methode color map*/
    std::shared_ptr<LoadTexture>                _colorMapTex;

    /** The color value use for the colorization methode plain color*/
    glm::vec4                                   _plainColor;

    /** The color value use for the colorization methode watercolor*/
    glm::vec4                                   _waterColor;

    /** the width and height of the opengl widget.*/
    std::shared_ptr<ViewportSize> _viewportSize;

    /** The index of the current scale.*/
    unsigned int _currentIndex;

    /** If true, enabled the shadows (compute and draw), disabled otherwise.*/
    bool _doShadow;

    /** If true, the light for compute the shade is the oriented light, global light otherwise.*/
    bool _doEditShadeLightDir;

    /** If true, the light for compute the shadows is the oriented light, global light otherwise.*/
    bool _doEditShadowLightDir;

    /** If true : do the mathematical morphology on the shadow is done , nothing otherwise. */
    bool _doShadowMorpho;

    /** If true we compute ths shade with a classic lambertien with native normal and the global light., ur methode otherwise */
    bool _doDefaultShading;

    /** If true, the next call to generateLaplacienPyramid() regenerate the LaplacienPyramid .*/
    bool _doReloadLaplacienPyramid;

     /** The merge method selected :
     *   0. Only blur (only if we have two scale)
     *   1. Only details (only if we have two scale)
     *   2. Overlay standart merge.
     *   3. WaterColor merge
     */
    int _shadeSelector;

    /** The colorization methode selected:
    *       0: plain color.
    *       1: water color.
    *       2: color map.
    *       3: cel-shading.
    */
    int _colorSelector;

    /** the pitch in radian of the light only for compute the light of the shadows*/
    float _pitchLightShadow;

    /** The maximum of scale that can be allocated*/
    unsigned int MAXSCALE = 5;

    /**
    * @brief Load all shader used for generate the textures.
    */
    void initializeGenShader();
    /*
    * @brief initalize the first scale and the mesh from a texture
    * @param heightMap      a heightMap in the form of texture
    */
    void initializeScale(std::shared_ptr<Texture> heightMap);

    /**
    * @brief generate a height map from the genheightmap shader (size 1024*1024).
    * @return a heightMap in the form of texture.
    */
    std::shared_ptr<Texture> computeGenHeightMap();

    /**
    * @brief Load all classics textures used.
    */
    void initializeTexture();

    /**
    * @brief Find a scale in _scalesManager from his ID
    * @param id     The id of the scale sought.
    */
    std::shared_ptr<ScaleInfo> findFromID(unsigned int id);

    /**
    * Allocate MAXSCALE scale with a size of 1024*1024 and store it in _supplyScale.
    */
    void initSupplyScale();

    /**
    * @brief return a scale from _supplyScale.
    * @return a scale or nullptr if _supplyScale is empty.
    */
    std::shared_ptr<Scale> getScaleFromSupply();

};

#endif // SCENE_H
