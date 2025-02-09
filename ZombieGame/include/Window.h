#ifndef Window_h
#define Window_h

#include <iostream>
#include <SFML/Graphics.hpp>


class Window {
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size); //constructors of the window class
	~Window();

	void BeginDraw(); // Clear the window.
	void EndDraw(); // Display the changes.
	void Update();//update windows
	bool IsDone();//check if updating is done
	
	sf::Vector2u GetWindowSize();
	
	void Draw(sf::Drawable& l_drawable); //draw on screen
private:
	void Setup(const std::string& l_title,const sf::Vector2u& l_size);
	void Destroy();
	void Create();
	
	//private values, encapsulated
	sf::RenderWindow m_window;    //main window
	
	sf::Vector2u m_windowSize;   //window size
	std::string m_windowTitle;   //window title
	bool m_isDone;
	
};

#endif