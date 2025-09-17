#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Constants.h"
#include <iostream>

class Player:public Entity
{public:
		
	//functions related to player movement and idling tiles
	Player(std::string imagepath);
	void setcharacter(sf::Vector2f dir,float deltaTime);

	sf::Vector2f getPlayerCenter();


	//functions related to stamina, health, weapons
	void updatehealthvalue(int damage,float deltaTime,bool isbeingdmg);
	void updatestamina(bool sprint,float deltaTime);

	int getselectedweap();
	void setselectedweap(int id);
	void setshooting(float deltaTime);
	bool& getshooting();
	void sethealth(int health);
	void updateplayertile(int tiles[HEIGHT][WIDTH]);

	void setstabbing(float deltaTime,int position);
	bool& getstabbing();

	bool isPlayerDead();


	//public general information

	int stamina=100;
	int health=100;
	bool moving=false;
	bool isinvincible = false;
	float animationTimer = 0.0f;
	float totaltime = 0.0f;


	

	int yshoot;


	sf::Sprite& getentity2(); //function to display action sprites
	sf::Sprite& getentity3();
	

private:
	void updateentity(sf::Vector2f dir,float deltaTime);
	
	sf::Texture actiontexture;
	sf::Sprite	actionentity;

	sf::Texture basetexture;
	sf::Sprite baseentity;


	int xidle=0,yidle=0; //needed for idle animation
	
	int xwalk = 0; //needed for sprint animation
	int ywalk=0;

	int xshoot; //needed for shooting animation

	int xstab, ystab;

	struct playertile {
		int x;
		int y;
	}playertile;
	

	

};
static int depletionrate=2;
static int selectedweap = 0; //0-no weap, 1-sword, 2-crossbow
static bool isshooting = false;
static bool isstabbing = false;



#endif

//add bullets class?