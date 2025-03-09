#include "../include/Zombie.h"
#include <queue>

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


void Zombie::checkforplayer2(int tiles[HEIGHT][WIDTH])
{
	float zombiecx = this->getentity().getGlobalBounds().left + this->getentity().getGlobalBounds().width / 2.0f;
	float zombiecy = this->getentity().getGlobalBounds().top + this->getentity().getGlobalBounds().height / 2.0f;
	
	int tilex = static_cast<int>(zombiecx) / 32;
	int tiley = static_cast<int>(zombiecy) / 32;
	int reached = 0;

	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			int newx = tilex + i;  
			int newy = tiley + j;  

			
			if (newx >= 0 && newx< HEIGHT && newy >= 0 && newy < WIDTH) {
			
				if (tiles[newy][newx] == 3) {
					reached = 1;
					//do smth here, start following algorithm
					//this->setpos(newx * 32, newy * 32);
				}
			}
			
		}

		if (reached)
			break;
	}

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


