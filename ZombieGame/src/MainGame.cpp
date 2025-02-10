#include "../include/MainGame.h"
#include "../include/PauseMenu.h"

MainGame::~MainGame()
{
}

MainGame::MainGame(Game* game):player("assets/images/character/Idle.png")
{

	this->game = game;
	printf("main game constructor done");
    
    float xfloat = (float)game->getWindowWidth()/2;
    float yfloat = (float)game->getWindowHeight()/2;
    player.setpos(2955, 1705);
  
    map.givepath("assets/images/map/try1.png");//choose image for the main map
   
 
  this->game->view.setCenter(1955, 1705); 

    this->game->view.zoom(0.3); 
   


    


    //generated
    //if (!map.load("maptiles.png", sf::Vector2u(32, 32), 250, 150))
      //  return ;
}

void MainGame::draw()
{
   
   // this->game->window.clear(sf::Color::Black);

    this->game->window.setView(this->game->view);
   //draw map,player
    this->game->window.draw(map.getmap());
   this->game->window.draw(player.getentity());

    return;
}

void MainGame::update(sf::Time timePerFrame)
{

    sf::Vector2f playerPosition = player.getentity().getPosition();
    this->game->view.setCenter(playerPosition);//set view to player position
    handlemapedges();
    //enter updating the char image
}

void MainGame::handleInput()
{ 
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    moveplayerinput(timePerFrame);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        player.setspeed(200);
    else
        player.setspeed(150);

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
        this->game->ispaused = 0;
        this->game->pushState(new PauseMenu(this->game));
    }

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

   
    sf::Vector2f viewSize = this->game->view.getSize();
  
    sf::Vector2f playerPosition = player.getentity().getPosition();
    sf::Vector2f halfViewSize = viewSize / 2.0f;
    //to restrict, just take the maximum between the position in coordonates of the view and the position of the player
    float clampedX = std::max(halfViewSize.x, std::min(playerPosition.x, mapWidth - halfViewSize.x));
    float clampedY = std::max(halfViewSize.y, std::min(playerPosition.y, mapHeight - halfViewSize.y));
    //update center of view
    this->game->view.setCenter(clampedX, clampedY);

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
