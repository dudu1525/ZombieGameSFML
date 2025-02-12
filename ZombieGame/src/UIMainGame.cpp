#include "../include/UIMainGame.h"

UIMainGame::UIMainGame(sf::View view)
{//add elements of the gui
	setview(view);
	rec1.setPosition(view.getCenter());
	rec1.setFillColor(sf::Color::Red);
	rec1.setSize(sf::Vector2f(100, 150));;



}

void UIMainGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rec1);
}

void UIMainGame::setview(sf::View view)
{
	this->view = view;
}
