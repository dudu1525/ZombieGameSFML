#include "../include/Projectiles.h"
#include <iostream>

#define PI 3.14159265

Projectile::Projectile()
{


}

void Projectile::shoot(Player& player, sf::RenderWindow& window, sf::View view)
{
	sf::Time frame = sf::seconds(1.0f / 60.0f);
	float time = frame.asSeconds();

	static float animationTime = 0.0f;
	const float delay = 0.2f;

	animationTime += time;

	if (animationTime >= delay && currentbullets > 0)
	{
	
		currentbullets--;
		animationTime -= delay;
		Bullet	b;
		bullets.push_back(b);
		//bullets.back().setRadius(1.3);
		//bullets.back().setFillColor(sf::Color::Black);
		//bullets.back().setOrigin(0, 0);

		bullets.back().getbullet().setPosition(player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
			player.getentity().getGlobalBounds().height / 2));



		float posmousex = sf::Mouse::getPosition(window).x + view.getCenter().x - view.getSize().x / 2 * 3.333;
		float posmousey = sf::Mouse::getPosition(window).y + view.getCenter().y - view.getSize().y / 2 * 3.333;

		float playerposx = player.getentity().getPosition().x + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
			player.getentity().getGlobalBounds().height / 2).x;
		float playerposy = player.getentity().getPosition().y + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
			player.getentity().getGlobalBounds().height / 2).y;

	

		angles.push_back(atan2(posmousey - playerposy,posmousex - playerposx));
		float degrees = angles.back() * 180 / PI;

		//add character animation> based on the angles intervals, change its image when shooting, also the position like before, set player texture also
		if (degrees <= 45 && degrees > -45)//right
		{
			player.yshoot = 2;
			bullets.back().getbullet().setPosition(player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width / 2+10,
				player.getentity().getGlobalBounds().height / 2));
			bool& temp = player.getshooting();
			temp = true;
			}
		else if (degrees <= -45 && degrees > -135)//up
		{
			player.yshoot = 1;
			bullets.back().getbullet().setPosition(player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width / 2 ,
				player.getentity().getGlobalBounds().height / 2-10));
			bool& temp = player.getshooting();
			temp = true;

		}
		else if (degrees > 45 && degrees <= 135)//down
		{
			player.yshoot = 0;
			bullets.back().getbullet().setPosition(player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
				player.getentity().getGlobalBounds().height / 2 +10));
			bool& temp = player.getshooting();
			temp = true;

		}
		else//left
		{
			player.yshoot = 3;
			bullets.back().getbullet().setPosition(player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width / 2 -10,
				player.getentity().getGlobalBounds().height / 2 ));
			bool& temp = player.getshooting();
			temp = true;

		}




		
	}
	else if (currentbullets == 0)
	{
		bool& temp = player.getshooting();
		temp = false;
		animationTime =0;
	}




}

std::vector<Bullet>& Projectile::getbullets()
{
	return this->bullets;
}

std::vector<float>& Projectile::getangle()
{
	return this->angles;
}

void Projectile::setbullets()
{
	currentbullets = 18;
}

int Projectile::getcurrentbullets()
{
	return currentbullets;
}

float Projectile::getspeed()
{
	return this->speed;
}

void Projectile::deallocatebullets(sf::View view)
{//x3,33 because of the zoomed in verison og the gameview
	int topleftx =( view.getCenter().x - view.getSize().x / 2)*3.33;
	int toplefty = (view.getCenter().y - view.getSize().y / 2) * 3.33;
	int toprightx = (view.getCenter().x + view.getSize().x / 2) * 3.33;
	int toprighty = (view.getCenter().y - view.getSize().y / 2) * 3.33;
	int bottomleftx =( view.getCenter().x - view.getSize().x / 2) * 3.33;
	int bottomlefty = (view.getCenter().y + view.getSize().y / 2) * 3.33;
	int bottomrightx = (view.getCenter().x + view.getSize().x / 2) * 3.33;
	int bottomrighty = (view.getCenter().y + view.getSize().y / 2) * 3.33;

	int i = 0;
	//get the positions of all the bullets and if not in the view, delete them
	for (int i = 0; i < bullets.size(); )
	{
		Bullet& b = bullets[i];
		sf::CircleShape cs = b.getbullet();
		int posx = cs.getPosition().x;
		int posy = cs.getPosition().y;

		// If the bullet is out of the view, erase it
		if (posx < topleftx || posy < toplefty || posx > bottomrightx || posy > bottomrighty)
		{
			bullets.erase(bullets.begin() + i);  // Remove the bullet
			angles.erase(angles.begin() + i);
		}
		else
		{
			i++;  // Only increment if no bullet is erased
		}
	}
}




void Projectile::checkforcollisions(int map[100][150], sf::RenderWindow& window)
{
	for (int i = 0; i < bullets.size();)
	{
		Bullet& b = bullets[i];
		sf::CircleShape cs = b.getbullet();
		int posx = cs.getPosition().x;
		int posy = cs.getPosition().y;

		if (map[posy / 32][posx / 32] == 2)//if it collides with an object
		{
		//	sf::Sprite temp;
			//temp.setPosition(posx, posy);
			//sf::Texture temp2;
			//temp2.loadFromFile("assets/images/character/Bullet.png");
			//temp.setTextureRect(sf::IntRect(96, 0, 32, 32));


			bullets.erase(bullets.begin() + i);
			angles.erase(angles.begin() + i);
			//window.draw(temp);
		}
		else
			i++;


	}

}





sf::CircleShape& Bullet::getbullet()
{
	return this->bullet;
}

void Bullet::setactivity()
{
	this->active = !this->active;
}

Bullet::Bullet()
{
	this->bullet.setFillColor(sf::Color::Yellow);
	this->bullet.setOrigin(0, 0);
	this->bullet.setRadius(1.2);
}







int Sword::calculateangle(Player player, sf::RenderWindow& window, sf::View view)
{

	float posmousex = sf::Mouse::getPosition(window).x + view.getCenter().x - view.getSize().x / 2 * 3.333;
	float posmousey = sf::Mouse::getPosition(window).y + view.getCenter().y - view.getSize().y / 2 * 3.333;

	float playerposx = player.getentity().getPosition().x + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
		player.getentity().getGlobalBounds().height / 2).x;
	float playerposy = player.getentity().getPosition().y + sf::Vector2f(player.getentity().getGlobalBounds().width / 2,
		player.getentity().getGlobalBounds().height / 2).y;

	float angleinrad= atan2(posmousey - playerposy, posmousex - playerposx);
	float degrees = angleinrad* 180 / PI;

	if (degrees <= 45 && degrees > -45)//right
	{ //set angle here
		offset = sf::Vector2f(20, 0);
		angle = 2;
		return 2;
		
	}
	else if (degrees <= -45 && degrees > -135)//up
	{
		offset = sf::Vector2f(-8, -25);
		angle = 1;
		return 1;

	}
	else if (degrees > 45 && degrees <= 135)//down
	{
		offset = sf::Vector2f(-8, +35);
		angle = 0;
		return 0;

	}
	else//left
	{
		offset = sf::Vector2f(-25, 0);
		angle = 3;
		return 3;

	}
	
}

bool& Sword::getactivesword()
{
	return this->isactive;
}

void Sword::setposition(Player player)
{
	
	text.loadFromFile("assets/images/character/swing2.png");
	//need to calculate based on angle;if angle== .....
		 this->hitbox.setTexture(text);
	//set a texture instead of a color with a rotation transform


		 hitbox.setOrigin(sf::Vector2f(text.getSize().x / 2, text.getSize().y));
		 

		sf::Vector2f playerCenter = player.getentity().getPosition() + 
			sf::Vector2f(player.getentity().getGlobalBounds().width / 2, 0);

		if (angle == 2) {  // Right
			this->hitbox.setRotation(90);  // No rotation
			offset = sf::Vector2f(10, 15);  // Move to the right of the player
		}
		else if (angle == 1) {  // Up
			this->hitbox.setRotation(0);  // Rotate upward
			offset = sf::Vector2f(0, 0);  // Move above the player
		}
		else if (angle == 3) {  // Left
			this->hitbox.setRotation(270);  // Rotate left
			offset = sf::Vector2f(-10, +15);  // Move to the left of the player
		}
		else if (angle == 0) {  // Down
			this->hitbox.setRotation(180);  // Rotate downward
			offset = sf::Vector2f(0, 25);  // Move below the player
		}

		if (player.totaltime < 0.8 / 2) {
			fadingIn = true;
			alphaValue = static_cast<int>(255 * (player.totaltime / (0.8 / 2)));
		}
		else {
			fadingIn = false;
			alphaValue = static_cast<int>(255 * (1 - ((player.totaltime - 0.8 / 2) / (0.8 / 2))));
		}
		alphaValue = std::max(0.0f, std::min(255.0f, alphaValue));
		sf::Color spriteColor = hitbox.getColor();
		spriteColor.a = static_cast<sf::Uint8>(alphaValue);  
		hitbox.setColor(spriteColor);

		sf::FloatRect temprect = hitbox.getGlobalBounds();
		swordhitbox = temprect;
	
		

		this->hitbox.setPosition(playerCenter + offset);

}

sf::Sprite& Sword::getfrect()
{
	return this->hitbox;
}
