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

// TODO doc with this exemple
/*  1  2  3  | 4  5  6
 *  7  8  9  | 10 11 12
 *  13 14 15 | 16 17 18
 * --------------------
 *  19 20 21 | 22 23 24
 *  25 26 27 | 28 29 30
 *  31 32 33 | 34 35 36

*/
Mesh* MeshLoader::vertexFromMNT(const std::vector<std::string> &filepaths)
{
    std::cout << "Loading MNT " << filepaths[0] << "..." << std::endl;

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




    unsigned int iSchemaIndex;
    unsigned int jSchemaIndex;
    unsigned int currentIndice;
    FileInfo currentFileInfo;



    float miny(10000.0),maxy(0.0); // Altitude min and max for find the median
    std::stringstream iss;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string value;
    std::vector<FileInfo> fileInfos = getFileInfosFromFiles(filepaths);
    std::vector<std::vector<unsigned int>> schema = setupSchema(fileInfos);
    float xSizeSlab = fileInfos[0].ncols*fileInfos[0].offset;
    float zSizeSlab = fileInfos[0].nrows*fileInfos[0].offset;

    // Reading the 1st line of files all at the top
    /*  1  2  3  | 4  5  6     <-- this
     *  7  8  9  | 10 11 12
     *  13 14 15 | 16 17 18
     * --------------------
     *  19 20 21 | 22 23 24
     *  25 26 27 | 28 29 30
     *  31 32 33 | 34 35 36
     **/

    for(jSchemaIndex = 0 ; jSchemaIndex < schema[0].size() ; jSchemaIndex++){
        currentFileInfo = fileInfos[schema[0][jSchemaIndex]];
        getline(currentFileInfo.filestream ,value);
        iss << value;
        getline(iss,value,' '); // Throw the first ' '
        for(unsigned int j=0;j<currentFileInfo.ncols;j++){
            getline(iss,value,' ');

            Vertex v = Vertex(j*currentFileInfo.offset+xSizeSlab*jSchemaIndex,stof(value),0.0f,float(j+jSchemaIndex*xSizeSlab)/float(schema[0].size()*currentFileInfo.ncols),0.0f);
            vertices.push_back(v);
            if(stof(value) > maxy) maxy = stof(value);
            if(stof(value) < miny) miny = stof(value);
            //Push vertex to vertices
        }
        iss.clear();
    }

//todo
    for(iSchemaIndex = 1 ; iSchemaIndex < schema.size() ; iSchemaIndex++){

    }

    //Read all data
    for(unsigned int i=1;i<fileInfo.nrows;i++){
        getline(fileInfo.filestream,value);
        iss << value;
        getline(iss,value,' ');// Throw the first ' '
        for(unsigned int j=0;j<fileInfo.ncols;j++){
            getline(iss,value,' ');
            Vertex v = Vertex(j*fileInfo.offset,stof(value),i*fileInfo.offset,float(j)/float(fileInfo.ncols),float(i)/float(fileInfo.nrows));
            vertices.push_back(v);

            if(stof(value) > maxy) maxy = stof(value);
            if(stof(value) < miny) miny = stof(value);

            currentIndice = fileInfo.ncols*i + j;

            // Inserting in the counterclockwise direction
            if(j!=0){
                indices.push_back(currentIndice);
                indices.push_back(currentIndice-fileInfo.ncols);
                indices.push_back(currentIndice-1);

                //Compute normal of the face and recompute the normal of each vertex of the face;
                computeNormal(&vertices[currentIndice],&vertices[currentIndice-fileInfo.ncols],&vertices[currentIndice-1]);

            }
            if(j!=fileInfo.ncols-1){

                indices.push_back(currentIndice);
                indices.push_back(currentIndice-fileInfo.ncols+1);
                indices.push_back(currentIndice-fileInfo.ncols);


                //Compute normal of the face and recompute the normal of each vertex of the face;
                computeNormal(&vertices[currentIndice],&vertices[currentIndice-fileInfo.ncols+1],&vertices[currentIndice-fileInfo.ncols]);
            }

        }
        iss.clear();
    }

    glm::vec3 shift_Pos(fileInfo.ncols/2*fileInfo.offset,(miny+maxy)/2,fileInfo.nrows/2*fileInfo.offset);
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


//TODO remonter l'erreur pour l'afficher en graphique
std::vector<MeshLoader::FileInfo> MeshLoader::getFileInfosFromFiles(const std::vector<std::string> &filepaths){
    std::vector<FileInfo> fileInfos;


    for(unsigned int i=0; i<filepaths.size();i++){

        fileInfos.push_back(FileInfo());
        fileInfos[i].filestream = std::ifstream(filepaths[i],std::ios::in);
        if(!fileInfos[i].filestream){
            std::cerr << "Impossible to open the file from " << filepaths[i] << std::endl;
            exit(0);
        }
        readHeader(&fileInfos[i]);
    }

    //check info

    for(unsigned int i=1;i<fileInfos.size();i++){
        if(fileInfos[i].ncols != fileInfos[0].ncols|| fileInfos[i].nrows!=fileInfos[0].nrows || fileInfos[i].offset!=fileInfos[0].offset )
        {
            std::cerr << "Can not read files with different headers (nrows, ncols and offset)" << std::endl;
        }
    }
    return fileInfos;
}


void MeshLoader::readHeader(MeshLoader::FileInfo *fileInfo)
{

    // Read header
    std::string value;
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"ncols");
    getline(fileInfo->filestream,value);
    fileInfo->ncols = std::stoi(value);
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"nrows");
    getline(fileInfo->filestream,value);
    fileInfo->nrows = std::stoi(value);
    getline(fileInfo->filestream,value,' ');

    // xllcorner and yallcorner are unsave
    checkHeader(value,"xllcorner");
    getline(fileInfo->filestream,value);
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"yllcorner");
    getline(fileInfo->filestream,value);

    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"cellsize");
    getline(fileInfo->filestream,value);
    fileInfo->offset = std::stof(value);
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"NODATA_value");
    getline(fileInfo->filestream,value);
    fileInfo->noDataValue = std::stof(value);
}


//Peu opti mais peu de fichier (<100) donc osef
std::vector<std::vector<unsigned int>> MeshLoader::setupSchema(const std::vector<FileInfo> &fileInfos){
    unsigned int i,j,k;
    float xSizeSlab = fileInfos[0].ncols*fileInfos[0].offset;
    float ySizeSlab = fileInfos[0].nrows*fileInfos[0].offset;
    float xmin = fileInfos[0].xllcorner,
          xmax = fileInfos[0].xllcorner,
          ymin = fileInfos[0].yllcorner,
          ymax = fileInfos[0].yllcorner;

    for(i=1;i<fileInfos.size();i++){
        if(fileInfos[i].xllcorner < xmin) xmin = fileInfos[i].xllcorner;
        if(fileInfos[i].xllcorner > xmax) xmax = fileInfos[i].xllcorner;
        if(fileInfos[i].yllcorner < ymin) ymin = fileInfos[i].yllcorner;
        if(fileInfos[i].yllcorner > ymax) ymax = fileInfos[i].yllcorner;
    }

    unsigned int ncols = (xmax - xmin)/(xSizeSlab) + 1;
    unsigned int nrows = (ymax - ymin)/(ySizeSlab) + 1;

    std::vector<std::vector<unsigned int>> schema;


    for(i=0 ; i<nrows ; i++){
        for(j=0 ; j<ncols ; j++){
            std::vector<int> schemaLine;
            for(k=0 ; k<fileInfos.size() ; k++){
                if(fileInfos[k].xllcorner == xmin+j*xSizeSlab && fileInfos[k].yllcorner == ymax - i*ySizeSlab){
                    schemaLine.push_back(k);
                    //schema[i][j]=k;
                }
            }
            std::cout<< schemaLine[j] << " | " ;
        }
        schema.push_back(schemaLine);
        std::cout << "---" << std::endl;
    }

    return schema;
}

