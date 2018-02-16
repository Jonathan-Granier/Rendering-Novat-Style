#include "shader.h"
#include "shader.h"

// Constructor : Compile and link the shaders to _ID


Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    initialize(vertexPath,fragmentPath);

}


Shader::~Shader(){
    if(glIsProgram(_ID)) {
      glDeleteProgram(_ID);
    }
}

void Shader::initialize(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
       string vertexCode, fragmentCode;
       ifstream vShaderFile, fShaderFile;
       // ensure ifstream objects can throw exceptions:
       vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
       fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
       try
       {
           // open files
           vShaderFile.open(vertexPath);
           fShaderFile.open(fragmentPath);
           stringstream vShaderStream, fShaderStream;
           // read file's buffer contents into streams
           vShaderStream << vShaderFile.rdbuf();
           fShaderStream << fShaderFile.rdbuf();
           // close file handlers
           vShaderFile.close();
           fShaderFile.close();
           // convert stream into string
           vertexCode   = vShaderStream.str();
           fragmentCode = fShaderStream.str();
       }
       catch(std::ifstream::failure e)
       {
           std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
       }
       const char* vShaderCode = vertexCode.c_str();
       const char* fShaderCode = fragmentCode.c_str();



       // 2. compile shaders
       unsigned int vertex, fragment;

       // vertex Shader
       vertex = glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertex, 1, &vShaderCode, NULL);
       glCompileShader(vertex);
       checkCompileErrors(vertex,"VERTEX");

       //Fragment Shader
       fragment = glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragment, 1, &fShaderCode, NULL);
       glCompileShader(fragment);
       // print compile errors if any
       checkCompileErrors(fragment,"FRAGMENT");

       // shader Program
       _ID = glCreateProgram();
       glAttachShader(_ID, vertex);
       glAttachShader(_ID, fragment);
       glLinkProgram(_ID);
       // print linking errors if any
       checkCompileErrors(_ID,"PROGRAM");
}

void Shader::use()
{
    glUseProgram(_ID);
}

void Shader::disable()
{
    glUseProgram(0);
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const string &name, bool value) const
{
   glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const string &name, int value) const
{
   glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const string &name, float value) const
{
   glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const string &name, const glm::vec2 &value) const
{
   glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const string &name, float x, float y) const
{
   glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const string &name, const glm::vec3 &value) const
{
   glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string &name, float x, float y, float z) const
{
   glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const string &name, const glm::vec4 &value) const
{
   glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const string &name, float x, float y, float z, float w)
{
   glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const string &name, const glm::mat2 &mat) const
{
   glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const string &name, const glm::mat3 &mat) const
{
   glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const string &name, const glm::mat4 &mat) const
{
   glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


// ----------------------- Private Function -------------------------------

void Shader::checkCompileErrors(GLuint shader, string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << std::endl;
        }
    }
}



