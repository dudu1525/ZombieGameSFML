#ifndef MAINMENU_H
#define MAINMENU_H
#include "States.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu:public States {//extends states

public:
    

    virtual void draw();
    virtual void update(sf::Time timePerFrame);
    virtual void handleInput();
    virtual void handleResizing(sf::Event& event);
    virtual void handleInputs(sf::Event& event);
    
    void set_text();
    void PressedPlay();
    void PressedExit();
    sf::View menuview;

    MainMenu(Game* game);
private:
    sf::Text MenuText;
    sf::Font font;
    Button playbtn;
    Button exitbtn;

    
};





#endif