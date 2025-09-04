#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
public:
	Entity() {};//used by inherited classes
	
	sf::Sprite& getentity();

	void setpos(float x, float y);
	int getposx();
	int getposy();

	void setspeed(float x);
	float getspeed();


protected:
	sf::Sprite spriteentity;   // Sprite for the entity
	sf::Texture textureentity;
	

	float speed = 151.3f;
	int posx=0;
	int posy=0;

};

#endif
