#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "generatedtexture.h"
#include <vector>
#include <iostream>


/**
* @brief This class is a child of GeneratedTexture. It is used to generate a height map from the genheightmap.frag shader.
* This class have the same use that the GeneratedTexture class.
* Only The RED canal of the texture are write. 
*/
class HeightMap : public GeneratedTexture
{
public:
    /**
    * @brief Constructor that instanciate genheightmap shader.
    *
    * @param name       The name of the texture.
    * @param width      The width of the texture
    * @param height     The height of the texture.
    */
    HeightMap(std::string name, const int &width, const int &height);

    /**
    * @brief Initialize the framebuffer object.
    */
    void initialize();

    /**
    * @brief Generate the texture in the fbo with the genheightmap shader.
    *
    * @param widthViewport      The width of the openGL widget.
    * @param heightViewport     The height of the openGL widget.
    */
    std::vector<float> generate(int widthViewport, int heightViewport);

};

#endif // HEIGHTMAP_H
