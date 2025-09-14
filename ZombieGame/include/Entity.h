#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
public:
	Entity() {};//used by inherited classes
	
	sf::Sprite& getentity();

	void setpos(float x, float y);
	float getposx();
	float getposy();

	void setspeed(float x);
	float getspeed();


protected:
	sf::Sprite spriteentity;   // Sprite for the entity
	sf::Texture textureentity;
	

	float speed = 151.3f;

};

#endif
