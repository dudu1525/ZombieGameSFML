#ifndef STATES_H
#define STATES_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stack>


class States {//superclass that has the following methods

public:
    Game* game=nullptr;//link game to game states
    virtual void draw() = 0;
    virtual void update(sf::Time timePerFrame) = 0; //added time to input
    virtual void handleInputs() = 0;
    virtual void handleResizing(sf::Event& event) = 0;
    virtual void handleEvents(sf::Event& event) = 0;

};




#endif