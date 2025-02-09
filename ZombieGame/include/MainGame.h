#ifndef MAINGAME_H
#define MAINGAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "States.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "WorldMap.h"
#include "Player.h"

class MainGame:public States {

	~MainGame();
public:
	MainGame(Game* game);

	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInput();
	virtual void handleResizing(sf::Event& event);
	virtual void handleInputs(sf::Event& event);

private:
	WorldMap map;  //map used for the game
	Player player;

	void moveplayerinput(sf::Time deltaTime);
	void handlemapedges();
	void handleplayeredges();

};




#endif