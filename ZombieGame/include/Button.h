#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>



class Button {
public:
	Button(int x,int y,int x2,int y2);
	Button(int x,int y,std::string name,int size,sf::Color colour);
	~Button();

	
	void set_button();
	void set_position(int x,int y);
	void draw_button(sf::RenderWindow& window);//draw shape+text
	void hover_button(sf::RenderWindow& window);

	bool isMouseIn(sf::RenderWindow& window);

	const sf::RectangleShape& getShape() const;
	const sf::Text& getText() const;
private:
	void centerText(int x,int y);

	sf::RectangleShape button;
	sf::Text button_text;
	sf::Font font; //init here cuz else it gets destroyed
	sf::Color hoverColor;

};







#endif
