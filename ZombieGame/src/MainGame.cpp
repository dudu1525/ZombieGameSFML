#include "../include/MainGame.h"
#include "../include/PauseMenu.h"
// . means current and .. means root of current
#define PI 3.14159265
#define NRZOMBIES 30

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

    int v[2] = { 0,0 };
    this->game->dm.queryData(v); //retrieve position from database
    player.setpos((float)v[0],(float) v[1]);
    player.sethealth(this->game->dm.gethealthdb());
    e.changehealth(player.health, 100);

    float playerCenterX = player.getentity().getGlobalBounds().left + player.getentity().getGlobalBounds().width / 2.0f;
    float playerCenterY = player.getentity().getGlobalBounds().top + player.getentity().getGlobalBounds().height / 2.0f;

    //get tile of player
    int playerTileX = static_cast<int>(playerCenterX) / 32;
    int playerTileY = static_cast<int>(playerCenterY) / 32;
    map.tileMatrix[playerTileY][playerTileX] = 3; //mark player tile

  


   // zombie1.setpos((float)v[0] - 40, (float)v[1]);

   // zombie2.setpos((float)v[0] + 40, (float)v[1]);
   

    map.givepath("assets/images/map/try4.png");//choose image for the main map    
    map.matrixbuilder();

     positionzombies();


    gameview = this->game->window.getView();
        
    gameview.zoom(0.3);


    


}

void MainGame::draw()
{
    
    this->game->window.setView(gameview);

   //draw game ui items
    this->game->window.draw(map.getmap());

    for (int i=0;i<NRZOMBIES;i++)
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
    this->game->dm.updatePosition(player.getentity().getPosition().x, player.getentity().getPosition().y);//update location in database
    sf::Vector2f playerCenter = player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width/2 , player.getentity().getGlobalBounds().height/2 );

    gameview.setCenter(playerCenter);//set view to player center position


    float deltaTime2 = clock2.restart().asSeconds();
    player.setstabbing(deltaTime2, sword.calculateangle(player,this->game->window,gameview));
   
    handlemapedges();
    
    updateplayerhealth();

    for (int i=0;i<NRZOMBIES;i++)
    detectzombie(zombies[i]);
  


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

    // Get the current size of the view
    sf::Vector2f viewSize = gameview.getSize();

    // Get the player's current position and bounds
    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();

    // Calculate the player's center position
    sf::Vector2f playerCenter = sf::Vector2f(
        playerPosition.x + playerBounds.width / 2,
        playerPosition.y + playerBounds.height / 2
    );

    // Get half of the view size for clamping
    sf::Vector2f halfViewSize = viewSize / 2.0f;

    // Clamp the view center so it doesn't go out of bounds
    float clampedX = std::max(halfViewSize.x, std::min(playerCenter.x, mapWidth - halfViewSize.x));
    float clampedY = std::max(halfViewSize.y, std::min(playerCenter.y, mapHeight - halfViewSize.y));

    // Update the view's center
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
    adjustedBounds.top += 25;             
    adjustedBounds.width -= (20);      
    adjustedBounds.height -=25;           
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



void MainGame::detectzombie(Zombie& zombie)
{
    float angle=0;
    sf::FloatRect playerBounds = player.getentity().getGlobalBounds();
    sf::FloatRect zombiebounds = zombie.getentity().getGlobalBounds();

   // printf("%d %d \n", zombie.getposx(), zombie.getposy());

    sf::FloatRect adjustedBounds = playerBounds;
    adjustedBounds.left += 10;
    adjustedBounds.top += 15;
    adjustedBounds.width -= (20);
    adjustedBounds.height -= 15;

   
    float hittime = 0.8f;

    if (zombie.zombiecollision.intersects(adjustedBounds))
    {   

        bool& temp = zombie.getisattacking();
        temp = true;
        zombie.damageTime += this->game->time.asSeconds();
        if (zombie.damageTime >= hittime)
        {//add the angle between the center of the zombie and the center of the player and add the angle as a argument for the zombieanimations, maybe call it here
            zombie.damageTime = 0.0f;
            player.updatehealthvalue(10, this->game->time.asSeconds(), true);
            e.changehealth(player.health, 100);

            

        }


    }
    else
    {
        player.updatehealthvalue(10, this->game->time.asSeconds(), false);

        zombie.damageTime = 0.0f;
    }

    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::Vector2f playerCenter = sf::Vector2f(
        playerPosition.x + playerBounds.width / 2,
        playerPosition.y + playerBounds.height / 2
    );

    sf::Vector2f zombieposition = zombie.getentity().getPosition();
    sf::Vector2f zombiecenter = sf::Vector2f(
        zombieposition.x + zombiebounds.width / 2,
        zombieposition.y + zombiebounds.height / 2
    );


    angle = atan2(playerCenter.y - zombiecenter.y, playerCenter.x - zombiecenter.x);
    float degrees = angle * 180 / PI;
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

    
    zombie.zombieanimations(this->game->time.asSeconds(),angle);



}

void MainGame::positionzombies()
{
    int height = 100;
    int width = 150;
    for (int i = 0; i < 30; i++)
    {
        int xrand=0, yrand=0;
        xrand = rand() % width + 1;
        yrand = rand() % height + 1;
        while (map.tileMatrix[yrand][xrand] == 2 || map.tileMatrix[yrand][xrand] == 3 || yrand==149 || xrand==100)
        {
            xrand = rand() % width + 1;
            yrand = rand() % height + 1;

        }

        map.tileMatrix[yrand][xrand] = 3;

        this->zombies[i].setpos(yrand * 32 , xrand * 32 );
      //  printf("%d %d ",yrand,xrand );


    }
}

void MainGame::clearzombies()
{
    for (int i=0;i<100;i++)
        for (int j = 0; j < 150; j++)
        {
            if (map.tileMatrix[i][i] == 3)
                map.tileMatrix[i][i] = 0;
        }
}

void MainGame::updateplayerhealth()//add invincibility frame, add here the database 
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
        e.changehealth(player.health, 100);
    }
    else
        player.updatehealthvalue(10, timePerFrame.asSeconds(), false);

}
