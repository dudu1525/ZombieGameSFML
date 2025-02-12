#ifndef UIMAINGAME_H
#define UIMAINGAME_H
#include <SFML/Graphics.hpp>

class UIMainGame : public sf::Transformable, public sf::Drawable {

public:

	UIMainGame(sf::View view);
	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	

	
	sf::View view;
	void setview(sf::View view);
private:
	sf::RectangleShape rec1;
	

		
};





#endif