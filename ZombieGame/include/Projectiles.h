#ifndef PROJECTILES_H
#define PROJECTILES_H
#include <SFML/Graphics.hpp>
#include "Player.h"	

class Bullet {

private:
	sf::CircleShape bullet;
	bool active = 1; //check if bullet active or inactive

public:
	sf::CircleShape& getbullet();
	void setactivity();
	Bullet();


};

class Projectile
{
public:
	Projectile();

	void shoot(Player player, sf::RenderWindow& window, sf::View view);//method used to generate bullets and then shoot them in a desired direction

	std::vector<Bullet>& getbullets();
	std::vector<float>& getangle(); //angle of each bullet's direction relative to OX
	
	void setbullets();
	int getcurrentbullets();
	float getspeed();
	void deallocatebullets(sf::View view);//bullets out of view
private:
	std::vector<Bullet> bullets;
	std::vector<float> angles;
	float speed = 0.5f;

	

};
static int maxbullets = 18;
static int currentbullets = 18;



#endif