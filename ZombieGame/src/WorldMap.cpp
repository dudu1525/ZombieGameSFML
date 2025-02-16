#include "../include/WorldMap.h"

sf::Sprite& WorldMap::getmap()
{
    return spritemap;
}

void WorldMap::givepath(std::string file)
{
    texturemap.loadFromFile(file);
    spritemap.setTexture(texturemap);

}






//all I need to generate the map is to define the level vector accordingly so poppulate the matrix
//I need to set the view somehow to be centered
//I need to minify the map, with the middle mouse;

void WorldMap::draw(sf::RenderTarget& target, sf::RenderStates states) const //needed because it inherits it
{
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset; //<contains texture

    // draw the vertex array
    target.draw(m_vertices, states); //<vertex array+texture
}

void WorldMap::matrixbuilder()
{
    sf::Image mapImage = texturemap.copyToImage();
    const int tileSize = 32;
    const int tilesX = 150;  
    const int tilesY = 100;

    //std::vector<std::vector<int>> tileMatrix(tilesY, std::vector<int>(tilesX, 0));
    
    //find a good color for each and do that, get the pixels for the tree, the rocks that have in common and youre set
    sf::Color rockColor(100, 100, 92);//fimnd color in common for 8 parts of rock
    sf::Color treeColor(102, 57, 49);//good for tree

   
    for (int i = 0; i < tilesY; ++i) {
        for (int j = 0; j < tilesX; ++j) {

            int pixelX = j * tileSize + tileSize / 2;
            int pixelY = i * tileSize + tileSize / 2;

            sf::Color pixelColor = mapImage.getPixel(pixelX, pixelY);
            sf::Color pixelColor2 = mapImage.getPixel(pixelX-1, pixelY);

            if (pixelColor == rockColor) {
                tileMatrix[i][j] = 1;  
            }
            else if (pixelColor == treeColor || pixelColor2==treeColor) {
                tileMatrix[i][j] = 2;  // Tree
            }
            else {
                tileMatrix[i][j] = 0;  // Normal tile
            }
        }
    }

    
    //for (int i = 0; i < tilesY; ++i) {
        //for (int j = 0; j < tilesX; ++j) {
         //   if (tileMatrix[i][j] == 2)
       //         std::cout << i << " " << j << std::endl;
     //   }
   // }


}





