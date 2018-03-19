#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"
#include <string>
#include "model.h"



/**
 * @brief Create and Draw a depthMap (store in 2D texture) from a model and a light position.
 */
class ShadowMap
{
public:
    /**
     * @brief Load the shader for create the shadowMap and initialize the 2D texture.
     * @param name : The name of the 2D texture.
     */
    ShadowMap(std::string name);
    /**
     * @brief initialize the 2D texture
     * @param name : The name of the 2D texture.
     */
    void initShadowMap(std::string name);
    /**
     * @brief Makes an orthgonal rendering of the scene from the point of view of the light
     * @param model : The scene.
     * @param lightPosition : The light position
     * @param width :  the width of the curent viewport for a rezise
     * @param height :  the height of the current viewport.
     * @return
     */
    glm::mat4 RenderFromLight(Model *model,glm::vec3 lightPosition, float width, float height);

    /**
     * @brief For debug , just draw the shadow map in a quad.
     */
    void DebugShadowMap();
    /**
     * @brief Draw the 2D texture of the shadow map
     * @param shader : the shader where to send the texture.
     */
    void draw(Shader *shader);
    /**
     * @brief return the MVP matrix of the light.
     * @return the MVP matrix of the light.
     */
    glm::mat4 lightSpaceMatrix() const;

private:
    Shader *_generatorShader;                   /** < The shader for generetat the depth map    */
    Shader *_debugShader;                       /** < The shader for display only the depth map */
    Texture *_shadowMap;                        /** < Texture to save the shadow map            */
    glm::mat4 _lightSpaceMatrix;                /** < MVP matrix of the light point of view     */
    unsigned int _depthMapFBO;                  /** < Frame Buffer Object for the depth map     */
    GLint _oldFBO;                              /** < Frame buffer Object for save the FBO of QT, see QT doc for more information */
    const unsigned int _SHADOW_WIDTH  = 1024;   /** < The width of the shadow map texture       */
    const unsigned int _SHADOW_HEIGHT = 1024;   /** < The height of the shadow map texture      */

    void renderQuad();                          /** < Render a simple Quad for display the shadow map texture   */


};

#endif // SHADOWMAP_H
