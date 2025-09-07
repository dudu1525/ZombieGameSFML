#ifndef MAINMENU_H
#define MAINMENU_H
#include "States.h"
#include <iostream>

#include "Button.h"
#include <fstream>
//view here, has zoom 1, set to 0,0, size 1920, 1080

class MainMenu:public States {//extends states

public:
    

    virtual void draw();
    virtual void update(sf::Time timePerFrame);
    virtual void handleInputs();
    virtual void handleResizing(sf::Event& event);
    virtual void handleEvents(sf::Event& event);
    
    void init();

    void set_text();
    void PressedPlay();
    void PressedExit();
    void PressedLoad();
    sf::View menuview;

    MainMenu(Game* game);
private:
    sf::Text MenuText;
    sf::Font font;
    Button playbtn;
    Button loadbtn;
    Button exitbtn;

    sf::Texture background;
    sf::Sprite backgroundSprite;
    bool is_empty(std::ifstream& file) //returns true if the file is empty
    {
        return file.peek() == std::ifstream::traits_type::eof();
    }
    
};





#endif