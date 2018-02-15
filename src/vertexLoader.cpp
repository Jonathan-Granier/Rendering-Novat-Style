#include "vertexLoader.h"

vertexLoader::vertexLoader()
{

}

// A cube without normal
std::vector<Vertex> vertexLoader::vertexFromHardCode()
{
    std::vector<Vertex> newVertex;
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f));

    newVertex.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));


    newVertex.push_back(Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f));

    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));

    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));

    newVertex.push_back(Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 0.0f));
    newVertex.push_back(Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f));
    return newVertex;
}
//TODO
std::vector<Vertex> vertexLoader::vertexFromObj(const std::string &path)
{

}
//TODO
std::vector<Vertex> vertexLoader::vertexFromMNT(const std::string &path)
{

}
