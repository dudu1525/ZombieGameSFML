#include "../include/Zombie.h"
#include <queue>
#define PI 3.14159265
Zombie::Zombie()
{

	this->speed = 160;
	this->textureentity.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Idle.png");
		
	this->attacktexture.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Attack.png");
	this->movetexture.loadFromFile("assets/images/Apocalypse Character Pack/Zombie/Walk.png");
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
{//initially 0.2,  1.0
	float totaltime = 0.1f; 
	accumulatedtime += deltatime; 
	attackcurrenttime += deltatime;
	if (attackcurrenttime >= totaltime)
	{
		attackcurrenttime = 0.0f;
		spriteentity.setTexture(attacktexture); 
		spriteentity.setTextureRect(sf::IntRect(attack.x * 32, angle * 32, 32, 32));
		attack.x = (attack.x + 1) % 5; 
	}
	if (accumulatedtime >= 0.50f) 
	{
		accumulatedtime = 0.0f;
		isattacking = false;
	}
}

void Zombie::zombiemovementanimations(float deltatime, int angle)
{
	float totaltime = 0.15f;

	currenttime += deltatime;
	if (currenttime >= totaltime)
	{
		currenttime = 0.0f;
		spriteentity.setTexture(movetexture);
		spriteentity.setTextureRect(sf::IntRect(move.x * 32,angle* 32, 32, 32));
		move.x = (move.x + 1) % 10;

	}



}
void Zombie::zombieanimations(float deltatime,int angle)
{
	

	

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

		zombiemovementanimations(deltatime, angle);

	}
}

void Zombie::drawzombiehp(sf::RenderWindow& window)
{
	healthbehind.setPosition(this->getposx() + 6, this->getposy());
	healthtop.setPosition(this->getposx() + 6, this->getposy());
	

	window.draw(healthbehind);
	window.draw(healthtop);

	//sf::RectangleShape zAtkRect;
	//zAtkRect.setPosition(zombieAttackCollision.left, zombieAttackCollision.top);
	//zAtkRect.setSize({ zombieAttackCollision.width, zombieAttackCollision.height });
	//zAtkRect.setFillColor(sf::Color::Transparent);
	//zAtkRect.setOutlineColor(sf::Color::Red);
	//zAtkRect.setOutlineThickness(2.f);
	//window.draw(zAtkRect);

	
	
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
		
	//make the matrixes: tilemap, visited boolean, parent: vector2i
		//make the bfs and construct the parent matrix, 
		//after having the parents matrix, get the middle of the tiles and make the zombie go to each middle of tile and just keep updating 
		
		
		float vectnorm = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
		sf::Vector2f normdir(this->direction.x / vectnorm, this->direction.y / vectnorm); //get direction between zombie and player, but 'normalized'= unit step

		if (isattacking == true)
		{
			normdir = sf::Vector2f(0, 0);

		}

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


void Zombie::attackPlayer(Player& player, UIMainGame& e)
{
	sf::FloatRect playerBounds = player.getentity().getGlobalBounds();
	sf::FloatRect zombiebounds = this->getentity().getGlobalBounds();

	this->zombiecollision = zombiebounds;
	//this->zombiecollision.left += 2;
	//this->zombiecollision.top += 2;
	//this->zombiecollision.width -= 4;
	//this->zombiecollision.height -=4;

	this->zombieAttackCollision = zombiebounds;
	this->zombieAttackCollision.left -= 65; //20  40
	this->zombieAttackCollision.top -= 65;
	this->zombieAttackCollision.width += 130;
	this->zombieAttackCollision.height += 130;

	sf::FloatRect adjustedBounds = playerBounds;
	adjustedBounds.left += 20;
	adjustedBounds.top += 15;
	adjustedBounds.width -= (20);
	adjustedBounds.height -= 15;

	float hittime = 0.4f;
	bool inCloseRange = this->zombiecollision.intersects(adjustedBounds);
	bool inAttackRange = this->zombieAttackCollision.intersects(adjustedBounds);

	if (inCloseRange)//register as player is in the range
	{
		this->isattacking = true; 
		accumulatedtime = 0.0f;
	}

	if (this->isattacking) //if is attacking, check in the bigger range
	{
		this->damageTime += this->time.asSeconds();
		if (inAttackRange && this->damageTime >= hittime)
		{
			this->damageTime = 0.0f;
			player.updatehealthvalue(10, this->time.asSeconds(), true);
			e.changehealth(player.health, 100);
		}
		if (accumulatedtime >= 0.50f)
		{
			this->isattacking = false;
			this->damageTime = 0.0f;
			player.updatehealthvalue(10, this->time.asSeconds(), false); // Consider when this should happen
		}
	}
	else
	{
		this->damageTime = 0.0f; 
		player.updatehealthvalue(10, this->time.asSeconds(), false);
	}

	float degrees = getPlayerZombieAngle(player);
	int angle = 0;
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