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
#include <fstream>
#include <sstream>
#include <iostream>




class Shader
{
public:
    // the program ID
    unsigned int _ID;

    // constructor reads and builds the shader

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();

    void initialize();
    // activate/disable the shader
    void use();
    void disable();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;


private:

    const GLchar* _vertexPath;
    const GLchar* _fragmentPath;

    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // SHADER_H
