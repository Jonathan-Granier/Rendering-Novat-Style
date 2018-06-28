#ifndef MAPS_H
#define MAPS_H
#include <memory>
#include "loadtexture.h"
#include "generatedtexture.h"
#include "mesh.h"
#include "shader.h"
//#include "lighttextures.h"


struct GenShaders{
    std::shared_ptr<Shader>         gaussBlurShader;
    std::shared_ptr<Shader>         slantShader;
    std::shared_ptr<Shader>         editHeightMapShader;
    std::shared_ptr<Shader>         normalMapShader;
    std::shared_ptr<Shader>         curvatureShader;
    std::shared_ptr<Shader>         correctCurvatureShader;
    std::shared_ptr<Shader>         shadeLightShader;
    std::shared_ptr<Shader>         shadowLightShader;
    std::shared_ptr<Shader>         parallaxShader;
    std::shared_ptr<Shader>         morphoShader;
    std::shared_ptr<Shader>         mergeShadowShader;
    std::shared_ptr<Shader>         shadingShader;
};


class Maps
{
public:
    Maps(std::shared_ptr<GenShaders> shaders, std::shared_ptr<Texture> heightMap, float ymin, float ymax);
    Maps(std::shared_ptr<GenShaders> shaders);




    void create(int width, int height, float ymin, float ymax);
    void create(std::shared_ptr<Texture> heightMap, int width, int height, float ymin, float ymax);

    void generateHeightMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> refHeightMap);
    void generateEditHeightMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> previousHeightMap, bool firstMap);
    void generateNormalMap(int widthViewport, int heightViewport);
    void generateSlantMap(int widthViewport,int heightViewport);

    void generateShadeLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch , float yaw, bool doEdit);
    //void generateShadeLightMap(int widthViewport, int heightViewport, std::shared_ptr<LightTextures> previousShadeLightMap, float pitch, bool doMerge,bool none);
    void generateShadowLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw, bool doEdit);
    //void generateShadowLightMap(int widthViewport, int heightViewport, std::shared_ptr<LightTextures> previousShadowLightMap, float pitch);
    void generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos);
    void generateMorphoErosionMap(int widthViewport, int heightViewport, bool doMorpho);
    void generateMorphoDilationMap(int widthViewport, int heightViewport,bool doMorpho);
    void generateMergeShadowMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> previousShadowMap, bool firstMap);
    void generateShadingMap(int widthViewport, int heightViewport, glm::mat4 mdvMat, glm::mat3 normalMat, glm::vec3 lightPosition, std::shared_ptr<Texture> previousShadingMap, bool firstMap, int shadeSelector);


    void drawHeightMap(std::shared_ptr<Shader> shader);
    void drawEditHeightMap(std::shared_ptr<Shader> shader);
    void drawNormalMap(std::shared_ptr<Shader> shader);
    void drawSlantMap(std::shared_ptr<Shader> shader);
    void drawShadeLightMap(std::shared_ptr<Shader> shader);
    void drawShadowLightMap(std::shared_ptr<Shader> shader);
    void drawParallaxMap(std::shared_ptr<Shader> shader);
    void drawMorphoErosionMap(std::shared_ptr<Shader> shader);
    void drawMorphoDilationMap(std::shared_ptr<Shader> shader);
    void drawMergeShadowMap(std::shared_ptr<Shader> shader);
    void drawShadingMap(std::shared_ptr<Shader> shader);


    void sendEditHeightMapToShader(std::shared_ptr<Shader> shader);
    void sendNormalMapToShader(std::shared_ptr<Shader> shader);
    void sendShadeLightMapToShader(std::shared_ptr<Shader> shader);
    void sendShadowLightMapToShader(std::shared_ptr<Shader> shader);
    void sendParallaxMap(std::shared_ptr<Shader> shader);
    void sendMorphoErosionMap(std::shared_ptr<Shader>  shader);
    void sendMorphoDilationMap(std::shared_ptr<Shader>  shader);
    void sendMergeShadowMap(std::shared_ptr<Shader> shader);
    void sendShadingMap(std::shared_ptr<Shader>  shader);




    float getLightThreshold() const;

    void setLightThreshold(float t);

    float getGaussBlurFactor() const;

    void setGaussBlurFactor(float g);

    void reloadHeightMap();

    int getWidth() const;

    int getHeight() const;

   // void setHeightMap(std::shared_ptr<Texture> heightMap);
    std::shared_ptr<Texture> getHeightMap();
    std::shared_ptr<GeneratedTexture> getEditHeightMap() const;
    std::shared_ptr<GeneratedTexture> getShadeLightMap() const;
    std::shared_ptr<GeneratedTexture> getShadowLightMap() const;
    std::shared_ptr<GeneratedTexture> getShadingMap() const;
    std::shared_ptr<GeneratedTexture> getMorphoDilationMap() const;

private :




    //    std::shared_ptr<Mesh>               _mesh;

    std::shared_ptr<GeneratedTexture>   _gaussBlurVMap; // Vertical
    std::shared_ptr<GeneratedTexture>   _gaussBlurHMap; // Horizontal

    std::shared_ptr<Texture>            _heightMap;
    std::shared_ptr<GeneratedTexture>   _editHeightMap;
    std::shared_ptr<GeneratedTexture>   _normalMap;
    std::shared_ptr<GeneratedTexture>   _slantMap;
    std::shared_ptr<GeneratedTexture>      _shadeLightMap;
    std::shared_ptr<GeneratedTexture>      _shadowLightMap;
    std::shared_ptr<GeneratedTexture>   _parallaxMap;
    std::shared_ptr<GeneratedTexture>   _morphoErosionMap;
    std::shared_ptr<GeneratedTexture>   _morphoDilationMap;
    std::shared_ptr<GeneratedTexture>   _mergeShadowMap;
    std::shared_ptr<GeneratedTexture>   _shadingMap;


    int _width;
    int _height;

    float _ymin;
    float _ymax;

    float _yminEdit;
    float _ymaxEdit;

    float _gaussBlurFactor;
    float _lightThreshold;

    bool _isGenerate;
    bool _factorIsChange;
    bool _isEdit;

    const float         _MAXLIGHTTRESHOLD = M_PI/2.0;
    const float         _MINLIGHTRESHOLD = 0;

    void initialize(std::shared_ptr<GenShaders> shaders);

    //void resize();
    void resize();
};

#endif // MAPS_H
