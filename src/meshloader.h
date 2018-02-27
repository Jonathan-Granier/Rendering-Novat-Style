#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "progressinfo.h"

#include "glm/glm.hpp"
#include "mesh.h"
#include "progressinfo.h"



class MeshLoader
{
public:
    MeshLoader(ProgressInfo *progressInfo);

    //std::vector<Vertex> vertexFromHardCode();
    Mesh* vertexFromHardCode();
    Mesh* vertexFromObj(const std::string &path);
    Mesh* vertexFromMNT(const std::vector<std::string> &filepaths);


private:

    struct FileInfo{
            std::ifstream filestream;
            unsigned int ncols;
            unsigned int nrows;
            float xllcorner;
            float yllcorner;
            float offset;
            float noDataValue;
        };



    Mesh *indexVBO(std::vector<Vertex> vertices);
    bool getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result);
    void checkHeader(std::string value, std::string goal);
    void computeNormal(Vertex *v1, Vertex *v2, Vertex *v3);


    std::vector<FileInfo> getFileInfosFromFiles(const std::vector<std::string> &filepaths);
    void readHeader(FileInfo *fileInfo);
    std::vector<std::vector<unsigned int>> setupSchema(const std::vector<FileInfo> &fileInfos);




    ProgressInfo *_progressInfo;




};

#endif // MESHLOADER_H
