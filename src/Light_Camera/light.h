#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
/**
 * @brief A basic light defined by a point.
 * The distance between the center of the world and the light point is constante.
 */
class Light
{
public:
    /**
     * @brief Basic constructor
     * @param position : the position of the light
     * @param mode :  if we move the light , false by default.
     */
    Light(glm::vec3 position=glm::vec3(10.0f,0.0f,0.0f), bool mode=false);

    /**
     * @brief Move the light
     * @param the new position of light.
     */
    void move(glm::vec2 p, float width, float height);
    void setFixePosition();
    glm::vec3 position() const;

    bool _mode; /** <For the mousse , true if we move the light , false otherwise. */


    /**
     * @brief Init the move of the light around the Y axe
     * @param moussPos : the actual position of the mousse
     */
    void startMoveAroundYAxe(glm::vec2 moussePos,float width,float height);
    /**
     * @brief Move the light around the Y axe, use startMoveAroundYAxe before use this.
     * @param moussePos : the actual position of the mousse
     */
    void moveAroundYAxe(glm::vec2 moussePos,float width,float height);

    void moveAroundXZ(float theta);

private:
    glm::vec3 _position; /** < The position of the light */
    glm::vec2 _oldmoussePosition; /** < The postion of the mousse */


    float _previousTheta;

    /**
     * @brief set and normalize a vector in the middle of the screen.
     * @param v : the vector to center and normalize.
     * @param width : the width of the screen.
     * @param height : the height of the screen.
     * @return
     */
    glm::vec2 centerAndNormalize(glm::vec2 v, float width, float height);
};

#endif // LIGHT_H
