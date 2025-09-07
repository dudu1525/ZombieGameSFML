#include "../include/Game.h"


#include "../include/States.h"
#include "../include/MainMenu.h"
#include "../include/MainGame.h"
#include "../include/PauseMenu.h"

Game::Game() 
	:view(sf::FloatRect(0, 0,1920, 1080)), dm("gamedb.db")
{
	window.setView(view);
	this->window.create(sf::VideoMode(1920, 1080), "ZombieGame");

	this->pushState(new MainMenu(this)); //push the main menu state with this as the parameter of the MainMenu constructor
	printf("constructor game opened");
	
}

void Game:: mainloop()//this happens for every state of the game, so the mainmenu, the maingame..etc
{//process events,handle inputs, clear, draw, set view, update, display

	while (window.isOpen())
	{
		sf::Time deltaTime = deltaClock.restart();  // Time since last frame
		timeSinceLastUpdate += deltaTime;

		processevents();
		
		if (peekState() == nullptr) continue;

		while (timeSinceLastUpdate >= timePerFrame)//(60 fps)
		{
			timeSinceLastUpdate -= timePerFrame;  
			peekState()->handleInputs(); 
			peekState()->update(timePerFrame);  
		}
		
			
		peekState()->draw(); 
		this->window.display();
	}

}


void Game::processevents()
{
	sf::Event evnt;
	States* current_state=peekState();
	while (window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			window.close();

	//	if (evnt.type == sf::Event::Resized)
	//	{
	//		peekState()->handleResizing(evnt);
	//	}
		if (peekState() != nullptr) {
			peekState()->handleEvents(evnt);
		}
		if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::F11)
		{
			if (isfullscreen == 0)
			{
				isfullscreen = 1;
				this->window.create(sf::VideoMode(1920, 1080), "ZombieGame", sf::Style::Fullscreen);
			}
			else
			{
				isfullscreen = 0;
				this->window.create(sf::VideoMode(1920, 1080), "ZombieGame");

			}

		}


	
			
	
	}

}


Game::~Game() {
	while (!this->states.empty()) popState();
}


void Game::pushState(States* state)
{
	this->states.push(state);

	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(States* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

States* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}


unsigned int Game::getWindowWidth() const {
	return window.getSize().x;
}


unsigned int Game::getWindowHeight() const {
	return window.getSize().y;
}

