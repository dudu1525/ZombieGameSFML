#ifndef UIMAINGAME_H
#define UIMAINGAME_H
#include <SFML/Graphics.hpp>

class UIMainGame : public sf::Transformable, public sf::Drawable {

public:

	UIMainGame(sf::View view);
	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void changestamina(int stamina,int currentstamina, sf::RenderTarget& target, sf::RenderStates states, sf::RenderWindow& window);

	void detectslots(sf::RenderWindow& window);

	void setbulletsvisible();
	bool& getbulletsvisib();
	sf::Text& getbulletstext();
	
	sf::View view;
	void setview(sf::View view);
	bool selected1 = 0;
	bool selected2 = 0;
	sf::RectangleShape slot1;
	sf::RectangleShape slot2;
private:
	sf::RectangleShape bullets;
	sf::RectangleShape bulletsbox;
	bool isbulletsvisible = false;
	sf::Texture bulletstext;
	sf::Text bulletsnum;
	sf::Font font;

	sf::RectangleShape staminatop;
	sf::RectangleShape staminabottom;


	sf::RectangleShape slot1img;
	sf::RectangleShape slot2img;
	sf::Texture tx1;
	sf::Texture tx2;

	
	

		
};





#endif