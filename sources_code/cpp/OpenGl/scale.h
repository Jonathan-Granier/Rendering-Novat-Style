#ifndef MAPS_H
#define MAPS_H
#include <memory>
#include "loadtexture.h"
#include "generatedtexture.h"
#include "mesh.h"
#include "shader.h"





/**
* A Struct used to share the shaders and have only one compiled version of each shader.
*/
struct GenShaders{
    /**
    * Compute the gaussien blur , need to call twice. First step of the laplacien pyramide.
    *   Input: height map.
    *   Output: height map
    */
    std::shared_ptr<Shader>         gaussBlurShader;
    /**
    * Compute the difference between do heightMap. Seconde step of the laplacien pyramide.
    *   Input: two height maps.
    *   Output: height map
    */
    std::shared_ptr<Shader>         editHeightMapShader;
    /**
    * Compute the normal.
    *   Input: height map.
    *   Output: 3D vectors.
    */
    std::shared_ptr<Shader>         normalMapShader;
    /**
    * Compute the slant map.
    *   Input: normal map.
    *   Output: 2D vectors in r,g and the size of the vector in b.
    */
    std::shared_ptr<Shader>         slantShader;
    /**
    * Directs the light locally used for compute the shanding.
    *   Input: slant map and the global light
    *   Output: 3D vectors.
    */
    std::shared_ptr<Shader>         shadeLightShader;
    /**
    * Directs the light locally used for compute the shadows.
    *   Input: slant map and the global light
    *   Output: 3D vectors.
    */
    std::shared_ptr<Shader>         shadowLightShader;
    /**
    * Compute the shadows with a ray marching.
    *   Input: height map and shadowLight map.
    *   Output : two value, 0: shadow, 1:light.
    */
    std::shared_ptr<Shader>         shadowShader;
    /**
    * Compute the mathematical morphology
    *   Input: shadow map.
    *   Output shadow map.
    */
    std::shared_ptr<Shader>         morphoShader;
    /**
    * Compute the mathematical morphology
    *   Input: shadow map.
    *   Output: value between 0 and 1. 0 : full shadow, 1: full light.
    */
    std::shared_ptr<Shader>         mergeShadowShader;

    /**
    * Compute the shading and if can merge with a another shading map.
    *   Input: shadeLight map, normal map, and shading map (if possible).
    *   Output : value between 0 and 1.
    */
    std::shared_ptr<Shader>         shadingShader;
};

/**
* @brief The size of the opengl widget.
*/
struct ViewportSize{
    int width;
    int height;
};

/**
* @brief This class manage one scale. A scale is composed  of an height map and all the texture generated from it.
* all scale have the same size (width, height) based on the DEM (.asc) in input.
* Use :
*      create the scene (don't forget use generateHeightMap if you use the create function with no heightmap)
*      generate the texture with a generate function
*      send a generated texture to a shader with sendMapToShader function or draw only one texture with draw function.
*/
class Scale
{
public:
    /**
    * @brief Scale constructor. Initialize all textures with a size 1024*1024.
    * @param shaders        shaders used for generate the textures
    * @param viewportSize   The size of the opengl widget.
    */
    Scale(std::shared_ptr<GenShaders> shaders,std::shared_ptr<ViewportSize> viewportSize);

    /**
    * @brief Create a new scale without heightMap. Just rezize the textures. Use generateHeightMap after.
    * @param width      the width of all textures (width of the DEM).
    * @param height     the height of all textures (height of the DEM).
    * @param ymin       the min value of the DEM.
    * @param ymax       the max value of the DEM.
    */
    void create(int width, int height, float ymin, float ymax);
    /**
    * @brief Create a new scale with a heightMap.
    * @param heightMap  a DEM in the form of a heightMap texture.
    * @param width      the width of all textures (width of the DEM).
    * @param height     the height of all textures (height of the DEM).
    * @param ymin       the min value of the DEM.
    * @param ymax       the max value of the DEM.
    */
    void create(std::shared_ptr<Texture> heightMap, int width, int height, float ymin, float ymax);

    /**
    * @brief Generate a height map with a gaussien blur from a another heightmap (first step of the laplacien pyramide) with the shader gaussBlur.frag call twice.
    * @param refHeightMap   the height map to blur.
    */
    void generateHeightMap(std::shared_ptr<Texture> refHeightMap);

    /**
    * @brief Do the difference between the  heightMap and the heightMap in paramater (the seconde step of the laplacien pyramide) with the shader editheightmap.frag.
    * Need to have a heightMap instanciate (generate or not)
    *
    * @param nextHeightMap  the heightMap with whom to make the difference. if null then set firstMap to true
    * @param firstMap       if it's true just copy the  heightMap in the editHeightMap texture, do the difference otherwise.
    */
    void generateEditHeightMap(std::shared_ptr<Texture> nextHeightMap, bool firstMap);

    /**
    * @brief Generate the normal map from the editHeightMap  with the shader normalmap.frag.
    * Need to have editHeightMap instanciate.
    */
    void generateNormalMap();

    /**
    * @brief Generate the slant map from the normal map with the shader slant.frag.
    * Need to have normalMap instanciate.
    */
    void generateSlantMap();

    /**
    * @brief Generate the shadeLightMap from the slantMap with the shader shadelight.frag.
    * Need to have slantMap instanciate.
    * directs the light to the slant
    * @param lightDir   the global direction of the light
    * @param pitch      the pitch of the light
    * @param yaw        the yaw of the light
    * @param doEdit     if false, don't directs the light.
    */
    void generateShadeLightMap(glm::vec3 lightDir, float pitch , float yaw, bool doEdit);

    /**
    * @brief Generate the shadowLightMap from the slantMap with the shader shadowlight.frag.
    * Need to have slantMap instanciate.
    * directs the light to the slant
    * @param lightDir   the global direction of the light
    * @param pitch      the pitch of the light
    * @param yaw        the yaw of the light
    * @param doEdit     if false, don't directs the light.
    */
    void generateShadowLightMap(glm::vec3 lightDir, float pitch, float yaw, bool doEdit);

    /**
    * @brief Generate the shadow map from the editHeighMap and shadowLightMap with the shader shadowmap.frag.
    * Need to have editHeighMap and shadowLightMap instanciate.
    * It's a raymarching.
    */
    void generateShadowMap();


    /**
    * @brief Generate the morphoDilationMap from the shadow map with the shader morpho.frag.
    *   Need to have shadowMap instanciate.
    *   Do the operation of mathematical morphology dilation on the shadowMap.
    * @param doMorpho       justg copy the shadow map in _morphoDilationMap if false.
    */
    void generateMorphoDilationMap(bool doMorpho);

    /**
    * @brief Generate the morphoErosionMap from the morphoDilationMap with the shader morpho.frag.
    *   Need to have morphoDilationMap instanciate.
    *   Do the operation of mathematical morphology erosion on the morphoDilationMap.
    * @param doMorpho       justg copy the morphoDilationMap in _morphoErosionMap if false.
    */
    void generateMorphoErosionMap(bool doMorpho);

    /**
    *  @brief Generate the mergeShadowMap from the morphoErosionMap and a another shadowMap with the shader mergeshadow.frag.
    *   Need to have morphoErosionMap instanciate.
    *   Merge two shadowmap in one.
    * @param previousShadowMap      A shadowMap from a another scale. If null then set lastMap to true.
    * @param lastMap                If true, just copy morphoErosionMap in mergeShadowMap
    */
    void generateMergeShadowMap(std::shared_ptr<Texture> previousShadowMap, bool lastMap);

    /**
    * @brief Generate the shadingMap from the shadeLightMap and the normal map. Can merge the result with a another shadingMap.
    * Need to have normalMap and shadeLightMap instanciate.
    * Do a lambertien with the normal and the light vector from the two textures.
    *
    * @param mdvMat                 The view matrice.
    * @param normalMat              The normal matrice.
    * @param previousShadingMap     A shading map from a another scale. If null then set firstMap to true.
    * @param firstMap               If true, don't merge with a another shading Map.
    * @param shadeSelector          The merge method selected :
    *                                   0. Only blur (only if we have two scale)
    *                                   1. Only details (only if we have two scale)
    *                                   2. Overlay standart merge.
    *                                   3. WaterColor merge
    *                               Show the shader "shading.frag" for more information
    */
    void generateShadingMap(glm::mat4 mdvMat, glm::mat3 normalMat, std::shared_ptr<Texture> previousShadingMap, bool firstMap, int shadeSelector);



    /**
     * @brief Draw only the  height map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawHeightMap(std::shared_ptr<Shader> shader);


    /**
     * @brief Draw only the  Edit Height Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawEditHeightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Normal Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawNormalMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Slant Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawSlantMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Shade Light Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadeLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Shadow Light Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadowLightMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Shadow Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Morpho Dilation Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMorphoDilationMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Morpho Erosion Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMorphoErosionMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Merge Shadow Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawMergeShadowMap(std::shared_ptr<Shader> shader);

    /**
     * @brief Draw only the  Shading Map with the shader in parameter
     * @param shader    shader used to draw the texture
     */
    void drawShadingMap(std::shared_ptr<Shader> shader);




    /**
    * @brief Send the heightMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendHeightMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the editHeightMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendEditHeightMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the normalMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendNormalMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the slantMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendSlantMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the shadeLightMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendShadeLightMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the shadowLightMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendShadowLightMapToShader(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the shadowMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendShadowMap(std::shared_ptr<Shader> shader);


    /**
    * @brief Send the morphoDilationMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendMorphoDilationMap(std::shared_ptr<Shader>  shader);

    /**
    * @brief Send the morphoErosionMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendMorphoErosionMap(std::shared_ptr<Shader>  shader);



    /**
    * @brief Send the mergeShadowMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendMergeShadowMap(std::shared_ptr<Shader> shader);

    /**
    * @brief Send the shadingMap to the shader in paramater.
    * @param shader     The shader that receives the texture..
    */
    void sendShadingMap(std::shared_ptr<Shader>  shader);


    /**
    * @brief Set the light Threshold that is the threshold for the smoothstep for the light correction.
    * @param t      The threshold between pi/10 and pi/2.
    */
    void setLightThreshold(float t);

    /**
    * @brief Set the sigma for the gauss blur.
    * @param g       The value of sigma, must be positive or null.
    */
    void setGaussBlurFactor(int g);


    /**
    * @return get the width of the textures
    */
    int getWidth() const;

    /**
    * @return get the height of the textures
    */
    int getHeight() const;

    /**
    * @return the heightMap
    */
    std::shared_ptr<Texture> getHeightMap();

    /**
    * @return the shadingMap
    */
    std::shared_ptr<Texture> getShadingMap() const;

    /**
    * @return the morphoErosionMap
    */
    std::shared_ptr<Texture> getMorphoErosionMap() const;

private :
    /**
    * The texture use generate the vertical blur of a heightMap. Generate by gaussBlur.frag.
    */
    std::shared_ptr<GeneratedTexture>   _gaussBlurVMap;
    /**
    * The texture use generate the horizontal blur of a heightMap. Generate by gaussBlur.frag.
    */
    std::shared_ptr<GeneratedTexture>   _gaussBlurHMap;

    /**
    * The main texture of this class. It can be a DEM , on a blur of the DEM.
    */
    std::shared_ptr<Texture>            _heightMap;

    /**
    * Height map that can be equal to _heightMap or a difference between _heightMap and a another height map. Generate by editheightmap.frag.
    */
    std::shared_ptr<GeneratedTexture>   _editHeightMap;

    /**
    * The normal of the _editHeightMap. Generate by normalmap.frag
    */
    std::shared_ptr<GeneratedTexture>   _normalMap;

    /**
    * The slant of the _editHeightMap. Generate by slantmap.frag.
    */
    std::shared_ptr<GeneratedTexture>   _slantMap;

    /**
    * The light locally directs by the slant. Used for compute the shading. Generate by shadelight.frag.
    */
    std::shared_ptr<GeneratedTexture>   _shadeLightMap;

    /**
    * The light locally directs by the slant. Used for compute the shadow. Generate by shadowlight.frag.
    */
    std::shared_ptr<GeneratedTexture>   _shadowLightMap;

    /**
    * The shadow compute with a raymarching. Generate by shadowmap.frag.
    */
    std::shared_ptr<GeneratedTexture>   _shadowMap;

    /**
    * The operation of mathematical morphology dilation on the _shadowMap. Generate by morpho.frag.
    */
    std::shared_ptr<GeneratedTexture>   _morphoDilationMap;

    /**
    * The operation of mathematical morphology erosion on the _morphoDilationMap. Generate by morpho.frag.
    */
    std::shared_ptr<GeneratedTexture>   _morphoErosionMap;

    /**
    * The merge between two _morphoDilationMap from two scale. Generate by mergeShadow.frag.
    */
    std::shared_ptr<GeneratedTexture>   _mergeShadowMap;

    /**
    * The shading of the scale. Generate by shading.frag.
    */
    std::shared_ptr<GeneratedTexture>   _shadingMap;

    /**
    * The size of the openGL widget.
    */
    std::shared_ptr<ViewportSize>       _viewportSize;

    /// The width of all textures and the DEM
    int _width;

    /// The height of all textures and the DEM
    int _height;

    /// The min value of the DEM.
    float _ymin;

    /// The max value of the DEM.
    float _ymax;

    /// The min value of the editHeightMap.
    float _yminEdit;

    /// The max value of the editHeightMap.
    float _ymaxEdit;

    /// The sigma of the gauss Blur. between 0 and +infinite.
    int _gaussBlurFactor;

    /// The limit of the angle correction of the light in randian.
    float _lightThreshold;

    /// the maximum angle correction of the light in radian
    const float         _MAXLIGHTTRESHOLD = M_PI/2.0;
    /// the minimum angle correction of the light in radian
    const float         _MINLIGHTRESHOLD = 0;

    /**
    * @brief initialize all generated texture.
    * @param shaders    all the path of the shaders used to generate the textures.
    */
    void initialize(std::shared_ptr<GenShaders> shaders);

    /**
    * @brief resize all texture with the _width and the _height value,
    */
    void resize();
};

#endif // MAPS_H
