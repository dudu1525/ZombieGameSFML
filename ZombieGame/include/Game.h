#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <stack>

#include "TextureManager.h"
#include "DBManager.h"
#define WIDTH 150
#define HEIGHT 100
//view here, has zoom 1, set to 0,0, size 1920, 1080

class States;

class Game {
public:
	Game();
	~Game();

	void mainloop();
	
	std::stack<States*> states; //stack of states

	sf::RenderWindow window;
	sf::View view;                  //what do you see on the screen



	void pushState(States* state);
	void popState();
	void changeState(States* state);
	States* peekState();

	DatabaseManager dm;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);  //(60 FPS)
	
	
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;

private:
	void processevents();
	
	sf::Clock deltaClock;  // Clock to track elapsed time
	sf::Time timeSinceLastUpdate = sf::Time::Zero; //accumulated time in(used to make 60 fps)

public:
	bool ispaused = 0;
};
static bool isfullscreen = 0;




#endif
