#include "meshLoader.h"
#include "glm/gtx/string_cast.hpp"


meshLoader::meshLoader()
{

}

// A cube without normal
Mesh* meshLoader::vertexFromHardCode()
{
    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f)); // 1
    vertices.push_back(Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 0.0f)); // 2
    vertices.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f)); // 3
    vertices.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f)); // 3
    vertices.push_back(Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f)); // 1
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f)); // 1

    vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));


    vertices.push_back(Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f));

    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));

    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f));

    vertices.push_back(Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 0.0f));
    vertices.push_back(Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f));


    return indexVBO(vertices);

}
//TODO translate c reader to c++ reader (FILE to ifstream)
Mesh* meshLoader::vertexFromObj(const std::string &path)
{


    std::string lineHeader;
    std::string lineGarbage;
    std::string lineFace;
    std::vector<unsigned int> positionIndices, texCoordIndices, normalIndices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<Vertex> vertices;


    std::cout << "Loading OBJ from " << path << "..." << std::endl;
    std::ifstream file(path,std::ios::in);



    if(!file){
        std::cerr << "Impossible to open the file from " << path << std::endl;
        exit(0);
    }


    while(!file.eof()){
        file >> lineHeader;
        if ( lineHeader.compare("v") == 0 ){ // Position
            glm::vec3 position;
            file >> position.x >> position.y >> position.z;
            positions.push_back(position);

        }else if ( lineHeader.compare("vt") == 0 ){ // Texture coord
            glm::vec2 texCoord;
            file >> texCoord.x >> texCoord.y;

            // TODO test
            //texCoord.y = -texCoord.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            texCoords.push_back(texCoord);
        }else if ( lineHeader.compare("vn") == 0 ){ // Normal
            glm::vec3 normal;
            file >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }else if ( lineHeader.compare("f") == 0 ){ // Face

            unsigned int positionIndex[3], texCoordIndex[3], normalIndex[3];


            getline(file,lineFace,'/');
            positionIndex[0] = stoi(lineFace);
            getline(file,lineFace,'/');
            texCoordIndex[0] = stoi(lineFace);
            getline(file,lineFace,' ');
            normalIndex[0] = stoi(lineFace);
            getline(file,lineFace,'/');
            positionIndex[1] = stoi(lineFace);
            getline(file,lineFace,'/');
            texCoordIndex[1] = stoi(lineFace);
            getline(file,lineFace,' ');
            normalIndex[1] = stoi(lineFace);
            getline(file,lineFace,'/');
            positionIndex[2] = stoi(lineFace);
            getline(file,lineFace,'/');
            texCoordIndex[2] = stoi(lineFace);
            getline(file,lineFace);
            normalIndex[2] = stoi(lineFace);
            /*
            std::cout << "I read a face : " <<  positionIndex[0] << "/" << texCoordIndex[0] << "/" << normalIndex[0] << " " <<
                                                positionIndex[1] << "/" << texCoordIndex[1] << "/" << normalIndex[1] << " " <<
                                                positionIndex[2] << "/" << texCoordIndex[2] << "/" << normalIndex[2] << std::endl;
    */

            for(unsigned i=0;i<3;i++){
                positionIndices .push_back(positionIndex[i]);
                texCoordIndices .push_back(texCoordIndex[i]);
                normalIndices   .push_back(normalIndex[i]);
            }
        }else{
            // Other , ingore this line

            getline(file,lineGarbage);
        }
    }


    file.close();

    // For each vertex of each triangle
    for( unsigned int i=0; i<positionIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int positionIndex  = positionIndices[i];
        unsigned int texCoordIndex  = texCoordIndices[i];
        unsigned int normalIndex    = normalIndices[i];

        // Get the attributes thanks to the index
        Vertex v = Vertex(positions[ positionIndex-1 ],normals[ normalIndex-1 ],texCoords[ texCoordIndex-1 ]);
        vertices.push_back(v);


        }

    std::cout << "Loading OBJ from " << path << " done." << std::endl;
    return indexVBO(vertices);



}
//TODO
Mesh* meshLoader::vertexFromMNT(const std::string &path)
{
    std::cout << "Loading OBJ MNT " << path << "..." << std::endl;
    std::cerr << "NOT IMPLEMENTED" << std::endl;
    exit(0);





    /*

    Format d'un fichier MNT

    ncols       int
    nrows       int
    xllcorner   float
    yllcorner   float
    cellsize    float
    NODATA_value
    *DATA*
    */

    /*
    unsigned int ncols;
    unsigned int nrows;

    std::vector<Vertex> vertices;
*/



}


/*Private */


Mesh *meshLoader::indexVBO(std::vector<Vertex> vertices){


    std::cout << "Indexing data (on "<< vertices.size() <<" vertex) : Start" << std::endl;
    unsigned int i;
    std::vector<unsigned int> indices;
    std::vector<Vertex> indexVertices;
    std::map<Vertex,unsigned int> VertexToOutIndex;


    ProgressBar bar(std::cout);
    for(i=0 ; i < vertices.size();i++){

        unsigned int index;

        bool found = getSimilarVertexIndex(vertices[i],VertexToOutIndex,index);
        if(found){
            indices.push_back(index);
        }
        else{
            indexVertices.push_back(vertices[i]);
            unsigned int newindex = indexVertices.size() - 1;
            indices.push_back(newindex);
            VertexToOutIndex[vertices[i]] = newindex;
        }
        bar.update(i,vertices.size());

    }
    std::cout << std::endl;

    std::cout << "Indexing data : Done" << std::endl;
    return new Mesh(indexVertices,indices);
}


bool meshLoader::getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result){
    std::map<Vertex,unsigned int>::iterator it = VertexToOutIndex.find(v);
    if(it == VertexToOutIndex.end())
    {
        return false;
    }
    else{
        result = it->second;
        return true;
    }

}

