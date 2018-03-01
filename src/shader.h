#ifndef SHADER_H
#define SHADER_H

//#include <glad/glad.h>
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>


#include <glm/glm.hpp>
#include <string>




/**
 * @brief The Shader class, opens, compiles and executes a vertex shader and a fragment shader
 */
class Shader
{
public:


        // constructor
    /**
     * @brief Reads, compiles and stores the ID program of the shaders
     * @param vertexPath : a path of a vertex shader
     * @param fragmentPath : a path of a fragment shader
     */
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    ~Shader();


    /**
     * @brief Reads, compiles the vertex and the fragment shader
     */
    void initialize();

    /**
     * @brief activate the shader
     */
    void use();
    /**
     * @brief disable the shader
     */
    void disable();

    /**
     * @brief get the id program
     * @return the id program
     */
    unsigned int ID() const;

    // utility uniform functions
    /**
     * @brief set a boolean like a uniform value into the sharders
     * @param name : the name of the boolean
     * @param value : the value of the boolean
     */
    void setBool(const std::string &name, bool value) const;
    /**
     * @brief set a integer like a uniform value into the sharders
     * @param name : the name of the integer
     * @param value : the value of the integer
     */
    void setInt(const std::string &name, int value) const;
    /**
     * @brief set a float like a uniform value into the sharders
     * @param name : the name of the float
     * @param value : the value of the float
     */
    void setFloat(const std::string &name, float value) const;
    /**
     * @brief set a 2D vector like a uniform value into the sharders
     * @param name : the name of the 2D vector
     * @param value : the value of the 2D vector
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    /**
     * @brief set a 2D vector like a uniform value into the sharders
     * @param name : the name of the 2D vector
     * @param x : the x value of the 2D vector
     * @param y :  the y value of the 2D vector
     */
    void setVec2(const std::string &name, float x, float y) const;
    /**
     * @brief set a 2D vector like a uniform value into the sharders
     * @param name : the name of the 2D vector
     * @param value : the value of the 2D vector
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    /**
     * @brief set a 3D vector like a uniform value into the sharders
     * @param name : the name of the 3D vector
     * @param x : the x value of the 3D vector
     * @param y : the y value of the 3D vector
     * @param z : the z value of the 3D vector
     */
    void setVec3(const std::string &name, float x, float y, float z) const;
    /**
     * @brief set a 4D vector like a uniform value into the sharders
     * @param name : the name of the 4D vector
     * @param value : the value of the 4D vector
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    /**
     * @brief set a 4D vector like a uniform value into the sharders
     * @param name : the name of the 4D vector
     * @param x : the x value of the 4D vector
     * @param y : the y value of the 4D vector
     * @param z : the z value of the 4D vector
     * @param w : the w value of the 4D vector
     */
    void setVec4(const std::string &name, float x, float y, float z, float w);
    /**
     * @brief set a 2D matrix like a uniform value into the sharders
     * @param name : the name of the 2D matrix
     * @param value : the value of the 2D matrix
     */
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    /**
     * @brief set a 3D matrix like a uniform value into the sharders
     * @param name : the name of the 3D matrix
     * @param value : the value of the 3D matrix
     */
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    /**
     * @brief set a 4D matrix like a uniform value into the sharders
     * @param name : the name of the 4D matrix
     * @param value : the value of the 4D matrix
     */
    void setMat4(const std::string &name, const glm::mat4 &mat) const;




private:
    /**
     * @brief the program ID
     */
    unsigned int _ID;

    /**
     * @brief the path of the vertex shader
     */
    const GLchar* _vertexPath;
    /**
     * @brief the path of the fragment shader
     */
    const GLchar* _fragmentPath;

    /**
     * @brief Check if the compilation or the linkage went fine
     * @param shader : the id of the shader or the program
     * @param type : the type of the shader : PROGRAMME , VERTEX or FRAGMENT
     */
    void checkCompileErrors(GLuint shader, std::string type);
    //TODO remonter les erreurs
};

#endif // SHADER_H
