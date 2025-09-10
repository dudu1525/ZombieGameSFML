#include "../include/Player.h"

//make bullets do damage to zombies, then make them die when they reach 0 hp, so see in zombies 
//make collision the zombies so bullets dissapear, 
//if a zombie dies, a new one respawns, this is the last part

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

	

}

void Player::setcharacter(sf::Vector2f dir,float deltaTime)
{
	updateentity(dir,deltaTime);
}

sf::Vector2f Player::getPlayerCenter()
{
    return  this->getentity().getPosition()
    + sf::Vector2f(this->getentity().getGlobalBounds().width / 2,
     this->getentity().getGlobalBounds().height / 2);
}
 



void Player::updatehealthvalue(int damage, float deltaTime, bool isbeingdmg)
{
    static float accumulatedtime = 0.0f;
    const float invincframe = 0.6f;

    accumulatedtime += deltaTime;

    if (isbeingdmg && !isinvincible)  
    {
        this->health -= damage;
        isinvincible = true;
        accumulatedtime = 0.0f; 
    }

    if (isinvincible && accumulatedtime >= invincframe)
    {
        isinvincible = false;
    }
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


int Player::getselectedweap()
{
	return selectedweap;
}

void Player::setselectedweap(int id)
{
	selectedweap = id;
}

void Player::setshooting(float timePerFrame)
{
	static float animationTime = 0.f; 
	const float frameDuration = 0.05f;
	animationTime += timePerFrame;

		xshoot = (xshoot + 1) % 4;
		actiontexture.loadFromFile("assets/images/character/Shoot.png");
		actionentity.setTexture(actiontexture);
		actionentity.setTextureRect(sf::IntRect(xshoot * 32, yshoot*32, 32, 26));//last 2 are width, first is the column, second is the row
		
	
}

bool& Player::getshooting()
{
	return isshooting;
}

void Player::sethealth(int health)
{
    this->health = health;
}

void Player::updateplayertile(int tiles[HEIGHT][WIDTH])
{
    tiles[playertile.y][playertile.x] = 0;
    playertile.x = static_cast<int>(this->getPlayerCenter().x) / 32;
    playertile.y = static_cast<int>(this->getPlayerCenter().y) / 32;
    tiles[playertile.y][playertile.x] = 4;
 
}


void Player::setstabbing(float timePerFrame,int position) {//takes 0.8 seconds
    animationTimer += timePerFrame;
    if (isstabbing==true)
    totaltime += timePerFrame;
    if (isstabbing && animationTimer >= 0.2f) {
        
        actiontexture.loadFromFile("assets/images/character/Stab.png");
        actionentity.setTexture(actiontexture);
        actionentity.setTextureRect(sf::IntRect(xstab * 32, position*32, 32, 26));
        xstab = (xstab + 1) % 4;
        // Reset animation timer
        animationTimer = 0.0f;

        // Stop stabbing after 4 frames
        if (xstab == 0) {
            isstabbing = false;
            totaltime = 0.0f;
            actiontexture.loadFromFile("assets/images/character/Idle.png");
            actionentity.setTexture(actiontexture);
        }
    }
}

bool& Player::getstabbing()
{
    return isstabbing;
}


void Player::updateentity(sf::Vector2f dir, float timePerFrame)
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

   

    animationTime += timePerFrame;
    idleTime += timePerFrame;

    if (!isstabbing)

    {
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
                    setshooting(timePerFrame);
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
                    setshooting(timePerFrame);
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
}


sf::Sprite& Player::getentity2()
{
	return actionentity;
}
sf::Sprite& Player::getentity3()
{
	return baseentity;
}

