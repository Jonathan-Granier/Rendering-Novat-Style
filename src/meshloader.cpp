#include "meshloader.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace glm;

MeshLoader::MeshLoader(ProgressInfo *p) :
    _progressInfo(p)
{}


Mesh* MeshLoader::vertexFromHardCode()
{
    // A cube without normal
    vector<Vertex> vertices;
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
Mesh* MeshLoader::vertexFromObj(const string &path)
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
            cout << "I read a face : " <<  positionIndex[0] << "/" << texCoordIndex[0] << "/" << normalIndex[0] << " " <<
                                                positionIndex[1] << "/" << texCoordIndex[1] << "/" << normalIndex[1] << " " <<
                                                positionIndex[2] << "/" << texCoordIndex[2] << "/" << normalIndex[2] << endl;
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

    cout << "Loading OBJ from " << path << " done." << endl;
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
Mesh* MeshLoader::vertexFromMNT(const vector<string> &filepaths)
{
    cout << "Loading MNT from : " << endl;
    for(unsigned int i=0;i< filepaths.size() ; i++ ){
        cout << filepaths[i] << "..." << endl;
    }
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
    FileInfo* currentFileInfo;



    float miny(10000.0),maxy(0.0); // Altitude min and max for find the median
    stringstream iss;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    string value;
    float floatValue;
    vector<FileInfo*> fileInfos = getFileInfosFromFiles(filepaths);
    vector<vector<unsigned int>> schema = setupSchema(fileInfos);
    float xSizeSlab = fileInfos[0]->ncols*fileInfos[0]->offset;
    float zSizeSlab = fileInfos[0]->nrows*fileInfos[0]->offset;

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
        getline(currentFileInfo->filestream ,value);
        iss << value;
        getline(iss,value,' '); // Throw the first ' '
        for(unsigned int j=0;j<currentFileInfo->ncols;j++){
            getline(iss,value,' ');
            floatValue = stof(value);
            //Insert x,y,z coord and uv TexCoord;
            Vertex v = Vertex(j*currentFileInfo->offset+xSizeSlab*jSchemaIndex,                                  //x
                              floatValue,                                                                       //y (altitude)
                              0.0f,                                                                             //z
                              float(j+jSchemaIndex*xSizeSlab)/float(schema[0].size()*currentFileInfo->ncols),    //u
                              0.0f);                                                                            //v
            vertices.push_back(v);

            if(floatValue > maxy) maxy = floatValue;
            if(floatValue < miny) miny = floatValue;
            //Push vertex to vertices
        }
        iss.clear();
    }
    /*
    Check if we already read the first line : 1 - yes , 0 - no
    we init i of the 3rd for with this variable
    */
    unsigned int jumpTheFirstLine=1; //

    // Reading all lines except the first
    /*  1  2  3  | 4  5  6
     *  7  8  9  | 10 11 12     <-- this
     *  13 14 15 | 16 17 18     <-- this
     * --------------------
     *  19 20 21 | 22 23 24     <-- this
     *  25 26 27 | 28 29 30     <-- this
     *  31 32 33 | 34 35 36     <-- this
     **/
    for(iSchemaIndex = 0 ; iSchemaIndex < schema.size() ; iSchemaIndex++){
        for(unsigned int i=jumpTheFirstLine;i<fileInfos[0]->nrows;i++){

            for(jSchemaIndex = 0; jSchemaIndex < schema[iSchemaIndex].size(); jSchemaIndex++){
                currentFileInfo = fileInfos[schema[iSchemaIndex][jSchemaIndex]];
                getline(currentFileInfo->filestream,value);
                iss << value;
                getline(iss,value,' ');// Throw the first ' '
                for(unsigned int j=0;j<currentFileInfo->ncols;j++){
                    getline(iss,value,' ');
                    floatValue = stof(value);
                    //Insert x,y,z coord and uv TexCoord;
                    Vertex v = Vertex(j*currentFileInfo->offset+xSizeSlab*jSchemaIndex,                              //x
                                      floatValue,                                                                   //y (altitude)
                                      i*currentFileInfo->offset+zSizeSlab*iSchemaIndex,                              //z
                                      float(j+jSchemaIndex*xSizeSlab)/float(schema[iSchemaIndex].size()*currentFileInfo->ncols),//u
                                      float(i+iSchemaIndex*zSizeSlab)/float(schema[iSchemaIndex].size()*currentFileInfo->nrows));//v
                    vertices.push_back(v);

                    if(floatValue > maxy) maxy = floatValue;
                    if(floatValue < miny) miny = floatValue;

                    currentIndice = vertices.size()-1;
                    // 3 != cases ( |x| current vertex)

                    /* Case 1
                     *  1    2  3  | 4  5  6
                     *  (7)  8  9  | 10 11 12
                     *  13   14 15 | 16 17 18
                     * --------------------
                     *  19   20 21 | 22 23 24
                     *  25   26 27 | 28 29 30
                     *  31   32 33 | 34 35 36=
                     *
                     * Make this polygone :
                     *       1 -2
                     *       | /
                     *      (7)
                     */

                    //Case 2
                    /*  1  2   3    | 4  5  6
                     *  7  8   9    | 10 11 12
                     *  13 14  15   | 16 17 18
                     * --------------------
                     *  19 20 (21)  | 22 23 24
                     *  25 26  27   | 28 29 30
                     *  31 32  33   | 34 35 36

                     * Make this polygones :
                     *     15        15-16
                     *    / |   and  | /
                     *  20-(21)     (21)
                     */

                    // Case 3
                    /*  1  2  3  | 4  5  6
                     *  7  8  9  | 10 11 12
                     *  13 14 15 | 16 17 (18)
                     * --------------------
                     *  19 20 21 | 22 23 24
                     *  25 26 27 | 28 29 30
                     *  31 32 33 | 34 35 36
                     * Make this polygone :
                     *       12
                     *      / |
                     *    17-(18)
                     */

                    //Insert in the counterclockwise direction

                    //Case 2 and 3     b
                    //               / |
                    //              c -a
                    if(j!=0 || jSchemaIndex!=0)
                    {
                        indices.push_back(currentIndice);
                        indices.push_back(currentIndice-schema[iSchemaIndex].size()*currentFileInfo->ncols);
                        indices.push_back(currentIndice-1);
                        computeNormal(&vertices[currentIndice],
                                      &vertices[currentIndice-schema[iSchemaIndex].size()*currentFileInfo->ncols],
                                      &vertices[currentIndice-1]);

                    }



                    // Case 1 and 2    c- b
                    //                 | /
                    //                 a
                    if(j!=currentFileInfo->ncols-1 || jSchemaIndex != schema[iSchemaIndex].size()-1)
                    {
                        indices.push_back(currentIndice);
                        indices.push_back(currentIndice-schema[iSchemaIndex].size()* currentFileInfo->ncols+1);
                        indices.push_back(currentIndice-schema[iSchemaIndex].size()* currentFileInfo->ncols);
                        computeNormal(&vertices[currentIndice],
                                      &vertices[currentIndice-schema[iSchemaIndex].size()* currentFileInfo->ncols+1],
                                      &vertices[currentIndice-schema[iSchemaIndex].size()* currentFileInfo->ncols]);

                    }

                }
                iss.clear();
            }


        }
        jumpTheFirstLine -=jumpTheFirstLine; // For the first loop we need to avoid the first line that is already read
    }

    vec3 shift_Pos(currentFileInfo->ncols*schema[0].size()/2 * currentFileInfo->offset,
                        (miny+maxy)/2,
                        currentFileInfo->nrows*schema.size()/2 * currentFileInfo->offset);
    for(unsigned int i=0;i<vertices.size();i++){
        vertices[i].Normal = normalize(vertices[i].Normal);
        vertices[i].Position -= shift_Pos;
    }

    return new Mesh(vertices,indices);
}


/*Private */


Mesh *MeshLoader::indexVBO(vector<Vertex> vertices){

    unsigned int i;
    vector<unsigned int> indices;
    vector<Vertex> indexVertices;
    map<Vertex,unsigned int> VertexToOutIndex;


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
    return new Mesh(indexVertices,indices);
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
        cerr << "Error in MNT file header | Expected: " << goal << " Read: " << value << endl;


}

// V1,V2,V3 in counterclockwise direction !

void MeshLoader::computeNormal(Vertex *v1, Vertex *v2, Vertex *v3){
    vec3 v12 = v2->Position - v1->Position;
    vec3 v13 = v3->Position - v1->Position;
    vec3 nf  = normalize(cross(v13,v12));
    v1->Normal+=nf;
    v2->Normal+=nf;
    v3->Normal+=nf;
}


//TODO remonter l'erreur pour l'afficher en graphique
vector<MeshLoader::FileInfo*> MeshLoader::getFileInfosFromFiles(const vector<string> &filepaths){
    vector<FileInfo*> fileInfos;


    for(unsigned int i=0; i<filepaths.size();i++){
        FileInfo *f = new FileInfo();

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
        }
    }
    return fileInfos;
}


void MeshLoader::readHeader(MeshLoader::FileInfo *fileInfo)
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
vector<vector<unsigned int>> MeshLoader::setupSchema(const vector<FileInfo*> &fileInfos){
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

