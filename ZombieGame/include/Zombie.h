#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

class Zombie :public Entity
{

public:
	Zombie();
	void zombieanimations(float deltatime, int angle);
	void drawzombiehp(sf::RenderWindow& window);
	sf::FloatRect zombiecollision;

	sf::Texture attacktexture;
	sf::Texture idletexture;
	sf::Texture movetexture;
	bool& getisattacking();

	void settextures(sf::Texture& idle, sf::Texture& attack);
	float damageTime = 0.0f;

private:
	bool ismoving = false;
	bool isattacking = false; 
	sf::Texture movetext;
	int health = 100;
	struct idle { //struct for idle part of animation
		int x = 0;
		int y = 0;
	}idle;
	struct attack {
		int x=0;
		int y=0;
	}attack;
	sf::RectangleShape healthbehind;
	sf::RectangleShape healthtop;
	

	void zombieidle(float deltatime);
	void zombieattacking(float deltatime,int angle);
	float currenttime = 0.0f;  //previously static member
	float accumulatedtime = 0.0f; //total time
};


#endif