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




	bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



	sf::Sprite spritemap;   // Sprite for the player
	sf::Texture texturemap;



	sf::VertexArray m_vertices;  //vertex array used for generating all the tiles
	sf::Texture m_tileset;//tiles for generation

	
	int v[20] = { 0,0,1,0,1,0,1,0,0,1,0,1,0,1,1,0 };
	int v2[20]= { 0,0,1,0,1,0,1,0,0,1,0,1,0,1,1,0 };
	int size = 16;
	void shiftright(int v[], int size);
	int makedec(int v[], int size);


	float changetostartalive = 0.4f;
	//int starvationlimit=4;
	int overpoplimit=3;
	int birthnumber=4;
	int nrsteps =12;
	void initmap(int map[250][150]);
	int countaliveneighbours(int map[250][150], int x, int y,int height, int width);
	void doSimulationMap(int oldmap[250][150]);
	void generatemap(int map[250][150]);
	int countaliveneighbours2(int map[250][150], int x, int y, int height, int width);
	void initsnow(int map[250][150]);


	std::vector<int> p;
	 double noise(double x, double y);
	 double  fade(double t);
	 double lerp(double t, double a, double b);
	 double grad(int hash, double x, double y);
};






#endif
