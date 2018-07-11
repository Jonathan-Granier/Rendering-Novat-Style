/**
* @file light.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/

#ifndef LIGHT_H
#define LIGHT_H


#include <math.h>
#include "glm/glm.hpp"
/**
 * @brief A basic light defined by two euler angle Yaw and Pitch in radian.
 * Use :
 *      Change Yaw with startMoveAroundYAxe and moveAroundYAxe (relative displacement).
 *      Change pitch with moveAroundXZ (absolute displacement)
 */
class Light
{
public:
    /**
     * @brief Basic constructor
     *
     * @param yaw       The yaw angle in radian of the light
     * @param pitch     The pitch angle in radian of the light
     */
    Light(float yaw=M_PI/2.0f, float pitch=M_PI/4.0f);



    /**
     * @brief Init the move of the light around the Y axe (yaw)
     *
     * @param moussPos      The actual position of the mousse.
     * @param width         The width of the OpenGL widget.
     * @param height        The height of the OpenGL widget.
     */
    void startMoveAroundYAxe(glm::vec2 moussePos,float width,float height);
    /**
     * @brief Move the light around the Y axe, use startMoveAroundYAxe before use this (yaw).
     *
     * @param moussePos : the actual position of the mousse.
     * @param width         The width of the OpenGL widget.
     * @param height        The height of the OpenGL widget.
     */
    void moveAroundYAxe(glm::vec2 moussePos,float width,float height);

    /**
     * @brief Move the light for have a theta angle between the vector direction and the plan xz of the world.
     * @param theta         A angle in radian.
     */
    void moveAroundXZ(float theta);

    /**
    * @brief Set a hard code direction.
    */
    void setFixeDirection();

    /**
    * @brief Set the yaw and the pitch of the light.
    *
    * @param yaw        The new yaw of the ligth.
    * @param pitch        The new pitch of the ligth.
    */
    void setFixeDirection(float yaw, float pitch);

    /**
    * @return The direction of the light, a normal 3D vector.
    */
    glm::vec3 getDirection() const;

    /**
    * @return The yaw angle in radian of the light
    */
    float getYaw() const;

    /**
    * @return The pitch angle in radian of the light
    */
    float getPitch() const;

private:
    /** The direction of the light */
    glm::vec3 _direction;
    /** The position of the mousse */
    glm::vec2 _oldmoussePosition;

    /** Euler's angle for the rotation around the y axis  */
    float _yaw;
    /** Euler's angle for the rotation around the xz plan */
    float _pitch;

    /**
     * @brief set and normalize a vector in the middle of the screen.
     * @param v : the vector to center and normalize.
     * @param width : the width of the OpenGL widget.
     * @param height : the height of the OpenGL widget.
     * @return a 2D vector.
     */
    glm::vec2 centerAndNormalize(glm::vec2 v, float width, float height);


    /**
     * @brief Compute the new direction with Euler's angles _yaw and _pitch
     */
    void updateDirection();

};

#endif // LIGHT_H
