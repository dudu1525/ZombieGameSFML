#ifndef STATES_H
#define STATES_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stack>


class States {//superclass that has the following methods

public:
    Game* game;//link game to game states
    virtual void draw() = 0;
    virtual void update(sf::Time timePerFrame) = 0; //added time to input
    virtual void handleInput() = 0;
    virtual void handleResizing(sf::Event& event) = 0;
    virtual void handleInputs(sf::Event& event) = 0;

};




#endif