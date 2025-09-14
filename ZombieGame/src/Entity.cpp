#include "../include/Entity.h"


sf::Sprite& Entity::getentity()
{
	return spriteentity;
}



void Entity::setpos(float x, float y)
{
	spriteentity.setPosition(x, y);
	

}
 
float Entity::getposx()
{
	return this->spriteentity.getPosition().x;
}

float Entity::getposy()
{
	return this->spriteentity.getPosition().y;
}

void Entity::setspeed(float x)
{
	speed = x;
}

float Entity::getspeed()
{
	return speed;
}


