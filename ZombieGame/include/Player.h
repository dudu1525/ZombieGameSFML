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

	void updatehealthvalue(int damage);
	void updatestamina(bool sprint,float deltaTime);
	int getdepletion();

	int stamina=100;
	int health;
	bool moving;

private:
	void updateentity(sf::Vector2f dir,float deltaTime);
	int xidle;
	 int yidle;
	 
	 
	 

	 int xwalk=0, ywalk=0;
};
static int depletionrate=2;
static int invincibility;
#endif