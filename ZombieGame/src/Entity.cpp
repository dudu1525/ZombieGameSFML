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

}

void Entity::setspeed(float x)
{
	speed = x;
}

float Entity::getspeed()
{
	return speed;
}


