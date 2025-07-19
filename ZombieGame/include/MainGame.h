#ifndef MAINGAME_H
#define MAINGAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "States.h"
#include "Zombie.h"
#include "Button.h"
#include "WorldMap.h"
#include "Player.h"
#include "UiMainGame.h"
#include "Projectiles.h"
#include <vector>
//view reseted, zoomed 0.3, not in the upper part of the desktop
class MainGame:public States {

	~MainGame();
public:
	MainGame(Game* game);

	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInput();
	virtual void handleResizing(sf::Event& event);
	virtual void handleInputs(sf::Event& event);
	
	void setfrompause();
	void loadPlayer();

	void serializeData(); //TO BE IMPLEMENTED
	void deserializeData();


private:
	WorldMap map;  //map used for the game
	Player player;
	sf::View gameview;
	Projectile proj;	
	Sword sword;
	int currentZombies=30;
//got the sowrd active from the player, just use it for collision damage
	std::vector<Zombie> zombies;
	//Zombie zombies[30];

	//Zombie zombie1;
	//Zombie zombie2;

	void moveplayerinput(sf::Time deltaTime);
	void handlemapedges();
	void handleplayeredges();
	void handleobjects(sf::Vector2f& direction);
	void zombiecollision(sf::Vector2f& direction); //not for now
	void detectzombie(Zombie& zombie);
	void positionzombies();
	void clearzombies();
	void deallocateDeadZombies();
	void makeMoreZombies();
	float accumulatedRespawnTime = 0.0f;
	sf::Clock accumulatedGameTime;


	void updateplayerhealth();

};
static sf::View uiview;
static UIMainGame   e(uiview);

	static bool frompause = 0;


#endif
