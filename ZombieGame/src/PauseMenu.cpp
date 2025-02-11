#include "../include/PauseMenu.h"
//do something here
//do something here 2
PauseMenu::~PauseMenu()
{
}
//got zoomed in view, reset by setting to 3.3 view and send it forward
//when popping the view, it gets updated to the x0.3 one

PauseMenu::PauseMenu(Game* game, MainGame* mg)
	:backbtn(200, 50, "Back to Game", 25, sf::Color::Green),  startbtn(200, 50, "Main Menu", 25, sf::Color::Green), optionsbtn(200, 50, "Options", 25, sf::Color::Green)
{
	printf("\nconstructor of pause menu: done\n");
	this->game = game;
	this->background.setSize(sf::Vector2f(static_cast<float> (game->getWindowWidth()), static_cast<float>(game->getWindowHeight()) +70 ));
	sf::Vector2f coords(400, 600);
	this->middlerect.setSize(coords);

	this->background.setFillColor(sf::Color(0, 0, 0, 100));

	//set main 
	middlerecttext.setSmooth(1);
	middlerecttext.loadFromFile("assets/images/menutexture.jpg");
	middlerect.setTexture(&middlerecttext);

	//initialize all buttons
	sf::View currentView = this->game->window.getView();
	sf::Vector2f viewCenter = currentView.getCenter();
	
	backbtn.set_position(viewCenter.x, viewCenter.y);
	startbtn.set_position(viewCenter.x, viewCenter.y);
	optionsbtn.set_position(viewCenter.x, viewCenter.y);
		//create a scaling component into button
	//and for button border

	//set main game
	this->setMGref(mg);
}

void PauseMenu::draw()
{

	//this happens exactly once, then it just gets drawn
	if (this->game->ispaused == 0)
	{
		sf::View currentView = this->game->window.getView();
		currentView.zoom(3.33);
		pauseview = currentView;
		this->game->window.setView(currentView);
		sf::Vector2f viewCenter = currentView.getCenter();
		sf::Vector2f viewSize = currentView.getSize();
		
		//center the background on the view
		this->background.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
		

		this->game->ispaused = 1;

		this->game->window.draw(background);
		
		backgroundTextureimage.create(this->game->window.getSize().x, this->game->window.getSize().y);
		backgroundTextureimage.update(this->game->window);
		backgroundSprite.setTexture(backgroundTextureimage);

	}
	else//does not take in factor the zoom(scaling) of the game so it must be done yet again to properly display the captured image from the window
	{
		
		
		//draw everything instead

		this->game->window.clear();
		this->game->window.draw(backgroundSprite);
		this->game->window.draw(middlerect);
		backbtn.draw_button(this->game->window);
		optionsbtn.draw_button(this->game->window);
		startbtn.draw_button(this->game->window);

	}



}

void PauseMenu::update(sf::Time timePerFrame)
{
	pauseview = this->game->window.getView();
	sf::Vector2f viewCenter = pauseview.getCenter();
	sf::Vector2f viewSize = pauseview.getSize();

	sf::Vector2u textureSize = backgroundTextureimage.getSize();


	float scaleX = viewSize.x / static_cast<float>(textureSize.x);//scale accordingly, current size/gotten,untransformed size
	float scaleY = viewSize.y / static_cast<float>(textureSize.y);
	backgroundSprite.setScale(scaleX, scaleY);

	//set rectangles position
	backgroundSprite.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
	sf::Vector2f rectSize = this->middlerect.getSize();
	this->middlerect.setPosition(viewCenter.x - rectSize.x / 2, viewCenter.y - rectSize.y / 2);

	//set button positions
	float xPos = viewCenter.x  - backbtn.getShape().getGlobalBounds().width / 2;
	float yPos = viewCenter.y + viewSize.y /2 * 0.058;
	backbtn.set_position(xPos, yPos-250);
	startbtn.set_position(xPos, yPos+170 );
	optionsbtn.set_position(xPos, yPos - 100);
	
		
	
}

void PauseMenu::handleInput()
{
	//PressedBack();
	//PressedMenu();
	
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

	if (event.type == sf::Event::MouseButtonPressed && backbtn.isMouseIn(this->game->window))
	{
		this->game->ispaused = 0;
		this->game->popState();

	}
	else
	if (event.type == sf::Event::MouseButtonPressed && startbtn.isMouseIn(this->game->window))
	{
		this->game->ispaused = 0;
		mgrefference->setfrompause();

		this->game->popState();

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
void PauseMenu::PressedMenu()
{//if play pressed, push state

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && startbtn.isMouseIn(this->game->window))
	{
	}


}