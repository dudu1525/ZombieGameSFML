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
	int getposx();
	int getposy();

	void setspeed(float x);
	float getspeed();


protected:
	sf::Sprite spriteentity;   // Sprite for the player
	sf::Texture textureentity;
	sf::Vector2f location;

	float speed = 151.3f;
	int posx;
	int posy;

};

#endif
