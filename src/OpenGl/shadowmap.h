#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <glm/glm.hpp>
#include <memory>
#include "shader.h"
#include "texture.h"
#include <string>
#include "scene.h"
#include "generatedtexture.h"


/**
 * @brief Create and Draw a depthMap (store in 2D texture) from a model and a light position.
 */
class ShadowMap : public GeneratedTexture
{
public:
    /**
     * @brief Load the shader for create the shadowMap and initialize the 2D texture.
     * @param name : The name of the 2D texture.
     */
    ShadowMap(std::string name, const int &width, const int &height);
    /**
     * @brief initialize the 2D texture
     * @param name : The name of the 2D texture.
     */
    void initialize();
    /**
     * @brief Makes an orthgonal rendering of the scene from the point of view of the light
     * @param model : The scene.
     * @param lightPosition : The light position
     * @param width :  the width of the curent viewport for a rezise
     * @param height :  the height of the current viewport.
     * @return
     */
    glm::mat4 generate(std::shared_ptr<Scene> scene,glm::vec3 lightPosition, float width, float height);


    glm::mat4 lightSpaceMatrix() const;

private:

    glm::mat4 _lightSpaceMatrix;                /** < MVP matrix of the light point of view     */
};

#endif // SHADOWMAP_H
