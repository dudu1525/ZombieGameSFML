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
#include <fstream>
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
	

	sf::Clock localPassedTime;

private:
	WorldMap map;  //map used for the game
	sf::View gameview;

	Player player;
	Projectile proj;	
	Sword sword;

	int currentZombies=30;
	std::vector<Zombie> zombies;

	float accumulatedRespawnTime = 0.0f;
	              //local time+serialized time=total in-game time
	float serializedPassedTime;
	


	void moveplayerinput(sf::Time deltaTime);
	void handlemapedges();
	void handleplayeredges();
	void handleobjects(sf::Vector2f& direction);

	void positionzombies();
	void clearzombies();
	void deallocateDeadZombies();
	void makeMoreZombies();
	void updateplayerhealth();


	


	public:
	
		static MainGame* deserializeData(Game* game, std::string dataFile)//static cuz you dont need an object to call it
	{

		printf("deserialized called");
		MainGame* mg=new MainGame(game); //see if player is loaded good

		std::ifstream data(dataFile, std::ios::binary);
		if (!data.is_open())
		{
			printf("couldnt open file! ");
			return nullptr;
		}
		data.read(reinterpret_cast<char*>(&mg->serializedPassedTime), sizeof(mg->serializedPassedTime));



		std::cout << "data deserialied succesfully" << std::endl;
		return mg;
	}
	
};
static sf::View uiview;
static UIMainGame   e(uiview);
static bool frompause = 0;



#endif
