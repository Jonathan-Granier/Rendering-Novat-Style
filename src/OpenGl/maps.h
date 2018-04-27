#ifndef MAPS_H
#define MAPS_H
#include <memory>
#include "loadtexture.h"
#include "generatedtexture.h"
#include "mesh.h"
#include "shader.h"
#include "lighttextures.h"


struct GenShaders{
    std::shared_ptr<Shader>         slantShader;
    std::shared_ptr<Shader>         curvatureShader;
    std::shared_ptr<Shader>         correctCurvatureShader;
    std::shared_ptr<Shader>         generateLightShader;
    std::shared_ptr<Shader>         gaussBlurShader;
    std::shared_ptr<Shader>         parallaxShader;
};


class Maps
{
public:
    Maps(std::shared_ptr<GenShaders> shaders, std::shared_ptr<Texture> heightMap, float ymin, float ymax);
    Maps(std::shared_ptr<GenShaders> shaders, int width, int height,float ymin, float ymax);

    void setNormalMap(std::vector<float> data);
    void generateHeightMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> refHeightMap);
    void generateSlantMap(int widthViewport,int heightViewport);
    //void generateCurvatureMap(int widthViewport, int heightViewport, int sigma);
    void generateLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos,float pitch , float yaw);
    void generateLightMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> previousLightMap,float pitch);

    void generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos);

    void drawHeightMap(std::shared_ptr<Shader> shader);
    void drawNormalMap(std::shared_ptr<Shader> shader);
    void drawSlantMap(std::shared_ptr<Shader> shader);

    /*
    void drawCurvatureMap(std::shared_ptr<Shader> shader);
    void drawCorrectCurvatureMap(std::shared_ptr<Shader> shader);
    */

    void drawLightMap(std::shared_ptr<Shader> shader);
    void drawParallaxMap(std::shared_ptr<Shader> shader);
    //void drawMesh();
/*
    void sendHeightMapToShader(std::shared_ptr<Shader> shader);
    void sendNormalMapToShader(std::shared_ptr<Shader> shader);
    void sendSlantMapToShader(std::shared_ptr<Shader> shader);
*/
/*  void sendCurvatureMapToShader(std::shared_ptr<Shader> shader);
    void sendCorrecCurvatureMapToShader(std::shared_ptr<Shader> shader);
*/
    void sendLightMapToShader(std::shared_ptr<Shader> shader);
    void sendParallaxMap(std::shared_ptr<Shader> shader);

    void setHeightMap(std::shared_ptr<Texture> heightMap);
    std::shared_ptr<Texture> getHeightMap();

    std::shared_ptr<Mesh> getMesh() const;


    void setLightThreshold(float t);

    void setGaussBlurFactor(float g);

    void reloadHeightMap();

    int getWidth() const;

    int getHeight() const;

    std::shared_ptr<GeneratedTexture> getLightMap() const;


private :




    //    std::shared_ptr<Mesh>               _mesh;

    std::shared_ptr<GeneratedTexture>   _gaussBlurVMap; // Vertical
    std::shared_ptr<GeneratedTexture>   _gaussBlurHMap; // Horizontal

    std::shared_ptr<Texture>            _heightMap;
    std::shared_ptr<Texture>            _normalMap;
    std::shared_ptr<GeneratedTexture>   _slantMap;

/*
    std::shared_ptr<GeneratedTexture>   _curvatureMap;
    std::shared_ptr<GeneratedTexture>   _correctCurvatureMap;
*/

    std::shared_ptr<LightTextures>      _lightMap;
    std::shared_ptr<GeneratedTexture>   _parallaxMap;


    int _width;
    int _height;

    float _ymin;
    float _ymax;


    float _lightThreshold;
    float _gaussBlurFactor;

    bool _isGenerate;
    bool _factorIsChange;

    const float         _MAXLIGHTTRESHOLD = M_PI/2.2;
    const float         _MINLIGHTRESHOLD = 0;

    void initialize(std::shared_ptr<GenShaders> shaders);
    void generateNormalMap();

    //void resize();
};

#endif // MAPS_H
