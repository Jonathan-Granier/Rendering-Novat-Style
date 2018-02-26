#include "meshloader.h"
#include "glm/gtx/string_cast.hpp"


MeshLoader::MeshLoader(ProgressInfo *p) :
    _progressInfo(p)
{}

// A cube without normal
Mesh* MeshLoader::vertexFromHardCode()
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
Mesh* MeshLoader::vertexFromObj(const std::string &path)
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
//TODO Faire les normales / Corriger les textures
Mesh* MeshLoader::vertexFromMNT(const std::string &path)
{
    std::cout << "Loading MNT " << path << "..." << std::endl;

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

    unsigned int ncols;
    unsigned int nrows;
    unsigned int currentIndice;
    float offset;
    float noDataValue;

    float miny(10000.0),maxy(0.0);
    std::stringstream iss;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> normalFace;
    std::string value;



    std::ifstream file(path,std::ios::in);



    if(!file){
        std::cerr << "Impossible to open the file from " << path << std::endl;
        exit(0);
    }

    // Read header

    getline(file,value,' ');
    checkHeader(value,"ncols");
    getline(file,value);
    ncols = std::stoi(value);
    getline(file,value,' ');
    checkHeader(value,"nrows");
    getline(file,value);
    nrows = std::stoi(value);
    getline(file,value,' ');

    // xllcorner and yallcorner are unsave
    checkHeader(value,"xllcorner");
    getline(file,value);
    getline(file,value,' ');
    checkHeader(value,"yllcorner");
    getline(file,value);

    getline(file,value,' ');
    checkHeader(value,"cellsize");
    getline(file,value);
    offset = std::stof(value);
    getline(file,value,' ');
    checkHeader(value,"NODATA_value");
    getline(file,value);
    noDataValue = std::stof(value);

    // Read the first line

    getline(file,value);
    iss << value;
    getline(iss,value,' '); // Throw the first ' '
    for(unsigned int j=0;j<ncols;j++){
        getline(iss,value,' ');

        Vertex v = Vertex(j*offset,stof(value),0.0f,float(j)/float(nrows),0.0f);
        vertices.push_back(v);
        if(stof(value) > maxy) maxy = stof(value);
        if(stof(value) < miny) miny = stof(value);
        //Push vertex to vertices
    }
    iss.clear();
    //Read all data
    for(unsigned int i=1;i<nrows;i++){
        getline(file,value);
        iss << value;
        getline(iss,value,' ');// Throw the first ' '
        for(unsigned int j=0;j<ncols;j++){
            getline(iss,value,' ');
            Vertex v = Vertex(j*offset,stof(value),i*offset,float(j)/float(nrows),float(i)/float(ncols));
            vertices.push_back(v);

            if(stof(value) > maxy) maxy = stof(value);
            if(stof(value) < miny) miny = stof(value);

            currentIndice = ncols*i + j;

            // Inserting in the counterclockwise direction
            if(j!=0){
                indices.push_back(currentIndice);
                indices.push_back(currentIndice-ncols);
                indices.push_back(currentIndice-1);

                //Compute normal of the face and recompute the normal of each vertex of the face;
                computeNormal(&vertices[currentIndice],&vertices[currentIndice-ncols],&vertices[currentIndice-1]);

            }
            if(j!=ncols-1){

                indices.push_back(currentIndice);
                indices.push_back(currentIndice-ncols+1);
                indices.push_back(currentIndice-ncols);


                //Compute normal of the face and recompute the normal of each vertex of the face;
                computeNormal(&vertices[currentIndice],&vertices[currentIndice-ncols+1],&vertices[currentIndice-ncols]);
            }

        }
        iss.clear();
    }

    glm::vec3 shift_Pos(ncols/2*offset,(miny+maxy)/2,nrows/2*offset);
    for(unsigned int i=0;i<vertices.size();i++){
        vertices[i].Normal = glm::normalize(vertices[i].Normal);
        vertices[i].Position -= shift_Pos;
    }

    return new Mesh(vertices,indices);
}


/*Private */


Mesh *MeshLoader::indexVBO(std::vector<Vertex> vertices){


    std::cout << "Indexing data (on "<< vertices.size() <<" vertex) : Start" << std::endl;
    unsigned int i;
    std::vector<unsigned int> indices;
    std::vector<Vertex> indexVertices;
    std::map<Vertex,unsigned int> VertexToOutIndex;


    _progressInfo->setMark(vertices.size());
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
        _progressInfo->setProgress(i);

    }
    _progressInfo->progressEnd();

    std::cout << "Indexing data : Done" << std::endl;
    return new Mesh(indexVertices,indices);
}


bool MeshLoader::getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result){
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

void MeshLoader::checkHeader(std::string value,std::string goal){
    if(value.compare(goal) != 0)
        std::cerr << "Error in MNT file header | Expected: " << goal << " Read: " << value << std::endl;


}

// V1,V2,V3 in counterclockwise direction !

void MeshLoader::computeNormal(Vertex *v1, Vertex *v2, Vertex *v3){
    glm::vec3 v12 = v2->Position - v1->Position;
    glm::vec3 v13 = v3->Position - v1->Position;
    glm::vec3 nf  = glm::normalize(glm::cross(v13,v12));
    v1->Normal+=nf;
    v2->Normal+=nf;
    v3->Normal+=nf;
}
