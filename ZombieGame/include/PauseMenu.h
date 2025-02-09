#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "States.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"



class PauseMenu :public States {

	~PauseMenu();
public:
	PauseMenu(Game* game);

	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInput();
	virtual void handleResizing(sf::Event& event);
	virtual void handleInputs(sf::Event& event);

private:
	sf::RectangleShape background;
	sf::RectangleShape middlerect;

	sf::Texture backgroundTextureimage;
	sf::Sprite backgroundSprite;
	

};




#endif
