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

    
    //find a good color for each and do that, get the pixels for the tree, the rocks that have in common and youre set
    sf::Color rockColor(126, 123, 116);//fimnd color in common for 8 parts of rock
    sf::Color treeColor(102, 57, 49);//good for tree
    sf::Color watercolor(99, 155, 255);

   
    for (int i = 0; i < tilesY; ++i) {
        for (int j = 0; j < tilesX; ++j) {

            int pixelX = j * tileSize + tileSize / 2;
            int pixelY = i * tileSize + tileSize / 2;
            int pixelx = j * 32;
            int pixely = i * 32;

            sf::Color pixelColor = mapImage.getPixel(pixelX, pixelY);
            sf::Color pixelColor2 = mapImage.getPixel(pixelX-1, pixelY);
            sf::Color pixelColor3 = mapImage.getPixel(pixelx+1,pixely+0);
            sf::Color pixelColor4 = mapImage.getPixel(pixelx+0,pixely+5);
            sf::Color damagecolortest = mapImage.getPixel(pixelx, pixely);

            if (pixelColor == rockColor || rockColor == pixelColor3 || rockColor == pixelColor4) {
                {//also set adjacent, the original i j is the top right
                    tileMatrix[i][j] = 2;  //set to 1
                    tileMatrix[i][j - 1] = 2;
                    tileMatrix[i + 1][j] = 2;
                    tileMatrix[i + 1][j - 1] = 2;
                }
            }
            else if (pixelColor == treeColor || pixelColor2 == treeColor) {
                tileMatrix[i][j] = 2;  // Tree
            }
            else if (damagecolortest == watercolor)
                tileMatrix[i][j] = 1;
            
        }
    }

    
    //for (int i = 0; i < tilesY; ++i) {
        //for (int j = 0; j < tilesX; ++j) {
         //   if (tileMatrix[i][j] == 2)
       //         std::cout << i << " " << j << std::endl;
     //   }
   // }


}





