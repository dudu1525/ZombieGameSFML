#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include "Player.h"
#include "UiMainGame.h"

#define WIDTH 150
#define HEIGHT 100

class Zombie :public Entity
{

public:
	Zombie();
	void zombieanimations(float deltatime, int angle);
	void drawzombiehp(sf::RenderWindow& window);
	sf::FloatRect zombiecollision;//used to detect the player's hitbox
	sf::FloatRect zombieAttackCollision; //used as the 'range' of the attack


	void checkforplayer(int tiles[HEIGHT][WIDTH]);
	float getPlayerZombieAngle(Player& player);
	void attackPlayer(Player& player,  UIMainGame&   e);
	void movez(Player& player);

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
	struct move {
		int x;
		int y;
	}move;


	const sf::Time time = sf::seconds(1.0f / 60.0f);
	

	sf::RectangleShape healthbehind;
	sf::RectangleShape healthtop;
	sf::Vector2f direction;//direction between zombie and player
	
	
	void zombieidle(float deltatime);
	void zombieattacking(float deltatime,int angle);
	void zombiemovementanimations(float deltatime, int angle);
	float currenttime = 0.0f;  //previously static member
	float attackcurrenttime = 0.0f;
	float accumulatedtime = 0.0f; //total time
};


#endif