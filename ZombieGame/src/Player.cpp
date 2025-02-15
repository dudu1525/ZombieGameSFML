#include "../include/Player.h"
#include <iostream>


Player::Player(std::string imagepath)
	
{
	textureentity.loadFromFile(imagepath);
	actiontexture.loadFromFile(imagepath);
	sf::Sprite sprite(textureentity, sf::IntRect(0, 0, 32, 32));
	sf::Sprite sprite2(actiontexture, sf::IntRect(0, 0, 32, 26));
	sf::Sprite sprite3(actiontexture, sf::IntRect(0, 0, 32, 6));

	spriteentity = sprite;
	actionentity = sprite2;
	baseentity = sprite3;
	xidle = 0;
	yidle = 0;
	//spriteentity.setScale(1.1, 1.1);
	//actionentity.setScale(1.1, 1.1);
	//baseentity.setScale(1.1, 1.1);

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

void Player::updatestamina(bool sprint,float deltaTime)
{
	static float updatetime = 0.f;
	const float framedur = 0.1f;

	updatetime += deltaTime;
	if (updatetime>=framedur)
	{
		updatetime -= framedur;
		if (sprint == true)//if sprinting, decrease stamina
		{
			if (this->stamina > 0 )
				this->stamina -= depletionrate;
			else if (this->stamina == 0)
			{		
				
				this->stamina = -10;
			}
			

		}
		else
		{
			if (stamina <= 98)
				this->stamina += depletionrate;
				else
			{
				this->stamina = 100;

					}

		}
	}

}

int Player::getdepletion()
{
	return depletionrate;
}

int Player::getselectedweap()
{
	return selectedweap;
}

void Player::setselectedweap(int id)
{
	selectedweap = id;
}

void Player::setshooting(float deltaTime)
{
	static float animationTime = 0.f; 
	const float frameDuration = 0.05f;
	animationTime += deltaTime;
//	if (animationTime>=frameDuration)
	//{
		//animationTime = 0;
		xshoot = (xshoot + 1) % 4;
		actiontexture.loadFromFile("assets/images/character/Shoot.png");
		actionentity.setTexture(actiontexture);
		actionentity.setTextureRect(sf::IntRect(xshoot * 32, yshoot*32, 32, 26));//last 2 are width, first is the column, second is the row
		
	//}
}

bool& Player::getshooting()
{
	return isshooting;
}

void Player::updateentity(sf::Vector2f dir, float deltaTime)
{
    static float animationTime = 0.f;
    static float idleTime = 0.f;
    
    
    float idleFrameDuration = 0.4f; 
    float frameDuration = 0.15f; 
    



    if (isshooting)
    {
        idleFrameDuration = 0.1f; 
        frameDuration = 0.1f;      
    }

    animationTime += deltaTime;
    idleTime += deltaTime;

    
    if (dir.x == 0 && dir.y == 0)
    {
        moving = 0; 

        if (idleTime >= idleFrameDuration)
        {
            idleTime -= idleFrameDuration; 
            animationTime = 0;            

          
            xidle = (xidle == 0) ? 1 : 0;

         
            basetexture.loadFromFile("assets/images/character/Idle.png");
            baseentity.setTexture(basetexture);
            baseentity.setTextureRect(sf::IntRect(xidle * 32, 26, 32, 6));

            if (isshooting)
            {
                setshooting(deltaTime);
            }
            else
            {
                actiontexture.loadFromFile("assets/images/character/Idle.png");
                actionentity.setTexture(actiontexture);
                actionentity.setTextureRect(sf::IntRect(xidle * 32, 0, 32, 26));
            }
        }
    }
    else // is moving
    {
        if (animationTime >= frameDuration) 
        {
            idleTime = 0; 
            animationTime -= frameDuration; 
            moving = 1; 

            
            xwalk = (xwalk + 1) % 4;

            
            if (dir.x > 0)
                ywalk = 2; // Right
            else if (dir.x < 0)
                ywalk = 3; // Left

            if (dir.y > 0)
                ywalk = 0; // Down
            else if (dir.y < 0)
                ywalk = 1; // Up

            basetexture.loadFromFile("assets/images/character/Walk.png");
            baseentity.setTexture(basetexture);
            baseentity.setTextureRect(sf::IntRect(xwalk * 32, ywalk * 32 + 26, 32, 6));

            if (isshooting)
            {
                setshooting(deltaTime); 
            }
            else
            {
                actiontexture.loadFromFile("assets/images/character/Walk.png");
                actionentity.setTexture(actiontexture);
                actionentity.setTextureRect(sf::IntRect(xwalk * 32, ywalk * 32, 32, 26));
            }
        }
    }
}


sf::Sprite& Player::getentity2()
{
	return actionentity;
}
sf::Sprite& Player::getentity3()
{
	return baseentity;
}
void Player::setpos2(float x, float y)
{
	actionentity.setPosition(x, y);

}

void Player::setpos3(float x, float y)
{
	baseentity.setPosition(x, y);
}
