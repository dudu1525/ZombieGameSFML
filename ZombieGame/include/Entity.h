#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
public:
	Entity();
	Entity(std::string imagepath);
	sf::Sprite& getentity();

	void setpos(float x, float y);

	void setspeed(float x);
	float getspeed();


protected:
	sf::Sprite spriteentity;   // Sprite for the player
	sf::Texture textureentity;

	float speed = 151.3f;

};

#endif
