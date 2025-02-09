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
bool WorldMap::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    p = {
         151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
         140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 20, 23, 190, 0, 148,
         247, 120, 234, 75, 6, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
         57, 177, 88, 33, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
         74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
         60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
         65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 195,
         233, 42, 96, 31, 120, 115, 99, 210, 194, 19, 33, 177, 109, 118, 13, 72,
         129, 39, 51, 34, 203, 155, 71, 204, 58, 179, 102, 152, 165, 110, 78, 40,
         238, 187, 19, 167, 185, 18, 138, 10
    };

    // Duplicate the permutation table
    p.resize(512);
    for (int i = 0; i < 256; i++) {
        p[256 + i] = p[i];
    }
    ///////////////////////////////////////////////////////////////for perlin noise^
    
    //initialize the map with the 4 jpg tiles, just set their values as 0,1,2,3,or 4

    int tiles[250][150]; //its iverse, i means the width, j means the height so must reverse these
    initmap(tiles);
    for (int i = 0; i < nrsteps; i++)
        doSimulationMap(tiles);
    overpoplimit = 5;
     birthnumber = 3;
    initsnow(tiles);
  


    //make some for testing
    tiles[90][50] = 3;
    tiles[90][51] = 3;
    tiles[0][0] = 4;
  
    //if cannot load from file
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::Quads); //set quads as the primitive of the vertex array 
    m_vertices.resize(width * height * 4); //set size of *4 because its quads

    //set the position and textures of the vertexes in the vertex array
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int aux = i + j * width; //quads go by this logic

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4]; //current quad from all the 250*150 ones
            //this is the position of the quad
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            //this is the texture, which region of the texture to use from the 32x32 grass
            //numai partea stanga conteaza
            //asta pt level* normal
            quad[0].texCoords= sf::Vector2f(32*tiles[i][j], 0);
            quad[1].texCoords = sf::Vector2f(32 * (tiles[i][j] +1), 0);
            quad[2].texCoords = sf::Vector2f(32 * (tiles[i][j] + 1), 32);
            quad[3].texCoords = sf::Vector2f(32 * tiles[i][j], 32);

            //quad[0].texCoords = sf::Vector2f(64, 0);
           // quad[1].texCoords = sf::Vector2f(96, 0);
           // quad[2].texCoords = sf::Vector2f(96, 32);
           // quad[3].texCoords = sf::Vector2f(64, 32);

        }
    }

    return true;
}

void WorldMap::draw(sf::RenderTarget& target, sf::RenderStates states) const //needed because it inherits it
{
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset; //<contains texture

    // draw the vertex array
    target.draw(m_vertices, states); //<vertex array+texture
}





//for perlin noise

double WorldMap::noise(double x, double y) {
    // Find unit grid cell coordinates containing the point
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;

    // Relative x, y within the unit grid cell
    x -= std::floor(x);
    y -= std::floor(y);

    // Compute fade curves for x, y
    double u = fade(x);
    double v = fade(y);

    // Hash coordinates of the four square corners
    int A = p[X] + Y, AA = p[A], AB = p[A + 1];
    int B = p[X + 1] + Y, BA = p[B], BB = p[B + 1];
    
    // Add blended results from the four corners of the grid cell
    return lerp(v, lerp(u, grad(p[AA], x, y),
        grad(p[BA], x - 1, y)),
        lerp(u, grad(p[AB], x, y - 1),
            grad(p[BB], x - 1, y - 1)));
}
 double  WorldMap::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
 double WorldMap::lerp(double t, double a, double b) {
    return a + t * (b - a);
}
 double WorldMap::grad(int hash, double x, double y) {
    int h = hash & 3; // Take the last 2 bits of the hash
    double u = h < 2 ? x : y; // If h is 0 or 1, use x, otherwise use y
    double v = h < 2 ? y : x; // If h is 0 or 1, use y, otherwise use x
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}







 //down below for generating the values in the tiles matrix

 int WorldMap:: makedec(int v[], int size)
 {
     int nr = 2;
     int finnr = 0;
     if (v[size - 1] == 1)
         finnr = 1;
     else
         finnr = 0;
     for (int i = size - 2; i >= 0; i--)
     {
         if (v[i] % 2 == 1)
             finnr += nr;

         nr = nr * 2;

     }
     return finnr;
 }

 void WorldMap:: shiftright(int v[], int size)
 {
     for (int i = size - 1; i >= 1; i--)
         v[i] = v[i - 1];

 }
 void WorldMap::initmap(int map[250][150])
 {//map j i
     for (int i = 0; i < 150; i++)
         for (int j = 0; j < 250; j++)
         {
             int nr = makedec(v, size);
             //change 40% = >810000
             if (nr > 13700)
                 map[j][i] = 0;
             else
                 map[j][i] = 1;

             v[0] = v[15] ^ v[13] ^ v[12] ^ v[10];
             shiftright(v, size);

         }
 }

 int WorldMap::countaliveneighbours(int map[250][150], int x, int y,int height,int width)
 {
     int count = 0;
     for (int i = -1; i < 2; i++) {
         for (int j = -1; j < 2; j++) {
             int neighbour_x = x + i;
             int neighbour_y = y + j;
             //If we're looking at the middle point 
             if (i == 0 && j == 0) {
                 //Do nothing, we don't want to add ourselves in! 
             }
             //In case the index we're looking at it off the edge of the map 
             else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= height || neighbour_y >= width) {
                 count = count + 1;
             }
             //Otherwise, a normal check of the neighbour 
             else if (map[neighbour_y][neighbour_x]) {
                 count = count + 1;
             }
         }
     }
     return count;
 }

 void WorldMap::doSimulationMap(int oldmap[250][150])
 {
     for (int i = 0; i < 150; i++)
         for (int j = 0; j < 250; j++)
         {
             int count = countaliveneighbours(oldmap, i, j, 150, 250);
             if (oldmap[j][i])
             {
                 if (count < overpoplimit)
                     oldmap[j][i] = 0;
                 else
                     oldmap[j][i] = 1;
             }
             else
             {
                 if (count>birthnumber)
                     oldmap[j][i] = 1;
                 else
                     oldmap[j][i] = 0;

             }

         }

 }

 void WorldMap::generatemap(int map[250][150])
 {
 }

 int WorldMap::countaliveneighbours2(int map[250][150], int x, int y, int height, int width)
 {
     int count = 0;
     for (int i = -1; i < 2; i++) {
         for (int j = -1; j < 2; j++) {
             int neighbour_x = x + i;
             int neighbour_y = y + j;
             //If we're looking at the middle point 
             if (i == 0 && j == 0) {
                 //Do nothing, we don't want to add ourselves in! 
             }
             //In case the index we're looking at it off the edge of the map 
             else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= height || neighbour_y >= width) {
                 count = count + 1;
             }
             //Otherwise, a normal check of the neighbour 
             else if (map[neighbour_y][neighbour_x]==2) {
                 count = count + 1;
             }
         }
     }
     return count;
 }

 void WorldMap::initsnow(int map[250][150])
 {
     int temp_map[250][150];
     for (int i = 0; i < 50; i++)
         for (int j = 0; j < 200; j++)
         {
             int nr = makedec(v2, size);
             
             if (nr > 13700)
                 map[j][i] = 4;
             else
                 map[j][i] = 3;

             v2[0] = v2[15] ^ v2[13] ^ v2[12] ^ v2[10];
             shiftright(v2, size);

         }
     for (int k=0;k<12;k++)
     for (int i = 0; i < 50; i++) {
         for (int j = 0; j < 200; j++) {
             int count = countaliveneighbours2(map, i, j, 50, 200);

             if (map[j][i] == 4) {
                 if (count < overpoplimit)
                     temp_map[j][i] = 2;
                 else
                     temp_map[j][i] = 4;
             }
             else if (map[j][i] == 2) {
                 if (count > birthnumber)
                     temp_map[j][i] = 4;
                 else
                     temp_map[j][i] = 2;
             }
         }
     }  
     for (int i = 0; i < 50; i++)
         for (int j = 0; j < 200; j++)
             map[j][i] = temp_map[j][i];


 }
