#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <memory>

#include "mesh.h"
#include "loadtexture.h"

/**
 * @brief A class for loading a mesh from differentes files type.
 */
class MeshLoader
{
public:
    /**
     * @brief Empty Constructor of MeshLoader
     */
    MeshLoader();

    /**
     * @brief Load and index a cube from a hard code tab (without normal)
     * @return a indexed Mesh pointer
     */
    std::shared_ptr<Mesh> cubeFromHardCode();

    std::shared_ptr<Mesh> axisFromHardCode();

    /**
     * @brief Load and index a plane from a hard code tab
     * @return a indexed Mesh pointer
     */
    std::shared_ptr<Mesh> planeFromHardCode();


    /**
     * @brief Load and index a unique OBJ from a file
     * @param path : the path of the OBJ
     * @return a indexed Mesh pointer
     */
    std::shared_ptr<Mesh> vertexFromObj(const std::string &path);
    /**
     * @brief Load and index a single mesh pointer from a set of MNT file
     * @param filepaths : a set of path of MNT file, the form described for all MNT files must be continuous and form a square or a rectangle.
     * @return a indexed Mesh pointer
     */
    std::shared_ptr<Mesh> vertexFromMNT(const std::vector<std::string> &filepaths);


 //   Texture* textureFromMNT(const std::vector<std::string> &filepaths,std::string name);



    std::shared_ptr<Mesh> vertexFromHeightMap(std::vector<float> data, int width, int height,float offset);



    std::shared_ptr<LoadTexture> textureFromMNT(const std::vector<std::string> &filepaths);
private:
    /**
     * @brief A basic struct to store the header information in a header of a MNT file
     */
    struct FileInfo{
            std::ifstream filestream; /*!< Reading head*/
            unsigned int ncols;       /*!< Number of columns*/
            unsigned int nrows;       /*!< Number of lines*/
            float xllcorner;          /*!< Position Weast-East of the upper right corner*/
            float yllcorner;          /*!< Position North-South of upper right corner*/
            float offset;             /*!< Distance (in meter) between 2 differentes altitudes*/
            float noDataValue;        /*!< The null value of the file*/
        };


    /**
     * @brief Index a set of vertex for optimise the memory
     * @param vertices : A set of vertex
     * @return a indexed Mesh pointer
     */
    std::shared_ptr<Mesh> indexVBO(std::vector<Vertex> vertices);
    /**
     * @brief Find a similar vertex of v already read and store his index in result.
     * @param v the vertex to find
     * @param VertexToOutIndex a map with the set og vertex already read
     * @param result the index of the similar vertex found , -1 if no similar vertex was found
     * @return true if a similar vertex was found , false otherwise
     */
    bool getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result);
    /**
     * @brief Compare value and goal and return a error if they are different
     * @param value input read
     * @param goal  input expected
     */
    void checkHeader(std::string value, std::string goal);
    /**
     * @brief Compute the normal of the polygone (v1,v2,v3) and sum with the normal of each vertex
     * The vertexs are in counterclockwise direction
     * @param v1 A Vertex pointer
     * @param v2 A Vertex pointer
     * @param v3 A Vertex pointer
     */
    void computeNormal(Vertex *v1, Vertex *v2, Vertex *v3);

    /**
     * @brief open, read and store the information of each header of MNT files store in filepaths
     * @param filepaths a set of MNT files
     * @return A set of FileInfo , one for each file in filepaths
     */
    std::vector<std::shared_ptr<FileInfo>> getFileInfosFromFiles(const std::vector<std::string> &filepaths);
    /**
     * @brief Read a MNT header and store the information in fileInfo
     * @param fileInfo : Where the information will be stored.
     */
    void readHeader(std::shared_ptr<FileInfo> FileInfo);
    /**
     * @brief From this : (0,1,2,3,4,5)(indice of fileInfos) and each upper corner position ; build a 2D vector with indice of fileInfos
     *  NW | N | NE
     * ------------
     *  W  | C | E
     * ------------
     *  SW | S  SE
     * @param fileInfos a set of FIleInfo
     * @return a schema with index of fileInfos in the cellules
     */
    std::vector<std::vector<unsigned int>> setupSchema(const std::vector<std::shared_ptr<FileInfo>> &fileInfos);

    /**
     * @brief Compute the center and the radius of the mesh m
     * @param m : a Mesh pointer
     */
    void computeCenterAndRadius(std::shared_ptr<Mesh> m);


};

#endif // MESHLOADER_H