#include "../include/Player.h"



Player::Player(std::string imagepath)
	
{
	textureentity.loadFromFile(imagepath);
	sf::Sprite sprite(textureentity, sf::IntRect(0, 0, 32, 32));

	spriteentity = sprite;
	xidle = 0;
	yidle = 0;
	//spriteentity.setTexture()
	spriteentity.setScale(1.1, 1.1);


}

void Player::setcharacter(sf::Vector2f dir,float deltaTime)
{
	updateentity(dir,deltaTime);
}


void Player::setxidle(int x)
{
	xidle = x;
}

void Player::setyidle(int y)
{
	yidle = y;
}

int Player::getxidle()
{
	return xidle;
}

int Player::getyidle()
{
	return yidle;
}

void Player::updateentity(sf::Vector2f dir,float deltaTime)//update the images of the character
{
	static float animationTime = 0.f; // Accumulate animation time, initialized only once 
	const float frameDuration = 0.1f; // 0.1 seconds per frame (10 FPS)

	static float idleTime = 0.f; // Accumulate animation time for idle
	const float idleFrameDuration = 0.6f;


	animationTime += deltaTime;//add 1 frame each time
	idleTime += deltaTime;
	if (animationTime >= frameDuration)
	{
		animationTime -= frameDuration; // Reset for the next frame
		
		if (dir.x == 0 && dir.y == 0)
		{
			if (idleTime >= idleFrameDuration)
			{
				idleTime -= idleFrameDuration; // Reset idle time
				if (xidle == 0)
					xidle = 1;
				else
					xidle = 0;
				textureentity.loadFromFile("assets/images/character/Idle.png");
				spriteentity.setTexture(textureentity);
				
				spriteentity.setTextureRect(sf::IntRect(xidle * 32, 0, 32, 32));
			}
		}
		else
		{
			xwalk = (xwalk + 1) % 4;
			if (dir.x > 0)
				ywalk = 2;
			else if (dir.x < 0)
				ywalk = 3;

			if (dir.y > 0)
				ywalk = 0;
			else if (dir.y < 0)
				ywalk = 1;

			textureentity.loadFromFile("assets/images/character/Walk.png");
			spriteentity.setTexture(textureentity);
			spriteentity.setTextureRect(sf::IntRect(xwalk * 32, ywalk * 32, 32, 32));

		}


	}



	 


}