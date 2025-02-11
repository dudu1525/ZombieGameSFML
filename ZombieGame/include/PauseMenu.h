#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "States.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "MainGame.h"


class PauseMenu :public States {

	~PauseMenu();
public:
	PauseMenu(Game* game, MainGame* mg);

	virtual void draw();
	virtual void update(sf::Time timePerFrame);
	virtual void handleInput();
	virtual void handleResizing(sf::Event& event);
	virtual void handleInputs(sf::Event& event);

	void setMGref(MainGame* ref);

	void PressedBack();

	void PressedMenu();


private:
	sf::RectangleShape background; //transparentish black rectangle over what was on the screen
	sf::RectangleShape middlerect;	//middle element

	sf::View pauseview;

	sf::Texture backgroundTextureimage; //texture that takes the window's image at one point
	sf::Sprite backgroundSprite; //sprite that ues the backgroundtextureimage

	sf::Texture middlerecttext;

	Button backbtn;
	Button startbtn;
	Button optionsbtn;

	MainGame* mgrefference;

};




#endif
