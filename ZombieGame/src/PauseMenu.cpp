#include "../include/PauseMenu.h"

PauseMenu::~PauseMenu()
{
}
//got zoomed in view(pauseview gets the view multiplied by 0.3)
// , reset by setting to 3.3 view and send it forward
//when popping the view, it gets updated to the x0.3 one

PauseMenu::PauseMenu(Game* game, MainGame* mg)
	:backbtn(200, 50, "Back to Game", 25, sf::Color::Green), 
	startbtn(200, 50, "Main Menu", 25, sf::Color::Green),
	optionsbtn(200, 50, "Options", 25, sf::Color::Green)
	, savegamebtn(200, 50, "Save", 25, sf::Color::Green)
{
	printf("\nconstructor of pause menu: done\n");

	this->game = game;
	pauseview = this->game->window.getDefaultView();

	this->background.setSize(sf::Vector2f(game->window.getDefaultView().getSize().x, game->window.getDefaultView().getSize().y));
	this->background.setFillColor(sf::Color(0, 0, 0, 100));


	this->middlerect.setSize(sf::Vector2f(400,600));
	middlerecttext.setSmooth(1);
	middlerecttext.loadFromFile("assets/images/menutexture.jpg");
	middlerect.setTexture(&middlerecttext);

	
	//set main game
	this->setMGref(mg);
}

void PauseMenu::draw()
{

	//this happens exactly once, then it just gets drawn
	if (this->game->ispaused == 0)
	{
		sf::Vector2f viewCenter = pauseview.getCenter();
		sf::Vector2f viewSize = pauseview.getSize();
		
		this->game->ispaused = 1;

		 
		backgroundTextureimage.create(this->game->window.getSize().x, this->game->window.getSize().y);
		backgroundTextureimage.update(this->game->window);//set current window as texture
		backgroundSprite.setTexture(backgroundTextureimage);

		sf::Vector2f textureSize(backgroundTextureimage.getSize());
		float scaleX = viewSize.x / textureSize.x;
		float scaleY = viewSize.y / textureSize.y;

		backgroundSprite.setScale(scaleX, scaleY);
	
		//the view is 1920x1080 and even when i scale down the windows, the elements on screen get scaled down
		//to fit the 1920x1080 virtual camera
		//this way even if the window is physically suppose 800x600, and i take the ss, it thinkgs im on the 1920x1080 view
		//even though im not and it further scales down the already 800x600 view to something smaller

		sf::Vector2f rectSize = this->middlerect.getSize();
		this->middlerect.setPosition(viewCenter.x - rectSize.x / 2, viewCenter.y - rectSize.y / 2);

		//set button positions
		int xPos =static_cast<int>( viewCenter.x - backbtn.getShape().getGlobalBounds().width / 2);
		int yPos = static_cast<int>(viewCenter.y + viewSize.y / 2 * static_cast<float>(0.058));
		backbtn.set_position(xPos, yPos - 250);
		startbtn.set_position(xPos, yPos + 170);
		optionsbtn.set_position(xPos, yPos - 30);
		savegamebtn.set_position(xPos, yPos - 150);


	}
	else//does not take in factor the zoom(scaling) of the game so it must be done yet again to properly display the captured image from the window
	{
		
		
		//draw everything instead
		this->game->window.setView(pauseview);
		this->game->window.clear();

		
		this->game->window.draw(backgroundSprite);
		this->game->window.draw(background);
		this->game->window.draw(middlerect);
		backbtn.draw_button(this->game->window);
		optionsbtn.draw_button(this->game->window);
		startbtn.draw_button(this->game->window);
		savegamebtn.draw_button(this->game->window);
	}



}

void PauseMenu::update(sf::Time timePerFrame)
{


}

void PauseMenu::handleInputs()
{
	
	
}

void PauseMenu::handleResizing(sf::Event& event)
{
	//sf::FloatRect visibleArea(0, 0, static_cast<float> (event.size.width), static_cast<float>(event.size.height));
	//pauseview = sf::View(visibleArea);
	
		
	
}

void PauseMenu::handleEvents(sf::Event& event)
{
	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		
		this->game->ispaused = 0;
		mgrefference->localPassedTime.restart();
		this->game->popState();
		
	}

	if (event.type == sf::Event::MouseButtonPressed && backbtn.isMouseIn(this->game->window))
	{
		
		this->game->ispaused = 0;
		mgrefference->localPassedTime.restart();

		this->game->popState();

	}
	else 
	if (event.type == sf::Event::MouseButtonPressed && startbtn.isMouseIn(this->game->window))
	{
		this->game->ispaused = 0;
		mgrefference->setfrompause();

		this->game->popState();

	}
	else //it tries to execute code after it popped ELSE NECESSARY!!!
	if (event.type == sf::Event::MouseButtonPressed && savegamebtn.isMouseIn(this->game->window))
	{
		
		mgrefference->serializeData();
		//make smth appear to confirm

	}

}

void PauseMenu::setMGref(MainGame* ref)
{
	this->mgrefference = ref;
}


void PauseMenu::PressedBack()
{//if play pressed, push state

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && backbtn.isMouseIn(this->game->window))
	{
		this->game->ispaused = 0;
		this->game->popState();
	}


}


//###############################################################################################################################################// Respawn State Functions

RespawnState::~RespawnState()
{

}

RespawnState::RespawnState(Game* game)
	:respawnbtn(200, 50, "Respawn", 25, sf::Color::Red),
	mainmenubtn(200, 50, "Main Menu", 25, sf::Color::Red)
{	
	this->game = game;
	respawnview= game->window.getDefaultView();
	

	backgroundTexture.loadFromFile("assets/images/respawnScreen.png");
	this->background.setSize(sf::Vector2f(game->getWindowWidth(), game->getWindowHeight() ) );
	background.setTexture(&backgroundTexture);



	int xPos = static_cast<int>(respawnview.getCenter().x - respawnbtn.getShape().getGlobalBounds().width / 2);
	//int yPos = static_cast<int>(viewCenter.y + viewSize.y / 2 * static_cast<float>(0.058));

	respawnbtn.set_position(xPos, 550);
	mainmenubtn.set_position(xPos, 700);



}

void RespawnState::draw()
{	this->game->window.setView(respawnview);
	this->game->window.clear();
	this->game->window.draw(background);
	mainmenubtn.draw_button(this->game->window);
	respawnbtn.draw_button(this->game->window);


}

void RespawnState::update(sf::Time timePerFrame)
{
}

void RespawnState::handleInputs()
{
}

void RespawnState::handleResizing(sf::Event& event)
{
}

void RespawnState::handleEvents(sf::Event& event)
{

	if (event.type == sf::Event::MouseButtonPressed && respawnbtn.isMouseIn(this->game->window))
	{

		
		this->game->changeState(new MainGame(game) );


	}
	else
		if (event.type == sf::Event::MouseButtonPressed && mainmenubtn.isMouseIn(this->game->window))
		{

			this->game->popState();

		}

}
