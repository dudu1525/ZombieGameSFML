#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player:public Entity
{public:

	Player(std::string imagepath);
	void setcharacter(sf::Vector2f dir,float deltaTime);
	void setxidle(int x);
	void setyidle(int y);
	int getxidle();
	int getyidle();

	void updatehealthvalue(int damage);
	void updatestamina(bool sprint,float deltaTime);
	int getdepletion();
	int getselectedweap();
	void setselectedweap(int id);
	void setshooting(float deltaTime);
	bool& getshooting();

	int stamina=100;
	int health;
	bool moving;

	int yshoot;

	sf::Sprite& getentity2(); //function to display action sprites
	sf::Sprite& getentity3();
	void setpos2(float x, float y);
	void setpos3(float x, float y);

private:
	void updateentity(sf::Vector2f dir,float deltaTime);
	
	sf::Texture actiontexture;
	sf::Sprite	actionentity;

	sf::Texture basetexture;
	sf::Sprite baseentity;


	int xidle,yidle; //needed for idle animation
	
	int xwalk = 0; //needed for sprint animation
	int ywalk=0;

	int xshoot; //needed for shooting animation

	

};
static int depletionrate=2;
static int invincibility;//for health
static int selectedweap = 0; //0-no weap, 1-sword, 2-crossbow
static bool isshooting = false;



#endif

//add bullets class?