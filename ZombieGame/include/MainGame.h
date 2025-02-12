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
#include "UiMainGame.h"
//view reseted, zoomed 0.3, not in the upper part of the desktop
class MainGame:public States {

	~MainGame();
public:
	MainGame(Game* game);

	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInput();
	virtual void handleResizing(sf::Event& event);
	virtual void handleInputs(sf::Event& event);

	void setfrompause();

private:
	WorldMap map;  //map used for the game
	Player player;
	sf::View gameview;
	sf::View uiview;
	//UIMainGame ui;

	void moveplayerinput(sf::Time deltaTime);
	void handlemapedges();
	void handleplayeredges();

};


	static bool frompause = 0;


#endif
