#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>


class Button {
public:
	
	Button(int x,int y,std::string name,int size,sf::Color colour);
	
	void set_position(int x,int y);
	void draw_button(sf::RenderWindow& window);//draw shape+text

	bool isMouseIn(sf::RenderWindow& window);

	const sf::RectangleShape& getShape() const;

private:
	void centerText(int x,int y);
	void hover_button(sf::RenderWindow& window);
	void set_button();

	sf::RectangleShape button;
	sf::Text button_text;
	sf::Font font; //init here cuz else it gets destroyed
	sf::Color hoverColor;

};







#endif
