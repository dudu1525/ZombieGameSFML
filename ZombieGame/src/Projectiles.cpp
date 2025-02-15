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

	

		angles.push_back(atan2(posmousey - playerposy,
			posmousex - playerposx));
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
