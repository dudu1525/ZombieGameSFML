#include "../include/MainGame.h"
#include "../include/PauseMenu.h"
MainGame::~MainGame()
{
}

MainGame::MainGame(Game* game):player("assets/images/character/Idle.png")
    
{

	this->game = game;
	printf(" main game constructor done");
    
    float xfloat = (float)game->getWindowWidth()/2;
    float yfloat = (float)game->getWindowHeight()/2;

    int v[2] = { 0,0 };
    this->game->dm.queryData(v);
    player.setpos((float)v[0],(float) v[1]);
    player.setpos2((float)v[0], (float)v[1]);
    player.setpos3((float)v[0], (float)v[1]+26);

    map.givepath("assets/images/map/try1.png");//choose image for the main map    
    gameview = this->game->window.getView();
        
    gameview.zoom(0.3);


    


}

void MainGame::draw()
{
    
    this->game->window.setView(gameview);

   //draw map,player, etc
    this->game->window.draw(map.getmap());
  // this->game->window.draw(player.getentity());
    if (player.getshooting() == true)
   this->game->window.draw(player.getentity2());
   this->game->window.draw(player.getentity3());
    
   
   for (int i = 0; i < proj.getbullets().size(); i++)
   {
       this->game->window.draw(proj.getbullets()[i].getbullet());
       proj.getbullets()[i].getbullet().move(proj.getspeed() * cos(proj.getangle()[i]), proj.getspeed() * sin(proj.getangle()[i]));
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
    
   
    handlemapedges();
    

    if (frompause == 1)
    {
        
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

    player.getentity().move(direction * movementSpeed * deltaTime.asSeconds());//added *deltatime
    handleplayeredges();
    //get the position and save it to the other sprite, or call the function 2 times
    

    player.setcharacter(direction,deltaTime.asSeconds());//animations

}
void MainGame::handlemapedges()
{
    float mapWidth = 250 * 32; 
    float mapHeight = 150 * 32; 

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
    float mapWidth = 250 * 32;  
    float mapHeight = 150 * 32; 

  
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

    //update position
    player.getentity().setPosition(playerPosition);
    player.getentity2().setPosition(playerPosition);
    //if (player.getshooting() == false)
    //    player.getentity3().setPosition(playerPosition);
  //  else
        player.setpos3(posx, posy);


}
