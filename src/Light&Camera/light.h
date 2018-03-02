#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
/**
 * @brief A basic light defined by a point.
 */
class Light
{
public:
    /**
     * @brief Basic constructor
     * @param position : the position of the light
     * @param mode :  if we move the light , false by default.
     */
    Light(glm::vec3 position=glm::vec3(0,0,1), bool mode=false);

    /**
     * @brief Move the light
     * @param the new position of light.
     */
    void move(glm::vec2 p, float width, float height);
    void setFixePosition();
    glm::vec3 position() const;

    bool _mode; /** <For the mousse , true if we move the light , false otherwise. */

private:
    glm::vec3 _position; /** < The position of the mousse */

};

#endif // LIGHT_H
