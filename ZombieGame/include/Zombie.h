#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.h"
#include <iostream>
#include "Player.h"
#include "UiMainGame.h"
#include <queue>
#include <fstream>
#include "TextureManager.h"
#include "Constants.h"

class Zombie :public Entity
{

public:
	Zombie();
	Zombie(TextureManager* tm);
	void zombieanimations(float deltatime, int angle);
	void drawzombiehp(sf::RenderWindow& window);
	sf::FloatRect zombiecollision;//used to detect the player's hitbox
	sf::FloatRect zombieAttackCollision; //used as the 'range' of the attack
	sf::Vector2f getZombieCenter();
	void serializeZombieData(std::ofstream& data);
	void deserializeZombieData(std::ifstream& data);

	void updateZombieHpBar();//update ui based on health/maxhealth
	void takeDamage(int amount);//health- call updatezombiehp 
	void checkforplayer(int tiles[HEIGHT][WIDTH]);
	float getPlayerZombieAngle(Player& player);
	void attackPlayer(Player& player,  UIMainGame&   e, sf::Time timeOfFrame);
	void movez(Player& player,int tiles[HEIGHT][WIDTH]);

	


	bool& getisattacking();

	
	float damageTime = 0.0f;
	bool ismoving = false;
private:

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
		int x=0;
		int y=0;
	}move;



	int calcangle=0;

	sf::RectangleShape healthbehind;
	sf::RectangleShape healthtop;
	sf::Vector2f direction;//direction between zombie and player
	
	
	void zombieidle(float deltatime);
	void zombieattacking(float deltatime,int angle);
	void zombiemovementanimations(float deltatime, int angle);
	float currenttime = 0.0f;  //previously static member
	float attackcurrenttime = 0.0f;
	float accumulatedtime = 0.0f; //total time
	//------------------------------------------------------------------------//for zombie bfs
	void bfs(int tiles[HEIGHT][WIDTH]);
	void reconstructPath();

	TextureManager* textmang=nullptr;
public:
	void followPath(sf::Time deltaTime);
	void updateZombieTiles(int tiles[HEIGHT][WIDTH]);
	int getHealth();

	bool takingDamagefromSword=false;
	float invincibilityTime = 0.8f;
	float accumulatedTime = 0.0f;


private:
	struct zombietile {
		int x=0;
		int y=0;
	}ztile;
	

	struct playertile {
		int x=0;
		int y=0;
	}ptile;

	std::vector<sf::Vector2f> path;
	int currentPathIndex = 0;
	bool followingPath = false;
	
	bool visited[HEIGHT][WIDTH] = {0};
	sf::Vector2i parent[HEIGHT][WIDTH];
	sf::Vector2i finalPath[HEIGHT][WIDTH];
	

};


#endif