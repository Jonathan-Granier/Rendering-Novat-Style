#ifndef VIEWER_H
#define VIEWER_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

//#include <unistd.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QColor>

#include "OpenGl/shader.h"
#include "OpenGl/scene.h"



#include "Light_Camera/camera.h"
#include "Light_Camera/light.h"


/**
 * @brief The Open GL widget , init openGL, setup a Scene, a camera, a light and shaders and draw it.
 * @details This class is the junction between the UI in QT and the OpenGL Windows.
 */
class Viewer : public QOpenGLWidget
{
    Q_OBJECT
public:
    /**
    * @brief State machine to select the draw Mode. Select if we draw a specifique texture or the mesh.
    */
    enum DRAWMODE{
                     /** Mode for draw the mesh.                    Shader : computelight.frag      */
                    CLASSICAL,
                    /** Mode for only draw the height map.          From DEM, genheightMap.frag or gaussBlur.frag. */
                    HEIGHTMAP,
                    /** Mode for only draw the edit height map.     Shader : editheightmap.frag.*/
                    EDITHEIGHTMAP,
                    /** Mode for only draw the slant map.           Shader : slant.frag.*/
                    SLANTMAP,
                    /** Mode for only draw the normal map.          Shader : normalmap.frag.*/
                    NORMALMAP,
                    /** Mode for only draw the shade light map.     Shader : shadelight.frag*/
                    SHADELIGHTMAP ,
                    /** Mode for only draw the shadow light map.    Shader : shadowlight.frag.*/
                    SHADOWLIGHTMAP,
                    /** Mode for only draw the shadow map.          Shader : shadowmap.frag.*/
                    SHADOW,
                    /** Mode for only draw the morpho erosion map.  Shader : morpho.frag.*/
                    MORPHODILATION,
                    /** Mode for only draw the morpho erosion map.  Shader : morpho.frag.*/
                    MORPHOEROSION,
                    /** Mode for only draw the morpho erosion map.  Shader : mergeshadow.frag.*/
                    MERGESHADOW,
                    /** Mode for only draw the morpho erosion map.  Shader : shading.frag.*/
                    SHADING
                 };



    /**
     * @brief Classic QWidget constructor, set up a QSurfaceFormat.
     * @param parent    The QWidget parent of Viewer.
     */
    Viewer(QWidget *parent = 0);

    /**
     * @brief Main loop of rendering. Draw a texture and or the mesh depending on the state (_drawmode)
     */
    virtual void paintGL();
    /**
     * @brief Initialize openGL context and the different element of viewer (Scene, camera, shader).
     */
    virtual void initializeGL();

    /**
     * @brief Resize the widget.
     * @details didn't work , need to set viewportSize variable in scene and scale objets.
     *
     * @param width     The new width of the widget.
     * @param height    The new height of the widget.
     *
     */
    virtual void resizeGL(int width,int height);


    /**
     * @brief Intercepts the imput of the mousse and do something depeding on the pressed key.
     * @details - Left button : move the camera.
     *          - Mid button : zoom the camera.
     *          - Right button : move the light.
     * @param me    The button pressed.
     */
    virtual void mousePressEvent(QMouseEvent *me);

    /**
     * @brief Intercepts the movements of the mouss when a button is pressed and do something depeding the button pressed.
     * @details -Left and Mid button : move the camera.
     *          -Right button : move the light.
     * @param me    The button pressed.
     */
    virtual void mouseMoveEvent(QMouseEvent *me);


    /**
    * @brief Set height of the global light
    *
    * @param theta      a angle in degree between 0 and 89.
    */
    void setHeightLight(float theta);

    /**
    * @brief Set the picht of the light for the shadowLightMap.
    *
    * @param p          a angle in degree between 0 and 89.
    */
    void setPitchShadowLight(float p);

    /**
     * @brief Reset the camera and the light postion.
     */
    void resetTheCameraPosition();

    /**
     * @brief Read and compile all shaders.
     */
    void reloadShader();

    /**
     * @brief Print the camera and light data
     */
    void printCamAndLight();

    /**
     * @brief Fixe the camera and the light to hard code positions.
     * @details Work only for full Alpe d'Huez DEM (the 6 .asc files, step 25m)
     */
    void fixeCamAndLight();


    /**
    * @brief Set the drawmode to the previous state.
    * @details The states are in the order given in the enum DRAWMODE
    */
    void previousDrawMode();

    /**
    * @brief Set the drawmode to the next state.
    * @details The states are in the order given in the enum DRAWMODE
    */
    void nextDrawMode();

    /**
    * @brief Set the drawmode to a specifique state.
    * @details
    *        0 :    HEIGHTMAP
             1 :    EDITHEIGHTMAP
             2 :    NORMALMAP
             3 :    SLANTMAP
             4 :    SHADELIGHTMAP
             5 :    SHADOWLIGHTMAP
             6 :    SHADOW
             7:     MORPHODILATION
             8:     MORPHOEROSION
             9:     MERGESHADOW
             10:    SHADING
             11:    CLASSICAL
             other: CLASSICAL
    */
    void setDrawMode(int d);

    /**
     * @brief Check and copy a stack file in _filepaths.
     *
     * @param fileNames     A stack of path file.
     *
     * @return              Return true if the fileNames are correct (.obj or .asc).
     */
    bool loadSceneFromFile(const QStringList &fileNames);


    /**
    * @brief Generate a scene from the genheightmap.frag shader.
    */
    void generateScene();


    /**
    * @brief
    */
    void selectCurrentScale(int id);


    /**
    * @return   Get the name of the current draw mode.
    */
    std::string getCurrentDrawMode();



    /**
    * @brief Set the light Threshold that is the threshold for the smoothstep for the light correction, for a scale.
    * @param id     The ID of the scale where the threshold is to change.
    * @param t      The threshold between pi/10 and pi/2.
    */
    void setLightThreshold(unsigned int id, float t);



    /**
    * @brief Set the sigma for the gauss blur.
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
    * @brief Reload the laplacien pyramid.
    */
    void reloadLaplacienPyramid();

    /**
    * @brief add a scale to the laplacien pyramid. We can't have more than 10 scale.
    * @param id         The id of the new scale.
    * @param enabled    Set if the new scale is enabled or not. By default it is disabled.
    */
    void addScale(unsigned int id);

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
    * @brief Enabled or disabled the shadow (compute and draw)
    * @param doShadow       If true, enabled the shadows , disabled otherwise.
    */
    void setDoShadow(int b);


    /**
    * @brief Set if the light for compute the shade is the global light or the oriented light.
    * @param b      oriented used if true, global light otherwise.
    */
    void setDoEditShadeLightDir(int b);

    /**
    * @brief Set if the light for compute the shade is the global light or the oriented light.
    * @param b      oriented used if true, global light otherwise.
    */
    void setDoEditShadowLightDir(int b);

    /**
    * @brief Set if the mathematical morphology on the shadow is done or not.
    * @param p      do the mathematical morphology if true, do nothing otherwise.
    */
    void setDoShadowMorpho(int b);

    /**
    * @brief Set the color of the colorization methode plain color.
    * @param plainColor     a rgba color between 0 and 1.
    */
    void setPlainColor(const QColor &plainColor);

    /**
    * @brief Return the actual color of the colorization methode plain color.
    * @return The actual color of the colorization methode plain color.
    */
    QColor getPlainColor() const;

    /**
    * @brief Set the color of the colorization methode watercolor.
    * @param waterColor     a rgba color between 0 and 1.
    */
    void setWaterColor(const QColor &waterColor);

    /**
    * @brief return the actual color of the colorization methode watercolor.
    * @return The actual color of the colorization methode watercolor.
    */
    QColor getWaterColor() const;
    /**
    * @brief Load a new texture for the colorMap colorization methode.
    * @param filepaths      Path of the texture file.
    */
    void loadColorMapTex(QString filepaths);

    /**
    * @brief Load a new texture for the cel-shading colorization methode.
    * @param filepaths      Path of the texture file.
    */
    void loadCelShadingTex(QString filepaths);

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




signals :
    /** Signal send when the initializeGL function is done*/
    void initializeDone();

private:

     /** Shader for draw the final scene with mesh, shading , shadow and color. */
    std::shared_ptr<Shader>     _meshShader;
    /** Shader for draw only one texture. */
    std::shared_ptr<Shader>     _drawTextureShader;

    /** The Scene. */
    std::shared_ptr<Scene>      _scene;
    /** The Camera. */
    std::shared_ptr<Camera>     _cam;
    /** The light. */
    std::shared_ptr<Light>      _light;



    /**
    * The current draw mode (see enum DRAWMODE for more details)
    */
    DRAWMODE    _drawMode;
    /**
    * Know if the scene has been already instanciate.
    */
    bool        _needInitializeScene;

    /**
    * Contains the files paths of the DEMs file (.asc)
    */
    std::vector<std::string> _filepaths;           /** < A vector of mesh file.*/

    /**
    * For the mousse. If true , we move the light , if false , we move the camera.
    */
    bool        _lightMode;
    
    /**
    * Last position of the mousse.
    */
    glm::vec2   _moussePos;

    /**
     * @brief load Scene from _filepaths
     */
    void loadScene();

    /**
    * @brief Init _meshShader and _drawTextureSHader
    */
    void initShaders();

    /**
    * @brief Active the shader _drawTexture Shader before send the texture to draw (not done in this function).
    * @param numTex        The num of the texture
    * @details
    *        0 :    heightMap
    *        1 :    editHeightMap
    *        2 :    normalMap
    *        3 :    slantMap
    *        4 :    shadeLightMap
    *        5 :    shadowLightMap
    *        6 :    shadowMap
    *        7:     morphoDilationMap
    *        8:     morphoErosionMap
    *        9:     mergeShadowMap
    *        10:    shadingMap
    */
    void initDrawTexture(int numTex);


};

#endif // VIEWER_H
