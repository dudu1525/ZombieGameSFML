#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

class Zombie :public Entity
{

public:
	Zombie();
	void zombieanimations(float deltatime);
	void drawzombiehp(sf::RenderWindow& window);
private:
	bool ismoving = false;
	bool isattacking=false;
	sf::Texture movetext;
	int health = 100;
	struct idle { //struct for idle part of animation
		int x = 0;
		int y = 0;
	}idle;
	sf::RectangleShape healthbehind;
	sf::RectangleShape healthtop;

	void zombieidle(float deltatime);

};


#endif