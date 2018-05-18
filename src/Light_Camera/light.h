#ifndef LIGHT_H
#define LIGHT_H


#include <math.h>
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
    Light(float yaw=M_PI/2.0f, float pitch=M_PI/4.0f);



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

    /**
     * @brief Move the light for have a theta angle between the vector position and the plan xz of the world.
     * @param theta a angle in radian
     */
    void moveAroundXZ(float theta);


    void setFixePosition();
    void setFixePosition(float yaw, float pitch);

    glm::vec3 position() const;

    float yaw() const;

    float pitch() const;

private:
    glm::vec3 _position; /** < The position of the light */
    glm::vec2 _oldmoussePosition; /** < The postion of the mousse */


    float _yaw;         /** Euler's angle for the rotation around the y axis  */
    float _pitch;       /** Euler's angle for the rotation around the xz plan */

    /**
     * @brief set and normalize a vector in the middle of the screen.
     * @param v : the vector to center and normalize.
     * @param width : the width of the screen.
     * @param height : the height of the screen.
     * @return
     */
    glm::vec2 centerAndNormalize(glm::vec2 v, float width, float height);


    /**
     * @brief Compute the new position with Euler's angles _yaw and _pitch
     */
    void updatePosition();

};

#endif // LIGHT_H
