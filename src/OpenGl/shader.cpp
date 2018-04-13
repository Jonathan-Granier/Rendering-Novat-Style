#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Constructor : Compile and link the shaders to _ID

using namespace std;
using namespace glm;
Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    ShaderInfo *s = new ShaderInfo;
    s->fragmentPath = fragmentPath;
    s->vertexPath = vertexPath;
    s->name = getName(vertexPath);
    initialize(s);
    _shaderInfos.push_back(s);
    _currentIndexShader = 0;


}




Shader::~Shader(){

    for(ShaderInfo *s: _shaderInfos){
        if(glIsProgram(s->id)) {
          glDeleteProgram(s->id);
        }
        delete(s);
    }

}

void Shader::add(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    ShaderInfo *s = new ShaderInfo;
    s->fragmentPath = fragmentPath;
    s->vertexPath = vertexPath;
    s->name = getName(vertexPath);
    initialize(s);
    _shaderInfos.push_back(s);
}


void Shader::initialize(ShaderInfo *shaderInfo)
{

    initializeOpenGLFunctions();
    // 1. retrieve the vertex/fragment source code from filePath
       string vertexCode, fragmentCode;
       ifstream vShaderFile, fShaderFile;
       // ensure ifstream objects can throw exceptions:
       vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
       fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
       try
       {
           // open files
           vShaderFile.open(shaderInfo->vertexPath);
           fShaderFile.open(shaderInfo->fragmentPath);
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
       catch(ifstream::failure e)
       {
           cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
       }
       const char* vShaderCode = vertexCode.c_str();
       const char* fShaderCode = fragmentCode.c_str();



       // 2. compile shadersfragmentPaht
       unsigned int vertex, fragment;

       // vertex Shader
       vertex = glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertex, 1, &vShaderCode, NULL);
       glCompileShader(vertex);
       checkCompileErrors(vertex,"VERTEX",shaderInfo->name);

       //Fragment Shader
       fragment = glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragment, 1, &fShaderCode, NULL);
       glCompileShader(fragment);
       // print compile errors if any
       checkCompileErrors(fragment,"FRAGMENT",shaderInfo->name);

       // shader Program
       unsigned int id;
       id = glCreateProgram();
       glAttachShader(id, vertex);
       glAttachShader(id, fragment);
       glLinkProgram(id);
       // print linking errors if any
       checkCompileErrors(id,"PROGRAM",shaderInfo->name);
       shaderInfo->id = id;
}

void Shader::use()
{
    glUseProgram(_shaderInfos[_currentIndexShader]->id );
}

void Shader::disable()
{
    glUseProgram(0);
}

void Shader::next()
{
    _currentIndexShader++;
    if(_currentIndexShader==_shaderInfos.size())
        _currentIndexShader = 0;
}

void Shader::previous()
{
    if(_currentIndexShader==0)
       _currentIndexShader=_shaderInfos.size();
    _currentIndexShader--;
}

void Shader::reload()
{
    for(ShaderInfo *s : _shaderInfos){
        initialize(s);
    }
}

unsigned int Shader::ID() const
{
    return _shaderInfos[_currentIndexShader]->id ;
}


string Shader::name() const{
    return _shaderInfos[_currentIndexShader]->name;
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const string &name, bool value)
{
   glUniform1i(glGetUniformLocation(ID(), name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const string &name, int value)
{
   glUniform1i(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const string &name, float value)
{
   glUniform1f(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const string &name, const vec2 &value)
{
   glUniform2fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const string &name, float x, float y)
{
   glUniform2f(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const string &name, const vec3 &value)
{
   glUniform3fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string &name, float x, float y, float z)
{
   glUniform3f(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const string &name, const vec4 &value)
{
   glUniform4fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const string &name, float x, float y, float z, float w)
{
   glUniform4f(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const string &name, const mat2 &mat)
{
   glUniformMatrix2fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const string &name, const mat3 &mat)
{
   glUniformMatrix3fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const string &name, const mat4 &mat)
{
   glUniformMatrix4fv(glGetUniformLocation(_shaderInfos[_currentIndexShader]->id , name.c_str()), 1, GL_FALSE, &mat[0][0]);
}



// ----------------------- Private Function -------------------------------
void Shader::checkCompileErrors(GLuint shader, string type,string name)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cerr << "ERROR::SHADER_COMPILATION_ERROR of name : "<< name <<  " type: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            cerr << "ERROR::PROGRAM_LINKING_ERROR of name : "<< name <<  " type: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << endl;
        }
    }
}

string Shader::getName(const GLchar *vertexPath)
{
    string name(vertexPath);
    size_t lastDot = name.find_last_of(".");
    name = name.substr(0, lastDot);
    size_t lastSlash = name.find_last_of("/");
    return name.substr(lastSlash +1 , name.size());
}



