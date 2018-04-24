#ifndef MAPS_H
#define MAPS_H
#include <memory>
#include "loadtexture.h"
#include "generatedtexture.h"
#include "mesh.h"
#include "shader.h"



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
    Maps(std::shared_ptr<GenShaders> shaders, std::shared_ptr<Texture> heightMap, std::string name);
    Maps(std::shared_ptr<GenShaders> shaders, int width=1024, int height=1024, std::string name="NO_NAME");



    void generateSlantMap(int widthViewport,int heightViewport);
    void generateCurvatureMap(int widthViewport, int heightViewport, int sigma);
    void generateLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float yaw, float pitch, float lightThreshold, int lightSelector);
    //void generateLightMap(float lightThreshold, std::shared_ptr<Texture> lightMap);

    void generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos);

    void drawHeightMap(std::shared_ptr<Shader> shader);
    void drawNormalMap(std::shared_ptr<Shader> shader);
    void drawSlantMap(std::shared_ptr<Shader> shader);
    void drawCurvatureMap(std::shared_ptr<Shader> shader);
    void drawCorrectCurvatureMap(std::shared_ptr<Shader> shader);
    void drawLightMap(std::shared_ptr<Shader> shader);
    void drawParallaxMap(std::shared_ptr<Shader> shader);
    void drawMesh();

    void sendHeightMapToShader(std::shared_ptr<Shader> shader);
    void sendNormalMapToShader(std::shared_ptr<Shader> shader);
    void sendSlantMapToShader(std::shared_ptr<Shader> shader);
    void sendCurvatureMapToShader(std::shared_ptr<Shader> shader);
    void sendCorrecCurvatureMapToShader(std::shared_ptr<Shader> shader);
    void sendLightMapToShader(std::shared_ptr<Shader> shader);
    void sendParallaxMap(std::shared_ptr<Shader> shader);

    void setHeightMap(std::shared_ptr<Texture> heightMap);
    std::shared_ptr<Texture> getHeightMap();

    std::shared_ptr<Mesh> getMesh() const;

    void printName();
private :




    std::shared_ptr<Mesh>               _mesh;
    std::shared_ptr<Texture>            _heightMap;
    std::shared_ptr<LoadTexture>        _normalMap;
    std::shared_ptr<GeneratedTexture>   _slantMap;
    std::shared_ptr<GeneratedTexture>   _curvatureMap;
    std::shared_ptr<GeneratedTexture>   _correctCurvatureMap;
    std::shared_ptr<GeneratedTexture>   _lightMap;
    std::shared_ptr<GeneratedTexture>   _parallaxMap;


    int _width;
    int _height;
    std::string _name;

    void initialize(std::shared_ptr<GenShaders> shaders);
    void initializeDataMaps();
    void resize();
};

#endif // MAPS_H
