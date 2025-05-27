#include "../include/Zombie.h"
#include <queue>
#include <stdexcept>
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
	float totaltime = 0.15f; 
	accumulatedtime += deltatime; 
	attackcurrenttime += deltatime;
	if (attackcurrenttime >= totaltime)
	{
		attackcurrenttime = 0.0f;
		spriteentity.setTexture(attacktexture); 
		spriteentity.setTextureRect(sf::IntRect(attack.x * 32, angle * 32, 32, 32));
		attack.x = (attack.x + 1) % 5; 
	}
	if (accumulatedtime >= 0.75f) 
	{
		accumulatedtime = 0.0f;
		isattacking = false;
	}
}

void Zombie::zombiemovementanimations(float deltatime, int angle)
{
	float totaltime = 0.15f;
	calcangle = angle;
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


void Zombie::updateZombieHpBar()
{
	int x = health * 20 / MAXHP;
	healthtop.setSize(sf::Vector2f(x, 3));

}

void Zombie::takeDamage(int amount)
{
	health = health - amount;
	if (health <= 0)
	{
		healthbehind.setSize(sf::Vector2f(0, 0));
		healthtop.setSize(sf::Vector2f(0, 0));


	}
	else
	{
		updateZombieHpBar();

	}
}

void Zombie::checkforplayer(int tiles[HEIGHT][WIDTH])
{
	float zombiecx = this->getentity().getGlobalBounds().left + this->getentity().getGlobalBounds().width / 2.0f;
	float zombiecy = this->getentity().getGlobalBounds().top + this->getentity().getGlobalBounds().height / 2.0f;
	
	int tilex = static_cast<int>(zombiecx) / 32;
	int tiley = static_cast<int>(zombiecy) / 32;
	int reached = 0;
	ismoving = 0;
	followingPath = false;
	for (int i = -5; i <= 5; i++) { //-3, 3
		for (int j = -5; j <= 5; j++) {
			int newx = tilex + i;  
			int newy = tiley + j;  

			
			if (newx >= 0 && newx< WIDTH-5 && newy >= 0 && newy < HEIGHT-5) {
			
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
void Zombie::bfs(int tiles[HEIGHT][WIDTH])//compute x's and y's as usual, but do [y][x] in the matrices [height][width]
{		
	std::queue<sf::Vector2i> q;
	

	for (int i=0;i<HEIGHT;i++)
		for (int j = 0; j < WIDTH; j++)
		{
			parent[i][j] = sf::Vector2i(0, 0);
			visited[i][j] = false;
		}
	int times = 0;
	int vx[4] = { 0,0,1,-1 };
	int vy[4] = { 1,-1,0,0 };
	//int vx[8] = { 0, 0, 1, -1,  1, -1,  1, -1 };
	//int vy[8] = { 1, -1, 0,  0,  1, -1, -1,  1 };
	visited[ztile.y][ztile.x] = true;
	parent[ztile.y][ztile.x] = sf::Vector2i(-1, -1);//marks the start
	q.push( sf::Vector2i(ztile.x, ztile.y) );
	while (!q.empty())
	{
		times++;
		sf::Vector2i current = q.front();
		q.pop();

		for (int i = 0; i <= 3; i++)//traverse its up,down,left,right neighbours, enqueue them if not visited and not an obstacle
		{
			int newY = current.y + vy[i];
			int newX = current.x + vx[i];

			if (newY >= 0 && newY < HEIGHT && newX >= 0 && newX < WIDTH)
			if (visited[current.y + vy[i]][current.x + vx[i]] == false && tiles[current.y + vy[i]][current.x + vx[i]] != 2 )
			{
				visited[current.y + vy[i]][current.x + vx[i]] = true;
				parent[current.y + vy[i]][current.x + vx[i]] = sf::Vector2i(current.x,current.y);
				q.push(sf::Vector2i(current.x + vx[i], current.y + vy[i]));
				if (current.y + vy[i] == ptile.y && current.x + vx[i] == ptile.x)//if player was found
				{	

					return;
				}
			}

		}
		//if (times == 50)
		//	break;

	//	q.pop();
	}


}
void Zombie::reconstructPath()
{
	path.clear();
	currentPathIndex = 0;
	followingPath = true;

	sf::Vector2i current = sf::Vector2i(ptile.x, ptile.y);

	while (parent[current.y][current.x] != sf::Vector2i(-1, -1))
	{
		path.push_back(sf::Vector2f(current.x, current.y)); // TILE coords
		current = parent[current.y][current.x];
	}

	std::reverse(path.begin(), path.end());

	
}

void Zombie::followPath(sf::Time deltaTime)
{
	if (!followingPath)
	{
		

		return;
	}
	if (currentPathIndex >= path.size())
		return;

	
	sf::Vector2f targetTile = path[currentPathIndex];
	sf::Vector2f targetPos = sf::Vector2f(targetTile.x * 32, targetTile.y * 32 ); 
	sf::Vector2f currentPos = this->getentity().getPosition();

	if (calcangle == 2)
	{
		targetPos = sf::Vector2f(targetTile.x * 33, targetTile.y * 32);
	}
	sf::Vector2f adirection = targetPos - currentPos;
	float distance = std::sqrt(adirection.x * adirection.x + adirection.y * adirection.y);
	
	if (distance < 1.0f)
	{	
		
		float vectnorm = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
		sf::Vector2f normdir(this->direction.x / vectnorm, this->direction.y / vectnorm); //get direction between zombie and player, but 'normalized'= unit step

		if (isattacking == true)
		{
			normdir = sf::Vector2f(0, 0);
			

		}

		this->getentity().move(normdir * this->speed * time.asSeconds());
		if (this->getentity().getPosition().x > 5000 || this->getentity().getPosition().y > 3500 || this->getentity().getPosition().x <= 0 || this->getentity().getPosition().y <= 0
			|| std::isnan(this->getentity().getPosition().x) || std::isinf(this->getentity().getPosition().x) || std::isnan(this->getentity().getPosition().y) || std::isinf(this->getentity().getPosition().y))
		{
			printf("in first pos, caused");
			throw std::runtime_error("Something went wrong!");
		}
		this->setpos(this->getentity().getPosition().x, this->getentity().getPosition().y);
	}
	sf::Vector2f normalized;
	if (distance > 0.00001f)
		normalized = adirection / distance;
	else
		normalized = adirection;
	float moveStep = speed * deltaTime.asSeconds();

	if (distance < moveStep)
		moveStep = distance;

	this->getentity().move(normalized * moveStep);
	if (this->getentity().getPosition().x > 5000 || this->getentity().getPosition().y > 3500 || this->getentity().getPosition().x < 0 || this->getentity().getPosition().y < 0
		|| std::isnan(this->getentity().getPosition().x) || std::isinf(this->getentity().getPosition().x) || std::isnan(this->getentity().getPosition().y) || std::isinf(this->getentity().getPosition().y))
	{
		printf("in second pos, caused");
		throw std::runtime_error("Something went wrong!");
	}
	this->setpos(this->getentity().getPosition().x, this->getentity().getPosition().y);
}

void Zombie::updateZombieTiles(int tiles[HEIGHT][WIDTH])
{
	int newtilex = static_cast<int> (this->getentity().getGlobalBounds().left + this->getentity().getGlobalBounds().width / 2.0f) / 32;
	int newtiley = static_cast<int>(this->getentity().getGlobalBounds().top + this->getentity().getGlobalBounds().height / 2.0f) / 32;
	//printf("globalbounds: %d %d ", this->getentity().getGlobalBounds().left, this->getentity().getGlobalBounds().top);
	if (ztile.x != newtilex || newtiley != ztile.y)
	{
		tiles[ztile.y][ztile.x] = 0;
		//printf(" tiles: %d %d ", newtilex, newtiley);
		tiles[newtiley][newtilex] = 3;

	}
	
}

int Zombie::getHealth()
{
	return this->health;
}


void Zombie::movez(Player& player, int tiles[HEIGHT][WIDTH])//WHEN MOVING, its tile needs to be updated. collisions need to be checked, and so on, tielmatrix and player pos must be given
{
	
	if (ismoving==1)
	{
		
	//make the matrixes: tilemap, visited boolean, parent: vector2i
		//make the bfs and construct the parent matrix, 
		//after having the parents matrix, get the middle of the tiles and make the zombie go to each middle of tile and just keep updating 


		ztile.x= static_cast<int> (this->getentity().getGlobalBounds().left + this->getentity().getGlobalBounds().width / 2.0f)/32;
		ztile.y= static_cast<int>(this->getentity().getGlobalBounds().top + this->getentity().getGlobalBounds().height / 2.0f)/32;
		ptile.x = static_cast<int> (player.getentity().getGlobalBounds().left + player.getentity().getGlobalBounds().width / 2.0f)/32;
		ptile.y= static_cast<int> (player.getentity().getGlobalBounds().top + player.getentity().getGlobalBounds().height / 2.0f)/32;
		
		bfs(tiles);
		reconstructPath();
		//move player
		

		/////////////////////////////////////////////
		/*float vectnorm = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
		sf::Vector2f normdir(this->direction.x / vectnorm, this->direction.y / vectnorm); //get direction between zombie and player, but 'normalized'= unit step

		if (isattacking == true)
		{
			normdir = sf::Vector2f(0, 0);

		}

		this->getentity().move(normdir * this->speed * time.asSeconds());
		this->setpos(this->getentity().getPosition().x, this->getentity().getPosition().y);*/
		/////////////////////////////////////////////////////////


		
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
	this->zombiecollision.left -= 2;
	this->zombiecollision.top -= 2;
	this->zombiecollision.width += 20;
	this->zombiecollision.height +=20;

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

	float hittime = 0.7f;
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