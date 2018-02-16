#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

class Shader
{
public:
    // the program ID
    unsigned int _ID;

    // constructor reads and builds the shader

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();

    void initialize(const GLchar *vertexPath, const GLchar *fragmentPath);
    // activate/disable the shader
    void use();
    void disable();
    // utility uniform functions
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setVec2(const string &name, const glm::vec2 &value) const;
    void setVec2(const string &name, float x, float y) const;
    void setVec3(const string &name, const glm::vec3 &value) const;
    void setVec3(const string &name, float x, float y, float z) const;
    void setVec4(const string &name, const glm::vec4 &value) const;
    void setVec4(const string &name, float x, float y, float z, float w);
    void setMat2(const string &name, const glm::mat2 &mat) const;
    void setMat3(const string &name, const glm::mat3 &mat) const;
    void setMat4(const string &name, const glm::mat4 &mat) const;


private:
    void checkCompileErrors(GLuint shader, string type);
};

#endif // SHADER_H
