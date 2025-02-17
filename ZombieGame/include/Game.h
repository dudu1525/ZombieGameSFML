#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include "TextureManager.h"
#include "DBManager.h"
//view here, has zoom 1, set to 0,0, size 1920, 1080

class States;

class Game {
public:
	Game();
	~Game();

	void mainloop();
	static int maxn;
	std::stack<States*> states; //stack of states

	sf::RenderWindow window;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::View view;                  //what do you see on the screen

	//sf::Texture player;
	//sf::Sprite players;

	TextureManager texmgr;
	void pushState(States* state);
	void popState();
	void changeState(States* state);
	States* peekState();
	DatabaseManager dm;
	const sf::Time time = sf::seconds(1.0f / 60.0f);

	
	
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;

private:
	void loadTextures();

	//void handleWindowResize(sf::Event& event);
	
	void processevents();
	

	sf::Clock deltaClock;  // Clock to track elapsed time
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);  // Fixed time step (60 FPS)
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

public:
	int ispaused = 0;
};

static int maxn = 9999;
static bool isfullscreen = 0;




#endif
