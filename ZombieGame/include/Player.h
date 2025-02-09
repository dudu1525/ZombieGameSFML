#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player:public Entity
{public:

	Player(std::string imagepath);
	void setcharacter(sf::Vector2f dir,float deltaTime);
	void setxidle(int x);
	void setyidle(int y);
	int getxidle();
	int getyidle();
private:
	void updateentity(sf::Vector2f dir,float deltaTime);
	int xidle;
	 int yidle;

	 int xwalk=0, ywalk=0;
};

#endif