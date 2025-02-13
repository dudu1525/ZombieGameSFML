#include "../include/UIMainGame.h"

UIMainGame::UIMainGame(sf::View view)
{//add elements of the gui
	setview(view);

	rec1.setPosition(view.getCenter());
	rec1.setFillColor(sf::Color::Red);
	rec1.setSize(sf::Vector2f(100, 150));;

	//stamina rectangles
	staminabottom.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2-20, view.getSize().y / 2-80));
	staminabottom.setFillColor(sf::Color::Black);
	staminabottom.setSize(sf::Vector2f(160, 30));
	staminatop.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 20, view.getSize().y / 2 - 80));
	staminatop.setFillColor(sf::Color::Blue);
	staminatop.setSize(sf::Vector2f(160, 30));

	//item slots-rectangles
	slot1.setPosition(view.getCenter() + sf::Vector2f(15, 330));
	slot1.setFillColor(sf::Color(128,128,128));
	slot1.setSize(sf::Vector2f(40, 50));
	
	slot2.setPosition(view.getCenter() + sf::Vector2f(-55, 330));
	slot2.setFillColor(sf::Color(128, 128, 128));
	slot2.setSize(sf::Vector2f(40, 50));
	//item slots-images
	slot1img.setPosition(view.getCenter() + sf::Vector2f(19, 334));
	tx1.loadFromFile("assets/images/Apocalypse Character Pack/crssbw.png");
	slot1img.setTexture(&tx1);
	slot1img.setSize(sf::Vector2f(32, 42));

	slot2img.setPosition(view.getCenter() + sf::Vector2f(-51, 334));
	tx2.loadFromFile("assets/images/Apocalypse Character Pack/swrd.png");
	slot2img.setTexture(&tx2);
	slot2img.setSize(sf::Vector2f(32, 42));

}

void UIMainGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
		

	target.draw(staminabottom);
	target.draw(staminatop);

	target.draw(slot1);
	target.draw(slot2);
	target.draw(slot1img);
	target.draw(slot2img);
		
}

void UIMainGame::changestamina(int stamina,int currentstamina, sf::RenderTarget& target, sf::RenderStates states,sf::RenderWindow& window)
{
	int finallenstamina=0;
	if (currentstamina > 0)
	{
		int perc = (currentstamina * 100) / stamina;
		finallenstamina = (perc * 160) / 100;
	}
	else
		finallenstamina = 0;

	staminatop.setSize(sf::Vector2f(finallenstamina, 30));
	detectslots(window);
	draw(target, states);
	

}
void UIMainGame::detectslots(sf::RenderWindow& window)//function responsible for managing weapons ui
{
	if (selected1 == 0 && selected2 == 0)
	{
		slot1.setFillColor(sf::Color::White);
		slot2.setFillColor(sf::Color::White);
	}
	else if (selected1 == 1 && selected2 == 0)
	{
		slot1.setFillColor(sf::Color::Black);
		slot2.setFillColor(sf::Color::White);

	}
	else if (selected1 == 0 && selected2 == 1)
	{
		slot1.setFillColor(sf::Color::White);
		slot2.setFillColor(sf::Color::Black);

	}



}


void UIMainGame::setview(sf::View view)
{
	this->view = view;
}
