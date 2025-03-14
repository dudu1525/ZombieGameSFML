#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

#define WIDTH 150
#define HEIGHT 100

class Zombie :public Entity
{

public:
	Zombie();
	void zombieanimations(float deltatime, int angle);
	void drawzombiehp(sf::RenderWindow& window);
	sf::FloatRect zombiecollision;

	void checkforplayer2(int tiles[HEIGHT][WIDTH]);
	void movez();

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


	const sf::Time time = sf::seconds(1.0f / 60.0f);
	

	sf::RectangleShape healthbehind;
	sf::RectangleShape healthtop;
	
	
	void zombieidle(float deltatime);
	void zombieattacking(float deltatime,int angle);
	float currenttime = 0.0f;  //previously static member
	float accumulatedtime = 0.0f; //total time
};


#endif