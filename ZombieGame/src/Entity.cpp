#include "../include/Entity.h"


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


