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

    //TODO A REFAIRE

   /* std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };



   return new Mesh(vertices,indices);
   */
    return indexVBO(vertices);

}
//TODO translate c reader to c++ reader (FILE to ifstream)
Mesh* meshLoader::vertexFromObj(const std::string &path)
{
/*
    char lineHeader[128];
    char lineGarbage[1000];
    int res;
    std::vector<unsigned int> positionIndices, texCoordIndices, normalIndices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<Vertex> vertices;

    std::cout << "Loading OBJ from " << path << "..." << std::endl;
    FILE *file = fopen(path.c_str(),"r");

    if(file == NULL ){
        std::cerr << "Impossible to open the file from " << path << std::endl;
        exit(0);
    }


    fscanf(file, "%s",lineHeader);


    while(res != EOF){


        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 position;
            fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z );
            positions.push_back(position);
            std::cout << "I read a position : " << glm::to_string(position) << std::endl;

        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 texCoord;
            fscanf(file, "%f %f\n", &texCoord.x, &texCoord.y ); // TODO test
            //texCoord.y = -texCoord.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            texCoords.push_back(texCoord);
            std::cout << "I read a texCoord : " << glm::to_string(texCoord) << std::endl;
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            normals.push_back(normal);
            std::cout << "I read a normal : " << glm::to_string(normal) << std::endl;
        }else if ( strcmp( lineHeader, "f" ) == 0 ){

            unsigned int positionIndex[3], texCoordIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",  &positionIndex[0], &texCoordIndex[0], &normalIndex[0],
                                                                        &positionIndex[1], &texCoordIndex[1], &normalIndex[1],
                                                                        &positionIndex[2], &texCoordIndex[2], &normalIndex[2] );
            if (matches != 9){
                cerr << "Can't read this OBJ , error on a f line , there are not 9 elements" << endl;
                exit(0);
            }
            positionIndices .push_back(positionIndex[0]);
            positionIndices .push_back(positionIndex[1]);
            positionIndices .push_back(positionIndex[2]);
            texCoordIndices .push_back(texCoordIndex[0]);
            texCoordIndices .push_back(texCoordIndex[1]);
            texCoordIndices .push_back(texCoordIndex[2]);
            normalIndices   .push_back(normalIndex[0]);
            normalIndices   .push_back(normalIndex[1]);
            normalIndices   .push_back(normalIndex[2]);
        }else{
            // Other , ingore this line

            fgets(lineGarbage, 1000, file);
            std::cout << "I throw : " << lineGarbage << std::endl;
        }
        res = fscanf(file, "%s", lineHeader);

    }
    fclose(file);
*/


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
        if ( lineHeader.compare("v") == 0 ){
            glm::vec3 position;
            file >> position.x >> position.y >> position.z;
            positions.push_back(position);

        }else if ( lineHeader.compare("vt") == 0 ){
            glm::vec2 texCoord;
            file >> texCoord.x >> texCoord.y;

            // TODO test
            //texCoord.y = -texCoord.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            texCoords.push_back(texCoord);
        }else if ( lineHeader.compare("vn") == 0 ){
            glm::vec3 normal;
            file >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }else if ( lineHeader.compare("f") == 0 ){

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
            //std::cout << "I throw : " << lineGarbage << std::endl;
        }
    }

    std::cout << "Loading OBJ from " << path << " done." << std::endl;
    file.close();


    // For each vertex of each triangle
    for( unsigned int i=0; i<positionIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int positionIndex    = positionIndices[i];
        unsigned int texCoordIndex        = texCoordIndices[i];
        unsigned int normalIndex    = normalIndices[i];

        // Get the attributes thanks to the index
        Vertex v = Vertex(positions[ positionIndex-1 ],normals[ normalIndex-1 ],texCoords[ texCoordIndex-1 ]);
        vertices.push_back(v);


        }


    return indexVBO(vertices);

}
//TODO
Mesh* meshLoader::vertexFromMNT(const std::string &path)
{
    std::cout << "Loading OBJ MNT " << path << "..." << std::endl;
    std::cerr << "NOT IMPLEMENTED" << std::endl;
    exit(0);
}


/*Private */


Mesh *meshLoader::indexVBO(std::vector<Vertex> vertices){
    unsigned int i;
     std::vector<unsigned int> indices;
     std::vector<Vertex> indexVertices;


    //std::map<Vertex,unsigned int> VertexToOutIndex;
    for(i=0 ; i < vertices.size();i++){
        unsigned int index;

        bool found = getSimilarVertexIndex(vertices[i],indexVertices,index);
        if(found){
            indices.push_back(index);
        }
        else{
            indexVertices.push_back(vertices[i]);
            indices.push_back(indexVertices.size()-1);
        }
    }

    return new Mesh(indexVertices,indices);
}


bool meshLoader::getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result){
    std::map<Vertex,unsigned int>::iterator it = VertexToOutIndex.find(v);
    if(it == VertexToOutIndex.end())
    {
        std::cout << glm::to_string(v.Position) << glm::to_string(v.Normal) << glm::to_string(v.TexCoords) << " notfound" << std::endl; ;
        return false;
    }
    else{
        std::cout << "In foud u" << std::endl;
        result = it->second;
        return true;
    }

}


bool meshLoader::getSimilarVertexIndex(Vertex &in_v,std::vector<Vertex> &out_v,unsigned int & result){
    for(unsigned int i=0; i<out_v.size();i++){
        if(
            is_near(in_v.Position.x,out_v[i].Position.x) &&
            is_near(in_v.Position.y,out_v[i].Position.y) &&
            is_near(in_v.Position.z,out_v[i].Position.z) &&
            is_near(in_v.Normal.x,out_v[i].Normal.x) &&
            is_near(in_v.Normal.y,out_v[i].Normal.y) &&
            is_near(in_v.Normal.z,out_v[i].Normal.z) &&
            is_near(in_v.TexCoords.x,out_v[i].TexCoords.x) &&
            is_near(in_v.TexCoords.y,out_v[i].TexCoords.y) )
        {
            result = i;
            return true;
        }
    }
    return false;
}

bool meshLoader::is_near(float v1, float v2){
    return fabs(v1-v2)< 0.01f;
}

