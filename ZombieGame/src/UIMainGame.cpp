#include "../include/UIMainGame.h"

UIMainGame::UIMainGame(sf::View view)
{//add elements of the gui
	setview(view);


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


	//bullets
	bulletstext.loadFromFile("assets/images/Apocalypse Character Pack/bullets.png");
	bullets.setTexture(&bulletstext);
	bullets.setSize(sf::Vector2f(96, 50));
	bullets.setPosition(view.getCenter() + sf::Vector2f(490 - 120, -445));
	bulletsbox.setSize(sf::Vector2f(120, 60));
	bulletsbox.setPosition(view.getCenter()+sf::Vector2f(500-120,-450));
	bulletsbox.setFillColor(sf::Color::Black);
	bulletsnum.setString("18/18");
	bulletsnum.setPosition(view.getCenter() + sf::Vector2f(565 - 120, -432));
	bulletsnum.setCharacterSize(18);
	font.loadFromFile("assets/fonts/arial.ttf");
	bulletsnum.setFont(font);

	//health
	healthbottom.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 20, view.getSize().y / 2 - 40));
	healthbottom.setFillColor(sf::Color::Black);
	healthbottom.setSize(sf::Vector2f(160, 30));
	healthtop.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2 - 20, view.getSize().y / 2 - 40));
	healthtop.setFillColor(sf::Color::Red);
	healthtop.setSize(sf::Vector2f(160, 30));
}

void UIMainGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
		

	target.draw(staminabottom);
	target.draw(staminatop);

	target.draw(healthbottom);
	target.draw(healthtop);

	target.draw(slot1);
	target.draw(slot2);
	target.draw(slot1img);
	target.draw(slot2img);
	if (isbulletsvisible)
	{
		target.draw(bulletsbox);
		target.draw(bullets);
		target.draw(bulletsnum);
	}
	
		
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
void UIMainGame::changehealth(int health, int maxhealth)
{
	int finalhealth = 0;
	if (health > 0)
	{//perc not necessary as health is 100, so *100/100 makes no sense
		finalhealth = (health * 160) / 100;
	}
	else
		finalhealth = 0;
	healthtop.setSize(sf::Vector2f(finalhealth, 30));


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

void UIMainGame::setbulletsvisible()
{
	isbulletsvisible = !isbulletsvisible;
}

bool& UIMainGame::getbulletsvisib()
{
	return isbulletsvisible;
}

sf::Text& UIMainGame::getbulletstext()
{
	return this->bulletsnum;
}


void UIMainGame::setview(sf::View view)
{
	this->view = view;
}
