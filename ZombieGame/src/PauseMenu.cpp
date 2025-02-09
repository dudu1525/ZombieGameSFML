#include "../include/PauseMenu.h"
//do something here
PauseMenu::~PauseMenu()
{
}
//get the current view with what it has, draw it then draw the black screen?

PauseMenu::PauseMenu(Game* game)
{
	printf("\nconstructor of pause menu: done\n");
	this->game = game;
	this->background.setSize(sf::Vector2f(static_cast<float> (game->getWindowWidth()), static_cast<float>(game->getWindowHeight())  ));
	sf::Vector2f coords(160, 220);
	this->middlerect.setSize(coords);
	this->middlerect.setFillColor(sf::Color::Black);
	//this->background.setFillColor(sf::Color::Red);
	this->background.setFillColor(sf::Color(0, 0, 0, 100));
	
}

void PauseMenu::draw()
{
	//draw other elements outside and display them? or abandon the greying out of the background and just put a rectangle in the middle.

	if (this->game->ispaused == 0)
	{
		sf::View currentView = this->game->window.getView();
		sf::Vector2f viewCenter = currentView.getCenter();
		sf::Vector2f viewSize = currentView.getSize();
		//center the background on the view
		this->background.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
		sf::Vector2f rectSize = this->middlerect.getSize();
		this->middlerect.setPosition(viewCenter.x - rectSize.x / 2, viewCenter.y - rectSize.y / 2);

		this->game->ispaused = 1;

		this->game->window.draw(background);
		this->game->window.draw(middlerect);
		backgroundTextureimage.create(this->game->window.getSize().x, this->game->window.getSize().y);
		backgroundTextureimage.update(this->game->window);
		backgroundSprite.setTexture(backgroundTextureimage);

		this->game->window.display();
	}
	else//does not take in factor the zoom(scaling) of the game so it must be done yet again to properly display the captured image from the window
	{
		sf::View currentView = this->game->window.getView();
		sf::Vector2f viewCenter = currentView.getCenter();
		sf::Vector2f viewSize = currentView.getSize();

		sf::Vector2u textureSize = backgroundTextureimage.getSize();

		float scaleX = viewSize.x / static_cast<float>(textureSize.x);//scale accordingly, current size/gotten,untransformed size
		float scaleY = viewSize.y / static_cast<float>(textureSize.y);
		backgroundSprite.setScale(scaleX, scaleY);
		backgroundSprite.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
		


		this->game->window.clear();
		this->game->window.draw(backgroundSprite);
		

	}



}

void PauseMenu::update(sf::Time timePerFrame)
{
	
		
	
}

void PauseMenu::handleInput()
{
	
}

void PauseMenu::handleResizing(sf::Event& event)
{ 
}

void PauseMenu::handleInputs(sf::Event& event)
{
	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		printf("handled esc\n");
		this->game->ispaused = 0;
		this->game->popState();
		
	}
}


