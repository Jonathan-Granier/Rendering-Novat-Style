#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "generatedtexture.h"
#include <vector>
#include <iostream>

class HeightMap : public GeneratedTexture
{
public:
    HeightMap(std::string name, const int &width, const int &height);
    void initialize();
    std::vector<float> generate(int widthViewport, int heightViewport);

};

#endif // HEIGHTMAP_H
