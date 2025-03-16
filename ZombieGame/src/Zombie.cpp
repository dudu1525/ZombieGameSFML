#include "../include/Zombie.h"
#include <queue>
#define PI 3.14159265
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


void Zombie::checkforplayer(int tiles[HEIGHT][WIDTH])
{
	float zombiecx = this->getentity().getGlobalBounds().left + this->getentity().getGlobalBounds().width / 2.0f;
	float zombiecy = this->getentity().getGlobalBounds().top + this->getentity().getGlobalBounds().height / 2.0f;
	
	int tilex = static_cast<int>(zombiecx) / 32;
	int tiley = static_cast<int>(zombiecy) / 32;
	int reached = 0;
	ismoving = 0;

	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			int newx = tilex + i;  
			int newy = tiley + j;  

			
			if (newx >= 0 && newx< WIDTH-4 && newy >= 0 && newy < HEIGHT-4) {
			
				if (tiles[newy][newx] == 4) {

					ismoving = 1;

					
				}
				
			}
			
		}

		if (ismoving)
			break;
	}

}

float Zombie::getPlayerZombieAngle(Player& player)//angle between zombie and player
{
	float angle;
	sf::FloatRect playerBounds = player.getentity().getGlobalBounds();
	sf::FloatRect zombiebounds = this->getentity().getGlobalBounds();
	sf::Vector2f playerPosition = player.getentity().getPosition();
	sf::Vector2f playerCenter = sf::Vector2f(
		playerPosition.x + playerBounds.width / 2,
		playerPosition.y + playerBounds.height / 2
	);

	sf::Vector2f zombieposition = this->getentity().getPosition();
	sf::Vector2f zombiecenter = sf::Vector2f(
		zombieposition.x + zombiebounds.width / 2,
		zombieposition.y + zombiebounds.height / 2
	);

	this->direction=sf::Vector2f(playerCenter.x - zombiecenter.x, playerCenter.y - zombiecenter.y);//direction between zombie and player


	angle = atan2(playerCenter.y - zombiecenter.y, playerCenter.x - zombiecenter.x);
	float degrees = angle * 180 / PI;

	return degrees;
}

void Zombie::movez(Player& player)//WHEN MOVING, its tile needs to be updated. collisions need to be checked, and so on, tielmatrix and player pos must be given
{
	
	if (ismoving==1)
	{
		
	
		this->getPlayerZombieAngle(player);
		
		float vectnorm = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
		sf::Vector2f normdir(this->direction.x / vectnorm, this->direction.y / vectnorm);

		this->getentity().move(normdir * this->speed * time.asSeconds());
		this->setpos(this->getentity().getPosition().x, this->getentity().getPosition().y);

		
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


void Zombie::attackPlayer(Player& player,  UIMainGame&   e)
{
	float angle = 0;
	sf::FloatRect playerBounds = player.getentity().getGlobalBounds();
	sf::FloatRect zombiebounds = this->getentity().getGlobalBounds();

	// printf("%d %d \n", zombie.getposx(), zombie.getposy());

	sf::FloatRect adjustedBounds = playerBounds;
	adjustedBounds.left += 10;
	adjustedBounds.top += 15;
	adjustedBounds.width -= (20);
	adjustedBounds.height -= 15;


	float hittime = 0.8f;

	if (this->zombiecollision.intersects(adjustedBounds))
	{

		this->isattacking = true;
		this->damageTime += this->time.asSeconds();
		if (this->damageTime >= hittime)
		{//add the angle between the center of the zombie and the center of the player and add the angle as a argument for the zombieanimations, maybe call it here
			this->damageTime = 0.0f;
			player.updatehealthvalue(10, this->time.asSeconds(), true);
			e.changehealth(player.health, 100);



		}


	}
	else
	{
		player.updatehealthvalue(10, this->time.asSeconds(), false);

		this->damageTime = 0.0f;
	}




	
	float degrees = getPlayerZombieAngle(player);
	if (degrees <= 45 && degrees > -45)//right
	{
		angle = 2;
	}
	else if (degrees <= -45 && degrees > -135)//up
	{
		angle = 1;

	}
	else if (degrees > 45 && degrees <= 135)//down
	{

		angle = 0;
	}
	else//left
	{

		angle = 3;
	}


	this->zombieanimations(this->time.asSeconds(), angle);



}
