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
	slot1.setFillColor(sf::Color::Black);
	slot1.setSize(sf::Vector2f(40, 50));
	
	slot2.setPosition(view.getCenter() + sf::Vector2f(-55, 330));
	slot2.setFillColor(sf::Color::Black);
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
	hoverimg(window);
	draw(target, states);
	

}
void UIMainGame::hoverimg(sf::RenderWindow& window)
{
	sf::Vector2i bounds = sf::Mouse::getPosition(window); //get the bounds of the mouse
	sf::Vector2f boundsf(static_cast<float>(bounds.x), static_cast<float>(bounds.y));
	sf::Vector2f worldMousePos = window.mapPixelToCoords(bounds);

	sf::Vector2f bsize = slot1.getSize(); //get size of button rectangle
	sf::Vector2f bpos = slot1.getPosition();//get position of button rectangle
	if (worldMousePos.x >= bpos.x && worldMousePos.x <= bpos.x + bsize.x && worldMousePos.y >= bpos.y && worldMousePos.y <= bpos.y + bsize.y)
		slot1.setFillColor(sf::Color::White);
	else {
		slot1.setFillColor(sf::Color::Black); // Reset button color when not hovered
	}

}
void UIMainGame::setview(sf::View view)
{
	this->view = view;
}
