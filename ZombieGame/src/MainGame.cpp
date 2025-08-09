#include "../include/MainGame.h"
#include "../include/PauseMenu.h"
// . means current and .. means root of current
#define PI 3.14159265
#define MAXZOMBIES 50
//all zombies stop at a set x coordinate
MainGame::~MainGame()
{
}

sf::Clock clock2;
MainGame::MainGame(Game* game):player("assets/images/character/Idle.png")
{ 
    srand(time(NULL));
	this->game = game;
	printf(" main game constructor done");
    
    float xfloat = (float)game->getWindowWidth()/2;
    float yfloat = (float)game->getWindowHeight()/2;

 

           player.setpos(xfloat, yfloat);//basic coords and health
           player.sethealth(100);
    player.updateplayertile(map.tileMatrix); //update location in the tilemap
   

   // /float playerCenterX = player.getentity().getGlobalBounds().left + player.getentity().getGlobalBounds().width / 2.0f;
   // float playerCenterY = player.getentity().getGlobalBounds().top + player.getentity().getGlobalBounds().height / 2.0f;

    //get tile of player
  //  int playerTileX = static_cast<int>(playerCenterX) / 32;
   // int playerTileY = static_cast<int>(playerCenterY) / 32;
    //map.tileMatrix[playerTileY][playerTileX] = 4; //mark player tile





   // zombie1.setpos((float)v[0] - 40, (float)v[1]);

   // zombie2.setpos((float)v[0] + 40, (float)v[1]);
   

    map.givepath("assets/images/map/try4.png");//choose image for the main map    
    map.matrixbuilder();//construct based on rocks and so on
    for (int i = 0; i < currentZombies; i++)//initially set to 30
    {
        Zombie z;
        zombies.push_back(z);
    }
     positionzombies();//position zombies randomly on the map



     //view related
    gameview = this->game->window.getView();   
    gameview.zoom(0.3);


    


}
void MainGame::loadPlayer()
{
    int v[2] = { 0,0 };
    this->game->dm.queryData(v); //retrieve position from database
    player.setpos((float)v[0], (float)v[1]);
    player.sethealth(this->game->dm.gethealthdb());
    e.changehealth(player.health, 100); //for testing purposes
    player.updateplayertile(map.tileMatrix);

}
void MainGame::serializeData()
{
    printf("serialize called ");
    const std::string dataFile = "assets/files/gamedata.dat";
    std::ofstream data(dataFile, std::ios::binary);
    if (!data.is_open())  
    {
        printf("couldnt open or create file! ");
        return;
    }
   
    data.write(reinterpret_cast<const char*>(&serializedPassedTime), sizeof(float));
    data.write(reinterpret_cast<const char*>(&currentZombies), sizeof(int));
    //serialize current nr of zombies   
    //serialize each zombie
    for (int i = 0; i < currentZombies; i++)
    {
        zombies[i].serializeZombieData(data);
    }


    data.close();
    this->game->dm.updatePosition(player.getentity().getPosition().x, player.getentity().getPosition().y);//update location in database


   std::cout << "data serialized successfully." << std::endl;

    
}

void MainGame::draw()
{
    
    this->game->window.setView(gameview);

   //draw game ui items
    this->game->window.draw(map.getmap());

    for (int i=0;i<zombies.size();i++)
    {
      

       

        this->game->window.draw(zombies[i].getentity());


        zombies[i].drawzombiehp(this->game->window);

    }
  

   this->game->window.draw(player.getentity2());//draw legs
   this->game->window.draw(player.getentity3());//draw torso

   

   if (player.getstabbing() == true)
   {
       
       sword.setposition(player);//thats why it changes, here the fade in and fade out effect can be added?
       this->game->window.draw(sword.getfrect());
   }
    
   
   for (int i = 0; i < proj.getbullets().size(); i++)
   {
       this->game->window.draw(proj.getbullets()[i].getbullet());
       proj.getbullets()[i].getbullet().move(proj.getspeed() * cos(proj.getangle()[i]), proj.getspeed() * sin(proj.getangle()[i]));
       proj.checkforcollisions(map.tileMatrix,this->game->window);//check for the collision with other objects
       proj.collisionWithZombies(map.tileMatrix, this->game->window, zombies, currentZombies);

   }


    

   //draw gui stuff.
   this->game->window.setView(uiview);
   sf::RenderStates rs;
   //  UIMainGame   e(uiview);
   // e.draw(this->game->window,rs);
    e.changestamina(100, player.stamina, this->game->window, rs,this->game->window);
   

}

void MainGame::update(sf::Time timePerFrame)
{
    //update player position based on arrows pressed
    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::Vector2f playerCenter = player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width/2 , player.getentity().getGlobalBounds().height/2 );

    player.updateplayertile(map.tileMatrix); //update the current player tile
        
    for (int i = 0; i < zombies.size(); i++)
    {
        zombies[i].checkforplayer(map.tileMatrix);
        zombies[i].movez(player,map.tileMatrix); //function used by the zombie to move to the player, using a bfs format
        zombies[i].followPath(this->game->time);
        zombies[i].attackPlayer(player,e);
      
        zombies[i].updateZombieTiles(map.tileMatrix);
        
        //update zombie tile
    }
    if (player.getstabbing() == true)//register sword hits
    {
        sword.swordHitZombies(zombies);
    }

    deallocateDeadZombies();
    //make more zombies once 1minute passes, 


    printf("zombie vector size: %d\ncurrent zombie counter:%d\n", zombies.size(), this->currentZombies);
   // player.updateplayertile(map.tileMatrix); //update the current player tile

    gameview.setCenter(playerCenter);//set view to player center position


    float deltaTime2 = clock2.restart().asSeconds();
    player.setstabbing(deltaTime2, sword.calculateangle(player,this->game->window,gameview));//stabbing animation, if player is stabbing
   
    handlemapedges();
    
    updateplayerhealth();

  
    e.updateTimeAliveUI(this->localPassedTime.getElapsedTime().asSeconds() + serializedPassedTime);


    if (frompause == 1)
    {
        clearzombies();
        frompause = 0;
        this->game->popState();

    }
}

void MainGame::handleInput()
{ 
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    moveplayerinput(timePerFrame);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && player.stamina>=0  && player.moving==true)
    {
        player.updatestamina(true, timePerFrame.asSeconds());
        player.setspeed(200);
    }
    else 
    {
        player.updatestamina(false, timePerFrame.asSeconds());
        player.setspeed(150);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.getselectedweap() == 2)
    {
        proj.shoot(player,this->game->window,gameview);

        sf::Text& temp2 = e.getbulletstext();
        std::string st = std::to_string(proj.getcurrentbullets()) + "/18";
        temp2.setString(st);

    }
    else
    {
        bool& isshootingtemp = player.getshooting();
        isshootingtemp = false;
    }
    
  

    
}

void MainGame::handleResizing(sf::Event& event)
{
}

void MainGame::handleInputs(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        this->game->window.setView(gameview);
        this->game->ispaused = 0;
        serializedPassedTime += localPassedTime.getElapsedTime().asSeconds();
        this->game->pushState(new PauseMenu(this->game,this));
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)//crossbow
    {
        e.selected1 = !e.selected1;
        e.selected2 = 0;
        if (e.selected1 == 1)
        {
            player.setselectedweap(2);
            bool& temp = e.getbulletsvisib();
            sf::Text& temp2 = e.getbulletstext();
            std::string st = std::to_string(proj.getcurrentbullets()) + "/18";
            temp2.setString(st);
           temp = 1;
        }
        else if (e.selected2 == 0 && e.selected1 == 0)
        {
            player.setselectedweap(0);
            bool& temp = e.getbulletsvisib();
            temp = 0;
        }

    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)//sword
    {
        e.selected2 = !e.selected2;
        e.selected1 = 0;
        if (e.selected2 == 1)
        {
            player.setselectedweap(1);
            bool& temp = e.getbulletsvisib();
            sf::Text& temp2 = e.getbulletstext();
            temp2.setString("  inf");
            temp = 1;
        }
        else if (e.selected2 == 0 && e.selected1 == 0)
        {
            player.setselectedweap(0);
            bool& temp = e.getbulletsvisib();
            temp = 0;
        }

    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
    {
       proj.deallocatebullets(gameview);
        proj.setbullets();
        sf::Text& temp2 = e.getbulletstext();
        std::string st = std::to_string(proj.getcurrentbullets()) + "/18";
        temp2.setString(st);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left && e.selected2==true)
    {
        bool& isstabbingtemp = player.getstabbing();
        isstabbingtemp = true;
        bool& projecttemp = sword.getactivesword();
        projecttemp = true;

        //call the sword sprite to be seen here, make it appear as long as the isstabbing is true and give it a direction
        //so the hitbox is seen
        
    }

    

}

void MainGame::setfrompause()
{
    frompause = 1;
}



void MainGame::moveplayerinput(sf::Time deltaTime)
{
    float movementSpeed = player.getspeed();
    sf::Vector2f direction(0.f, 0.f);
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.f; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.f; // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x -= 1.f; // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x += 1.f; // Move right
    }

   //normalize for diagonal movement
    if (direction.x != 0.f || direction.y != 0.f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; 
    }

    handleobjects(direction);
   // zombiecollision(direction); further testing

    if (player.getstabbing() == true)
        movementSpeed = 0;

    player.getentity().move(direction * movementSpeed * deltaTime.asSeconds());//added *deltatime
    handleplayeredges();
    player.setpos(player.getentity().getPosition().x, player.getentity().getPosition().y);
    //get the position and save it to the other sprite, or call the function 2 times

    player.setcharacter(direction,deltaTime.asSeconds());//animations

}
void MainGame::handlemapedges()
{
    float mapWidth = 150 * 32; 
    float mapHeight = 100 * 32; 

    
    sf::Vector2f viewSize = gameview.getSize();

   
    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();

   
    sf::Vector2f playerCenter = sf::Vector2f(
        playerPosition.x + playerBounds.width / 2,
        playerPosition.y + playerBounds.height / 2
    );

   
    sf::Vector2f halfViewSize = viewSize / 2.0f;

    
    float clampedX = std::max(halfViewSize.x, std::min(playerCenter.x, mapWidth - halfViewSize.x));
    float clampedY = std::max(halfViewSize.y, std::min(playerCenter.y, mapHeight - halfViewSize.y));

    
    gameview.setCenter(clampedX, clampedY);
}


void MainGame::handleplayeredges()
{
    float mapWidth = 150 * 32;  
    float mapHeight = 100 * 32; 

  
    sf::Vector2f playerPosition = player.getentity().getPosition();

   
    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();
  

   
    if (playerPosition.x < 0) {
        playerPosition.x = 0; // Prevent moving left out of bounds
    }
    else if (playerPosition.x + playerBounds.width > mapWidth) {
        playerPosition.x = mapWidth - playerBounds.width; // Prevent moving right out of bounds
    }

   
    if (playerPosition.y < 0) {
        playerPosition.y = 0; // Prevent moving up out of bounds
    }
    else if (playerPosition.y + playerBounds.height > mapHeight) {
        playerPosition.y = mapHeight - playerBounds.height; // Prevent moving down out of bounds
    }


    float posx = playerPosition.x;
    float posy = playerPosition.y + 26;
    sf::Vector2f playerpos2(posx, posy);//needed for legs part of sprite


    //update position
    player.getentity().setPosition(playerPosition);
    //update sprites
    player.getentity2().setPosition(playerPosition);
    player.getentity3().setPosition(playerpos2);

}

void MainGame::handleobjects(sf::Vector2f& direction)
{
    
    const int tileSize = 32;

    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();

    //substract some pixels for better visuals
    sf::FloatRect adjustedBounds = playerBounds;
    adjustedBounds.left += 10;            
    adjustedBounds.top += 10;             
    adjustedBounds.width -= (20);      
    adjustedBounds.height -=10;           
    //center of player
    float playerCenterX = adjustedBounds.left + adjustedBounds.width / 2.0f;
    float playerCenterY = adjustedBounds.top + adjustedBounds.height / 2.0f;

    //get tile of player
    int playerTileX = static_cast<int>(playerCenterX) / tileSize;
    int playerTileY = static_cast<int>(playerCenterY) / tileSize;

    if (direction.x != 0.f) {//left
        if (direction.x < 0) {
            sf::FloatRect tileLeft( (playerTileX - 1) * tileSize,playerTileY * tileSize,tileSize,tileSize);

            if (map.tileMatrix[playerTileY][playerTileX - 1] == 2 && adjustedBounds.intersects(tileLeft)) {
                direction.x = 0.f;
            }
        }
        else if (direction.x > 0) {//right
            sf::FloatRect tileRight( (playerTileX + 1) * tileSize,playerTileY * tileSize,tileSize,tileSize);
            if (map.tileMatrix[playerTileY][playerTileX + 1] == 2 && adjustedBounds.intersects(tileRight)) {
                direction.x = 0.f;
            }
        }
    }

    
    if (direction.y != 0.f) {//up
        if (direction.y < 0) {
            sf::FloatRect tileAbove( playerTileX * tileSize, (playerTileY - 1) * tileSize,tileSize, tileSize );
            if (map.tileMatrix[playerTileY - 1][playerTileX] == 2 && adjustedBounds.intersects(tileAbove)) {
                direction.y = 0.f;
            }
        }
        else if (direction.y > 0) {
           
            sf::FloatRect tileBelow(  playerTileX * tileSize,(playerTileY + 1) * tileSize,tileSize, tileSize  );
            if (map.tileMatrix[playerTileY + 1][playerTileX] == 2 && adjustedBounds.intersects(tileBelow)) {
                direction.y = 0.f;
            }
        }
    }


}





void MainGame::positionzombies()
{
    int height = 100;
    int width = 150;
    for (int i = 0; i < currentZombies; i++)
    {
        int xrand=0, yrand=0;
        xrand = rand() % width-10 + 10;
        yrand = rand() % height-10 + 10;
        while (map.tileMatrix[yrand][xrand] == 2 || map.tileMatrix[yrand][xrand] == 4
            || map.tileMatrix[yrand][xrand] == 3 || yrand>=149 || xrand>=100)
        {
            xrand = rand() % width + 1;
            yrand = rand() % height + 1;

        }

        map.tileMatrix[yrand][xrand] = 3;
        
        this->zombies[i].setpos(xrand * 32 , yrand * 32 );
       // printf("zombie %d at:%d x,%d y: \n", i, zombies[i].getposx(), zombies[i].getposy());


    }
  //  printf(" FINALL");

}

void MainGame::clearzombies()
{
    for (int i=0;i<100;i++)
        for (int j = 0; j < 150; j++)
        {
            if (map.tileMatrix[i][j] == 3)
                map.tileMatrix[i][j] = 0;
        }
}

void MainGame::deallocateDeadZombies()
{
    for (int i = 0; i < zombies.size(); )
    {
        if (zombies[i].getHealth() <= 0)
        {
            zombies.erase(zombies.begin() + i);
            
        }
        else//increment if not <=0
        {
            ++i;
        }
    }
    currentZombies = zombies.size();
}

void MainGame::makeMoreZombies()//not used for now
{

    if (currentZombies == MAXZOMBIES)
        return;
    currentZombies++;

    int currentZombiesinVector = zombies.size();
    float incrementFrame = 1.0 / 60;
    accumulatedRespawnTime += incrementFrame;

    if (accumulatedRespawnTime< 3600)
        return;

    for (int i = currentZombiesinVector; i < currentZombies; i++)
    {
        Zombie z;
        zombies.push_back(z);
        //position them on the map
        //update the tilematrix
        //dont let them spawn in range of +-20 from the player
        //check bounds

        //call a function that makes that for a specific zombie

        //give the refference of the zombie

    }
}

void MainGame::updateplayerhealth()//given main game has access to player and ui view, the modif should appear here to the ui
{
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); //get timeperframe as second after

    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();

    sf::Vector2f playerCenter = sf::Vector2f(
        playerPosition.x + playerBounds.width / 2,
        playerPosition.y + playerBounds.height / 2
    );

    int tilex = playerCenter.x / 32;
    int tiley = playerCenter.y / 32;
    if (map.tileMatrix[tiley][tilex] == 1)
    {
        player.updatehealthvalue(10, timePerFrame.asSeconds(),true);
        e.changehealth(player.health, 100);//screen health
    }
    else
        player.updatehealthvalue(10, timePerFrame.asSeconds(), false);

}
