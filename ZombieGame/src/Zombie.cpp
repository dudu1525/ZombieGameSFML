#include "../include/Zombie.h"

Zombie::Zombie()
{

	this->speed = 160;
	this->textureentity.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Idle.png");
	healthbehind.setFillColor(sf::Color::Black);
	healthtop.setFillColor(sf::Color::Green);

	healthbehind.setSize(sf::Vector2f(20,3));
	healthtop.setSize(sf::Vector2f(20, 3));


}

void Zombie::zombieidle(float deltatime)
{
	static float currenttime = 0.0f;
	 float totaltime = 0.25f;
	
	
	 
	 currenttime += deltatime;
	 if (currenttime >= totaltime)
	 {
		 currenttime = 0.0f;
		 spriteentity.setTexture(textureentity);
		 spriteentity.setTextureRect(sf::IntRect(idle.x*32,idle.y*32,32,32));

		 idle.x = (idle.x + 1) % 5;
	 }
}

void Zombie::zombieanimations(float deltatime)
{
	if (!ismoving)
	{
		zombieidle(deltatime);
	}
	else
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


