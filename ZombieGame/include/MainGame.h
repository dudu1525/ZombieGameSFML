#ifndef MAINGAME_H
#define MAINGAME_H
#include <iostream>

#include "States.h"
#include "Zombie.h"
#include "WorldMap.h"
#include "Player.h"
#include "TextureManager.h"
#include "UiMainGame.h"
#include "Projectiles.h"
#include "Constants.h"
#include <vector>
#include <fstream>
//view reseted, zoomed 0.3, not in the upper part of the desktop
class MainGame:public States {

	~MainGame();
public:
	MainGame(Game* game);
	//inherited from state machine
	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInputs();
	virtual void handleResizing(sf::Event& event);
	virtual void handleEvents(sf::Event& event);
	
	void setfrompause();



	//load player and game data
	void loadPlayer();
	void serializeData(); 
	sf::Clock localPassedTime;

private:
	WorldMap map;  
	sf::View gameview;
	Player player;
	Projectile proj;	
	Sword sword;

	int currentZombies=30;//zombies that are in real time on the map
	int maxCurrentZombies=30;//total zombies that should be on the map
	std::vector<Zombie> zombies; 

	float accumulatedRespawnTime = 0.0f; //local time+serialized time=total in-game time
	float serializedPassedTime;
	


	void moveplayerinput(sf::Time deltaTime);
	void handlemapedges();
	void handleplayeredges();
	void handleobjects(sf::Vector2f& direction);

	void positionzombies();
	void clearzombies();
	void deallocateDeadZombies();
	void makeMoreZombies();
	void updateplayerhealth(sf::Time timePerFrame);
	void positionZombieOnMap(Zombie& zombie);


	TextureManager tm;
	


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
		data.read(reinterpret_cast<char*>(&mg->currentZombies), sizeof(mg->currentZombies));
		mg->zombies.resize(mg->currentZombies);
		for (int i = 0; i < mg->currentZombies; i++)
		{
			mg->zombies[i].deserializeZombieData(data);
		}
		//update tiles? or updated inside update func
		//deserialize maxcurrentzombies also
		std::cout << "data deserialied succesfully" << std::endl;
		return mg;
	}
	
};
static sf::View uiview;
static UIMainGame   e(uiview);
static bool frompause = 0;



#endif


//now to do respawning and creating more zombies!