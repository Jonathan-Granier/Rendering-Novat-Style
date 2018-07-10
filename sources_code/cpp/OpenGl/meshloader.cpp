#include "meshloader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <iostream>
#include <sstream>

using namespace std;
using namespace glm;



#define NOTEXTUREOBJ 1

MeshLoader::MeshLoader()
{}


shared_ptr<Mesh> MeshLoader::vertexFromObj(const string &path)
{


    string lineHeader;
    string lineGarbage;
    string lineFace;
    vector<unsigned int> positionIndices, texCoordIndices, normalIndices;
    vector<vec3> positions;
    vector<vec2> texCoords;
    vector<vec3> normals;
    vector<Vertex> vertices;


    cout << "Loading OBJ from " << path << "..." << endl;
    ifstream file(path,ios::in);



    if(!file){
        cerr << "Impossible to open the file from " << path << endl;
        exit(0);
    }


    while(!file.eof()){
        file >> lineHeader;
        if ( lineHeader.compare("v") == 0 ){ // Position
            vec3 position;
            file >> position.x >> position.y >> position.z;
            positions.push_back(position);

        }else if ( lineHeader.compare("vt") == 0 ){ // Texture coord
            vec2 texCoord;
            file >> texCoord.x >> texCoord.y;

            // TODO test
            //texCoord.y = -texCoord.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            texCoords.push_back(texCoord);
        }else if ( lineHeader.compare("vn") == 0 ){ // Normal
            vec3 normal;
            file >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }else if ( lineHeader.compare("f") == 0 ){ // Face

            unsigned int positionIndex[3], texCoordIndex[3], normalIndex[3];


            getline(file,lineFace,'/');
            positionIndex[0] = stoi(lineFace);
            getline(file,lineFace,'/');
            if(NOTEXTUREOBJ)
                texCoordIndex[0]=0;
            else
                texCoordIndex[0] = stoi(lineFace);
            getline(file,lineFace,' ');
            normalIndex[0] = stoi(lineFace);
            getline(file,lineFace,'/');
            positionIndex[1] = stoi(lineFace);
            getline(file,lineFace,'/');

            if(NOTEXTUREOBJ)
                texCoordIndex[1]=0;
            else
                texCoordIndex[1] = stoi(lineFace);
            getline(file,lineFace,' ');
            normalIndex[1] = stoi(lineFace);
            getline(file,lineFace,'/');
            positionIndex[2] = stoi(lineFace);
            getline(file,lineFace,'/');
            if(NOTEXTUREOBJ)
                texCoordIndex[2]=0;
            else
                texCoordIndex[2] = stoi(lineFace);
            getline(file,lineFace);
            normalIndex[2] = stoi(lineFace);
        
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
        Vertex v;/**/
        if(NOTEXTUREOBJ)
            v = Vertex(positions[ positionIndex-1],normals[ normalIndex-1]);
        else/**/ //TODO
            v = Vertex(positions[ positionIndex-1],normals[ normalIndex-1 ],texCoords[ texCoordIndex-1 ]);
        vertices.push_back(v);


        }

    return indexVBO(vertices);



}

shared_ptr<LoadTexture> MeshLoader::textureFromDEM(const vector<string> &filepaths){

    /*

    Format d'un fichier DEM

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
    std::shared_ptr<FileInfo> currentFileInfo;

    stringstream iss;
    string value;
    vector<float> data;
    vector<std::shared_ptr<FileInfo>> fileInfos = getFileInfosFromFiles(filepaths);
    vector<vector<unsigned int>> schema = setupSchema(fileInfos);




    for(iSchemaIndex = 0 ; iSchemaIndex < schema.size() ; iSchemaIndex++){
        for(unsigned int i=0;i<fileInfos[0]->nrows;i++){

            for(jSchemaIndex = 0; jSchemaIndex < schema[iSchemaIndex].size(); jSchemaIndex++){
                currentFileInfo = fileInfos[schema[iSchemaIndex][jSchemaIndex]];
                getline(currentFileInfo->filestream,value);
                iss << value;
                getline(iss,value,' ');// Throw the first ' '
                for(unsigned int j=0;j<currentFileInfo->ncols;j++){
                    getline(iss,value,' ');
                    data.push_back(stof(value));

                }
                iss.clear();
            }
        }
    }
    /*
    vec3 shift_Pos(currentFileInfo->ncols*schema[0].size()/2 * currentFileInfo->offset,
                        (miny+maxy)/2,
                        currentFileInfo->nrows*schema.size()/2 * currentFileInfo->offset);
    for(unsigned int i=0;i<vertices.size();i++){
        vertices[i].Normal = normalize(vertices[i].Normal);
        vertices[i].Position -= shift_Pos;
    }

    */

    vector<float> heightMapData;
    int width = fileInfos[0]->ncols*schema[0].size();
    int height = fileInfos[0]->nrows*schema.size();
    unsigned int index = 0;
    // Reverse texture
    for(int i = height-1 ; i>= 0 ; i--){
        for(int j=0; j < width; j++){
            index = i*width + j;
            heightMapData.push_back(data[index]);

        }
    }
    shared_ptr<LoadTexture> heightMap = make_shared<LoadTexture>("heightMap", heightMapData,GL_R32F, GL_RED, width,height);
    heightMap->setHeightMapOffset(currentFileInfo->offset);
    return heightMap;

}



shared_ptr<Mesh> MeshLoader::vertexFromHeightMap(vector<float> data, int width, int height,float offset){

    if(data.size() != (unsigned int) width*height){
        cerr << "[vertexFormHeightMap] : incorrect size of data. Have : " << data.size() << " data but : " << width*height << " expected." << endl;
    }
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    float ymin(10000.0),ymax(0.0); // Altitude min and max for find the median
    unsigned int currentIndex = 0;


    // First Line
    for(int j=0 ; j<width ; j++){
        Vertex v = Vertex(j*offset,
                          data[currentIndex],
                          0.0f,
                          (float)j/(float)(width-1),
                          0.0f);
        vertices.push_back(v);
        if(data[currentIndex] > ymax) ymax = data[currentIndex];
        if(data[currentIndex] < ymin) ymin = data[currentIndex];
        currentIndex++;
    }


    for(int i=1 ; i<height ; i++){
        for(int j=0 ; j<width ; j++){
            Vertex v = Vertex(j*offset,
                              data[currentIndex],
                              i*offset,
                              (float)j/(float)(width-1),
                              (float)i/(float)(height-1));
            vertices.push_back(v);
            if(data[currentIndex] > ymax) ymax = data[currentIndex];
            if(data[currentIndex] < ymin) ymin = data[currentIndex];


            //Case 2 and 3     b
            //               / |s
            //              c -a
            if(j!=0)
            {
                indices.push_back(currentIndex);
                indices.push_back(currentIndex-width);
                indices.push_back(currentIndex-1);
                computeNormal(&vertices[currentIndex],
                              &vertices[currentIndex-width],
                              &vertices[currentIndex-1]);

            }



            // Case 1 and 2    c- b
            //                 | /
            //                 a
            if(j!=width-1 )
            {
                indices.push_back(currentIndex);
                indices.push_back(currentIndex-width+1);
                indices.push_back(currentIndex-width);
                computeNormal(&vertices[currentIndex],
                              &vertices[currentIndex-width+1],
                              &vertices[currentIndex-width]);

            }

            currentIndex++;

        }
    }


    vec3 shift_Pos(width/2 * offset,
                        (ymin+ymax)/2,
                        height/2 * offset);
    for(unsigned int i=0;i<vertices.size();i++){
        vertices[i].normal = normalize(vertices[i].normal);
        vertices[i].position -= shift_Pos;
    }



    return make_shared<Mesh>(vertices,indices,width,height,ymin,ymax);


}



/************************************************
 *              Private Functions               *
 ************************************************/


shared_ptr<Mesh> MeshLoader::indexVBO(vector<Vertex> vertices){

    unsigned int i;
    vector<unsigned int> indices;
    vector<Vertex> indexVertices;
    map<Vertex,unsigned int> VertexToOutIndex;


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

    }
    return make_shared<Mesh>(indexVertices,indices);
}


bool MeshLoader::getSimilarVertexIndex(Vertex &v,map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result){
    map<Vertex,unsigned int>::iterator it = VertexToOutIndex.find(v);
    if(it == VertexToOutIndex.end())
    {
        return false;
    }
    else{
        result = it->second;
        return true;
    }

}
//TODO remonter l'erreur
void MeshLoader::checkHeader(string value,string goal){
    if(value.compare(goal) != 0)
        cerr << "Error in DEM file header | Expected: " << goal << " Read: " << value << endl;


}

// V1,V2,V3 in counterclockwise direction !

void MeshLoader::computeNormal(Vertex *v1, Vertex *v2, Vertex *v3){
    vec3 v12 = v2->position - v1->position;
    vec3 v13 = v3->position - v1->position;
    vec3 nf  = normalize(cross(v12,v13));

    v1->normal+=nf;
    v2->normal+=nf;
    v3->normal+=nf;

}


//TODO remonter l'erreur pour l'afficher en graphique
vector<std::shared_ptr<MeshLoader::FileInfo>> MeshLoader::getFileInfosFromFiles(const vector<string> &filepaths){
    vector<std::shared_ptr<FileInfo>> fileInfos;


    for(unsigned int i=0; i<filepaths.size();i++){
        std::shared_ptr<FileInfo> f = make_shared<FileInfo>();

        f->filestream = ifstream(filepaths[i],ios::in);
        if(!f->filestream){
            cerr << "Impossible to open the file from " << filepaths[i] << endl;
            exit(0);
        }
        readHeader(f);
        fileInfos.push_back(f);
    }

    //check info

    for(unsigned int i=1;i<fileInfos.size();i++){
        if(fileInfos[i]->ncols != fileInfos[0]->ncols|| fileInfos[i]->nrows!=fileInfos[0]->nrows || fileInfos[i]->offset!=fileInfos[0]->offset )
        {
            cerr << "Can not read files with different headers (nrows, ncols and offset)" << endl;
            exit(0);
        }
    }
    return fileInfos;
}


void MeshLoader::readHeader(std::shared_ptr<FileInfo> fileInfo)
{

    string value;
    //Number of colomns
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"ncols");
    getline(fileInfo->filestream,value);
    fileInfo->ncols = stoi(value);

    //Number of lines
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"nrows");
    getline(fileInfo->filestream,value);
    fileInfo->nrows = stoi(value);

    //Position x of the corner
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"xllcorner");
    getline(fileInfo->filestream,value);
    fileInfo->xllcorner = stof(value);

    //Position y of the corner
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"yllcorner");
    getline(fileInfo->filestream,value);
    fileInfo->yllcorner = stof(value);

    //Size of a cell
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"cellsize");
    getline(fileInfo->filestream,value);
    fileInfo->offset = stof(value);

    //Error value TODO USE
    getline(fileInfo->filestream,value,' ');
    checkHeader(value,"NODATA_value");
    getline(fileInfo->filestream,value);
    fileInfo->noDataValue = stof(value);
}


//Peu opti mais peu de fichier (<100) donc osef
vector<vector<unsigned int>> MeshLoader::setupSchema(const std::vector<std::shared_ptr<FileInfo> > &fileInfos){
    unsigned int i,j,k;
    float xSizeSlab = fileInfos[0]->ncols*fileInfos[0]->offset;
    float ySizeSlab = fileInfos[0]->nrows*fileInfos[0]->offset;
    float xmin = fileInfos[0]->xllcorner,
          xmax = fileInfos[0]->xllcorner,
          ymin = fileInfos[0]->yllcorner,
          ymax = fileInfos[0]->yllcorner;

    for(i=1;i<fileInfos.size();i++){
        if(fileInfos[i]->xllcorner < xmin) xmin = fileInfos[i]->xllcorner;
        if(fileInfos[i]->xllcorner > xmax) xmax = fileInfos[i]->xllcorner;
        if(fileInfos[i]->yllcorner < ymin) ymin = fileInfos[i]->yllcorner;
        if(fileInfos[i]->yllcorner > ymax) ymax = fileInfos[i]->yllcorner;
    }

    unsigned int ncols = (xmax - xmin)/(xSizeSlab) + 1;
    unsigned int nrows = (ymax - ymin)/(ySizeSlab) + 1;

    vector<vector<unsigned int>> schema;


    for(i=0 ; i<nrows ; i++){
        vector<unsigned int> schemaLine;
        for(j=0 ; j<ncols ; j++){
            for(k=0 ; k<fileInfos.size() ; k++){
                if(fileInfos[k]->xllcorner == xmin+j*xSizeSlab && fileInfos[k]->yllcorner == ymax - i*ySizeSlab){
                    schemaLine.push_back(k);
                }
            }
        }
        schema.push_back(schemaLine);
    }
    return schema;
}
