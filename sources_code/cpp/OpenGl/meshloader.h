/**
* @file meshloader.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/

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
 * @brief A class for loading a mesh from DEM and OBJ.
 */
class MeshLoader
{
public:
    /**
     * @brief Empty Constructor of MeshLoader
     */
    MeshLoader();

    /**
     * @brief Load and index a unique OBJ from a file
     * @param path : the path of the OBJ
     * @return a indexed Mesh pointer
     */
    static std::shared_ptr<Mesh> vertexFromObj(const std::string &path);
    /**
     * @brief Load and index a single mesh pointer from a heightMap texture
     * @param data : the data of the heightMap
     * @param widht : width of the heightMap
     * @param height : height of the heightMap
     * @param offset : the step between two value in the heightMap.
     * @return a indexed Mesh pointer
     */
    static std::shared_ptr<Mesh> vertexFromHeightMap(std::vector<float> data, int width, int height, float offset);


    /**
     * @brief Load texture from a set of DEM file.
     * @param filepaths : a set of path of DEM file, the form described for all DEM files must be continuous and form a square or a rectangle.
     * @return a heightMap texture.
     */
    static std::shared_ptr<LoadTexture> textureFromDEM(const std::vector<std::string> &filepaths);

private:
    /**
     * @brief A basic struct to store the header information in a header of a DEM file
     */
    struct FileInfo{
            /** Reading head*/
            std::ifstream filestream;
            /** Number of columns*/
            unsigned int ncols;
             /** Number of lines*/
            unsigned int nrows;
            /** Position Weast-East of the upper right corner*/
            float xllcorner;
            /** Position North-South of upper right corner*/
            float yllcorner;
            /** Distance (in meter) between 2 differentes altitudes*/
            float offset;
            /** The null value of the file*/
            float noDataValue;
        };


    /**
     * @brief Index a set of vertex for optimise the memory
     * @param vertices : A set of vertex
     * @return a indexed Mesh pointer
     */
    static std::shared_ptr<Mesh> indexVBO(std::vector<Vertex> vertices);
    /**
     * @brief Find a similar vertex of v already read and store his index in result.
     * @param v the vertex to find
     * @param VertexToOutIndex a map with the set og vertex already read
     * @param result the index of the similar vertex found , -1 if no similar vertex was found
     * @return true if a similar vertex was found , false otherwise
     */
    static bool getSimilarVertexIndex(Vertex &v,std::map<Vertex,unsigned int> &VertexToOutIndex, unsigned int &result);
    /**
     * @brief Compare value and goal and return a error if they are different
     * @param value input read
     * @param goal  input expected
     */
    static void checkHeader(std::string value, std::string goal);
    /**
     * @brief Compute the normal of the polygone (v1,v2,v3) and sum with the normal of each vertex
     * The vertexs are in counterclockwise direction
     * @param v1 A Vertex pointer
     * @param v2 A Vertex pointer
     * @param v3 A Vertex pointer
     */
    static void computeNormal(Vertex *v1, Vertex *v2, Vertex *v3);

    /**
     * @brief open, read and store the information of each header of DEM files store in filepaths
     * @param filepaths a set of DEM files
     * @return A set of FileInfo , one for each file in filepaths
     */
    static std::vector<std::shared_ptr<FileInfo>> getFileInfosFromFiles(const std::vector<std::string> &filepaths);
    /**
     * @brief Read a DEM header and store the information in fileInfo
     * @param fileInfo : Where the information will be stored.
     */
    static void readHeader(std::shared_ptr<FileInfo> FileInfo);
    /**
     * @brief From this : (0,1,2,3,4,5)(indice of fileInfos) and each upper corner position ; build a 2D vector with indice of fileInfos
     *  1 | 5 |
     * --------
     *  0 | 2 |
     * --------
     *  3 | 4 |
     * @param fileInfos a set of FIleInfo
     * @return a schema with index of fileInfos in the cellules
     */
    static std::vector<std::vector<unsigned int>> setupSchema(const std::vector<std::shared_ptr<FileInfo>> &fileInfos);

    /**
     * @brief Compute the center and the radius of the mesh m
     * @param m : a Mesh pointer
     */
    static void computeCenterAndRadius(std::shared_ptr<Mesh> m);


};

#endif // MESHLOADER_H
