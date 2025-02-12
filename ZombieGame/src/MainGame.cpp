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

  

    map.givepath("assets/images/map/try1.png");//choose image for the main map
   
 
        
    //this->game->view.zoom(0.3); 
    
    gameview = this->game->window.getView();
        
   // uiview = this->game->window.getView();
    gameview.zoom(0.3);


    


    //generated
    //if (!map.load("maptiles.png", sf::Vector2u(32, 32), 250, 150))
      //  return ;
}

void MainGame::draw()
{
    
    this->game->window.setView(gameview);


   //draw map,player, gameview parts
    this->game->window.draw(map.getmap());
   this->game->window.draw(player.getentity());


   //draw gui stuff.
   this->game->window.setView(uiview);
   sf::RenderStates rs;
     UIMainGame   e(uiview);
   // e.draw(this->game->window,rs);
    e.changestamina(100, player.stamina, this->game->window, rs);
   
   //this->game->window.draw(ui.elements);

}

void MainGame::update(sf::Time timePerFrame)
{

    sf::Vector2f playerPosition = player.getentity().getPosition();
    this->game->dm.updatePosition(player.getentity().getPosition().x, player.getentity().getPosition().y);//update location in database
    sf::Vector2f playerCenter = player.getentity().getPosition() + sf::Vector2f(player.getentity().getGlobalBounds().width/2 , player.getentity().getGlobalBounds().height/2 );

    gameview.setCenter(playerCenter);//set view to player position
    
   
    handlemapedges();
    //enter updating the char image
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
    
   // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      //  this->game->pushState(new PauseMenu(this->game));
    
 
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

    //update position
    player.getentity().setPosition(playerPosition);
}
