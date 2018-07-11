/**
* @file shader.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/

#ifndef SHADER_H
#define SHADER_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>



#include <glm/glm.hpp>
#include <string>
#include <vector>

/**
* @brief The Shader class, opens, compiles and executes a vertex shader and a fragment shader.
* Input :
*    path of a vertex shader and a fragment shader.
* Use :
*      use/disable to activate/disable the shaders
*       reload to recompute the shaders
*       set... to set a uniform var to the shaders.
 */
class Shader
{
public:


    /**
     * @brief Create a new shader and initialize it.
     * @param vertexPath     a path of a vertex shader.
     * @param fragmentPath   a path of a fragment shader.
     */
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    ~Shader();

    /**
     * @brief Add a new shader and initialize it.
     * @param vertexPath    a path of a vertex shader.
     * @param fragmentPaht  a path of a fragment shader.
     */

    /**
     * @brief activate the current shader.
     */
    void use();

    /**
     * @brief disable the shaders.
     */
    void disable();

    /**
     * @brief Read and compile all shaders
     */
    void reload();

    /**
     * @brief get the current id program.
     * @return the current id program.
     */
    unsigned int getId() const;



    // utility uniform functions
    /**
     * @brief set a boolean like a uniform value into the current sharders.
     * @param name      the name of the boolean.
     * @param value     the value of the boolean.
     */
    void setBool(const std::string &name, bool value);
    /**
     * @brief set a integer like a uniform value into the current sharders.
     * @param name      the name of the integer.
     * @param value     the value of the integer.
     */
    void setInt(const std::string &name, int value);
    /**
     * @brief set a float like a uniform value into the current sharders.
     * @param name      the name of the float.
     * @param value     the value of the float.
     */
    void setFloat(const std::string &name, float value);
    /**
     * @brief set a 2D vector like a uniform value into the current sharders.
     * @param name      the name of the 2D vector.
     * @param value     the value of the 2D vector.
     */
    void setVec2(const std::string &name, const glm::vec2 &value);
    /**
     * @brief set a 2D vector like a uniform value into the current sharders.
     * @param name      the name of the 2D vector.
     * @param x         the x value of the 2D vector.
     * @param y         the y value of the 2D vector.
     */
    void setVec2(const std::string &name, float x, float y);
    /**
     * @brief set a 2D vector like a uniform value into the current sharders.
     * @param name      the name of the 2D vector.
     * @param value     the value of the 2D vector.
     */
    void setVec3(const std::string &name, const glm::vec3 &value);
    /**
     * @brief set a 3D vector like a uniform value into the current sharders.
     * @param name      the name of the 3D vector.
     * @param x         the x value of the 3D vector.
     * @param y         the y value of the 3D vector.
     * @param z         the z value of the 3D vector.
     */
    void setVec3(const std::string &name, float x, float y, float z);
    /**
     * @brief set a 4D vector like a uniform value into the current sharders.
     * @param name      the name of the 4D vector.
     * @param value     the value of the 4D vector.
     */
    void setVec4(const std::string &name, const glm::vec4 &value);
    /**
     * @brief set a 4D vector like a uniform value into the current sharders.
     * @param name      the name of the 4D vector.
     * @param x         the x value of the 4D vector.
     * @param y         the y value of the 4D vector.
     * @param z         the z value of the 4D vector.
     * @param w         the w value of the 4D vector.
     */
    void setVec4(const std::string &name, float x, float y, float z, float w);
    /**
     * @brief set a 2D matrix like a uniform value into the current sharders.
     * @param name      the name of the 2D matrix.
     * @param value     the value of the 2D matrix.
     */
    void setMat2(const std::string &name, const glm::mat2 &mat);
    /**
     * @brief set a 3D matrix like a uniform value into the current sharders.
     * @param name      the name of the 3D matrix.
     * @param value     the value of the 3D matrix.
     */
    void setMat3(const std::string &name, const glm::mat3 &mat);
    /**
     * @brief set a 4D matrix like a uniform value into the current sharders.
     * @param name      the name of the 4D matrix.
     * @param value     the value of the 4D matrix.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat);





private:

     /** The program ID*/
    unsigned int _id;

    /** The path of the vertex shader*/
    const GLchar* _vertexPath;

    /** The path of the fragment shader*/
    const GLchar* _fragmentPath;

    /** Name of the shader */
    std::string _name;


    /**
     * @brief Reads, compiles the vertex and the fragment of the current shader and store the id
     * @shaderInfo      The current shader
     */
    void initialize();


    /**
     * @brief Check if the compilation or the linkage went fine.
     * @param shader    the id of the shader or the program.
     * @param type      the type of the shader : PROGRAMME , VERTEX or FRAGMENT.
     * @param name      name of the shader.
     */
    void checkCompileErrors(GLuint shader, std::string type, std::string name);

    /**
     * @brief Get the name of the shader from the vertexPath.
     * @param vertexPath    The path of the vertex shader.
     * @return the name of the shader.
     */
    std::string getName(const GLchar *vertexPath);
};

#endif // SHADER_H
