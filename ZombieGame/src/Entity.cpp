#include "../include/Entity.h"



Entity::Entity()
{
}

Entity::Entity(std::string imagepath)
{
	textureentity.loadFromFile(imagepath);

	spriteentity.setTexture(textureentity);
	spriteentity.setScale(0.75, 0.75);


}

sf::Sprite& Entity::getentity()
{
	return spriteentity;
}



void Entity::setpos(float x, float y)
{
	spriteentity.setPosition(x, y);
	this->posx = x;
	this->posy = y;

}

int Entity::getposx()
{
	return this->posx;
}

int Entity::getposy()
{
	return this->posy;
}

void Entity::setspeed(float x)
{
	speed = x;
}

float Entity::getspeed()
{
	return speed;
}


