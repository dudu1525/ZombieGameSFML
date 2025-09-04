#include "../include/Button.h"


Button::Button(int x, int y, std::string name,int size,sf::Color colour)
{
	set_button();
	button.setSize(sf::Vector2f(x, y));
	this->button_text.setString(name);
	this->button_text.setCharacterSize(size);
	this->button_text.setFillColor(sf::Color::Black);
	this->hoverColor = colour;
	font.loadFromFile("assets/fonts/arial.ttf");
	if (!font.loadFromFile("assets/fonts/arial.ttf")) {
	
		std::cerr << "Error loading font" << std::endl;
		return;
	}
	this->button_text.setFont(font);
}

void Button::set_button()
{

	button.setOutlineThickness(3);
	button.setFillColor(sf::Color::White);
	button.setOutlineColor(sf::Color::Black);
}


const sf::RectangleShape& Button::getShape() const
{
	return button;
}



void Button::set_position(int x,int y)
{
	button.setPosition(x, y);
	centerText(x,y);

	
}



void Button::draw_button(sf::RenderWindow& window)
{
		window.draw(button);     
		window.draw(button_text); 
		hover_button(window);
		
}

void Button::hover_button(sf::RenderWindow& window)
{
	sf::Vector2i bounds= sf::Mouse::getPosition(window); //get the bounds of the mouse
	sf::Vector2f boundsf(static_cast<float>(bounds.x), static_cast<float>(bounds.y));
	sf::Vector2f worldMousePos = window.mapPixelToCoords(bounds);

	sf::Vector2f bsize = button.getSize(); //get size of button rectangle
	sf::Vector2f bpos = button.getPosition();//get position of button rectangle
	if (worldMousePos.x>=bpos.x && worldMousePos.x<=bpos.x+bsize.x && worldMousePos.y >= bpos.y && worldMousePos.y <= bpos.y + bsize.y)
			button.setFillColor(hoverColor);
		else {
			button.setFillColor(sf::Color::White); // Reset button color when not hovered
		}

}

bool Button::isMouseIn(sf::RenderWindow& window)
{
	sf::Vector2i bounds = sf::Mouse::getPosition(window); //get the bounds of the mouse
	sf::Vector2f boundsf(static_cast<float>(bounds.x), static_cast<float>(bounds.y));
	sf::Vector2f worldMousePos = window.mapPixelToCoords(bounds);

	sf::Vector2f bsize = button.getSize(); //get size of button rectangle
	sf::Vector2f bpos = button.getPosition();//get position of button rectangle
	if (worldMousePos.x >= bpos.x && worldMousePos.x <= bpos.x + bsize.x && worldMousePos.y >= bpos.y && worldMousePos.y <= bpos.y + bsize.y)
			return true;
		else
			return false;
}

void Button:: centerText(int x,int y) {

	sf::Vector2f buttonSize = button.getSize();

	sf::FloatRect textBounds = button_text.getGlobalBounds();


	float x2 =x+ (buttonSize.x - textBounds.width) / 2;
	float y2 = y+(buttonSize.y - textBounds.height) / 3;

	button_text.setPosition(x2, y2);
}