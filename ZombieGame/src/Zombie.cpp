#include "../include/Zombie.h"

Zombie::Zombie()
{

	this->speed = 160;
	this->textureentity.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Idle.png");
		
	this->attacktexture.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Attack.png");
	spriteentity.setTexture(textureentity);
	spriteentity.setTextureRect(sf::IntRect(0, 0, 32, 32));

	healthbehind.setFillColor(sf::Color::Black);
	healthtop.setFillColor(sf::Color::Green);

	healthbehind.setSize(sf::Vector2f(20,3));
	healthtop.setSize(sf::Vector2f(20, 3));


}

void Zombie::zombieidle(float deltatime)
{
	float totaltime = 0.25f; 
	currenttime += deltatime; 
	if (currenttime >= totaltime) 
	{
		currenttime = 0.0f; 
		spriteentity.setTexture(textureentity);
		spriteentity.setTextureRect(sf::IntRect(idle.x * 32, idle.y * 32, 32, 32));
		idle.x = (idle.x + 1) % 5; 
	}
}

void Zombie::zombieattacking(float deltatime, int angle)
{
	float totaltime = 0.2f; 
	accumulatedtime += deltatime; 
	currenttime += deltatime;
	if (currenttime >= totaltime) 
	{
		currenttime = 0.0f; 
		spriteentity.setTexture(attacktexture); 
		spriteentity.setTextureRect(sf::IntRect(attack.x * 32, angle * 32, 32, 32));
		attack.x = (attack.x + 1) % 5; 
	}
	if (accumulatedtime >= 1.0f) 
	{
		accumulatedtime = 0.0f;
		isattacking = false;
	}
}


void Zombie::zombieanimations(float deltatime,int angle)
{
	zombiecollision = this->getentity().getGlobalBounds();
	zombiecollision.left -= 3;
	zombiecollision.top -= 3;
	zombiecollision.width += 6;
	zombiecollision.height += 6;
	

	if (!ismoving && !isattacking)
	{
		zombieidle(deltatime);
	}
	else if (isattacking)
	{
		zombieattacking(deltatime,angle);
	}
	else if (ismoving)
	{

	}
}

void Zombie::drawzombiehp(sf::RenderWindow& window)
{
	healthbehind.setPosition(this->getposx() + 6, this->getposy());
	healthtop.setPosition(this->getposx() + 6, this->getposy());
	

	window.draw(healthbehind);
	window.draw(healthtop);
}

bool& Zombie::getisattacking()
{
	return this->isattacking;
}

void Zombie::settextures(sf::Texture& idle, sf::Texture& attack)
{
	this->attacktexture = attack;
	this->idletexture = idle;
}


