#ifndef PROJECTILES_H
#define PROJECTILES_H
#include <SFML/Graphics.hpp>
#include "Player.h"	
#include "Zombie.h"
class Bullet {

private:
	sf::CircleShape bullet;
	bool active = 1; //check if bullet active or inactive

public:
	sf::CircleShape& getbullet();
	void setactivity();
	Bullet();


};

class Sword {

public:
	float getangle();
	int calculateangle(Player player, sf::RenderWindow& window, sf::View view);
	void swordHitZombies(std::vector<Zombie>& zombie);

	bool& getactivesword();
	void setposition(Player player);
	sf::Sprite& getfrect();

private:
	sf::FloatRect swordhitbox; //will used to set as damage //used with intersects
	sf::Sprite hitbox;//sprite to draw the sword
	sf::Vector2f offset;
	int  angle;  //1up, 2right, 0down, 3 left
	bool fadingIn;
	float alphaValue;

	sf::Texture text;

	bool isactive;

};

class Projectile
{
public:
	Projectile();

	void shoot(Player& player, sf::RenderWindow& window, sf::View view);//method used to generate bullets and then shoot them in a desired direction

	std::vector<Bullet>& getbullets();
	std::vector<float>& getangle(); //angle of each bullet's direction relative to OX
	
	void setbullets();
	int getcurrentbullets();
	float getspeed();
	void deallocatebullets(sf::View view);//bullets out of view
	void checkforcollisions(int map[100][150], sf::RenderWindow& window);
	void collisionWithZombies(int map[100][150], sf::RenderWindow& window, std::vector<Zombie>& zombie, int nrzombies);
	
private:
	std::vector<Bullet> bullets;
	std::vector<float> angles;
	float speed = 0.5f;

	

};
static int maxbullets = 18;
static int currentbullets = 18;


#endif