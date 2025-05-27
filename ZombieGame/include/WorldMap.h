#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
class WorldMap :public sf::Drawable, public sf::Transformable {

public:
	
	sf::Sprite& getmap();
	void givepath(std::string file);
	void matrixbuilder();

	int tileMatrix[100][150] = { 0 }; //0-nothing, 2-obstacle, 3-player, player-4

	//beside when in [y][x] inside the matrix, use as x,y,<normal


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
	


	sf::Sprite spritemap;   
	sf::Texture texturemap;



	sf::VertexArray m_vertices;  //vertex array used for generating all the tiles
	sf::Texture m_tileset;//tiles for generation

	
	


	
};






#endif
