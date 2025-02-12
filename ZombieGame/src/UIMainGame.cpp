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



}

void UIMainGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
		

	target.draw(staminabottom);
	target.draw(staminatop);
}

void UIMainGame::changestamina(int stamina,int currentstamina, sf::RenderTarget& target, sf::RenderStates states)
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
	draw(target, states);
	

}

void UIMainGame::setview(sf::View view)
{
	this->view = view;
}
