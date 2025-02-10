#include "../include/MainMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/States.h"
#include "../include/MainGame.h"
#include <map>
#include <string>

MainMenu::MainMenu(Game* game)
    :playbtn(230, 100, "PLAY", 50,sf::Color::Green),exitbtn(200,80,"EXIT",40,sf::Color::Cyan)
{       
    this->game = game;
    printf("main menu constructor done");
    


    float xPos = game->getWindowWidth() / 2 - playbtn.getShape().getGlobalBounds().width / 2;
    float yPos = game->getWindowHeight()*0.28;
    float exity = game->getWindowHeight()-exitbtn.getShape().getGlobalBounds().height*1.2;

    playbtn.set_position(xPos, yPos);
    exitbtn.set_position(5,exity);

    if (!game->background.loadFromFile("assets/images/map/background_menu.png"))
    {
        printf("error loading background image\n");
    }
   //game->backgroundSprite.setTexture(game->texmgr.getRef("backgroundmenu")); //probably the load textures function isnt done as the mainmenu constructor is done first

   game->background.loadFromFile("assets/images/map/background_menu.png");
   game->backgroundSprite.setTexture(game->background);
    game->backgroundSprite.setOrigin(0, 0);
    game->backgroundSprite.setScale( 1920 / game->backgroundSprite.getLocalBounds().width,  1080 / game->backgroundSprite.getLocalBounds().height);

    this->set_text(); //set main menu text

  
    
}
void MainMenu::draw()
{
    

    this->game->window.clear(sf::Color::Red);
    this->game->window.draw(this->game->backgroundSprite);
    this->game->window.draw(MenuText);
    
    exitbtn.draw_button(this->game->window);
    playbtn.draw_button(this->game->window);
    return;
}

void MainMenu::update(sf::Time timePerFrame)
{
    
}

void MainMenu::handleInput()
{
   


   PressedPlay();
    PressedExit();

}



void MainMenu::set_text()
{
    
    font.loadFromFile("assets/fonts/arial.ttf");
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
      
        std::cerr << "Error loading font" << std::endl;
        return;
    }
    sf::Vector2u windowSize = game->window.getSize();
    unsigned int windowWidth = windowSize.x;
    unsigned int windowHeight = windowSize.y;

    MenuText.setString("Reason 2 Die: 2D");
    MenuText.setFont(font);
    MenuText.setCharacterSize(60); // Optional: set character size
    MenuText.setFillColor(sf::Color::Cyan);
    MenuText.setPosition(windowWidth/2-MenuText.getGlobalBounds().width / 2, windowHeight/10);


}

void MainMenu::PressedPlay()
{//if play pressed, push state

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && playbtn.isMouseIn(this->game->window))
    {
        game->pushState(new MainGame(game));//push the main game as the current state, with the constructor that has as parameter a Game class
    }


}

void MainMenu::PressedExit()
{
    //if exit is pressed, window closes
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && exitbtn.isMouseIn(this->game->window))
    {
        this->game->window.close();
    }

}

void MainMenu::handleResizing(sf::Event& event) {
    float newWidth = static_cast<float>(event.size.width);
    float newHeight = static_cast<float>(event.size.height);

    // Update the view and center it properly
    menuview.setSize(newWidth, newHeight);
    menuview.setCenter(newWidth / 2, newHeight / 2);
    this->game->window.setView(menuview);

    // Correct background scaling to always fit
    float scaleX = newWidth / game->background.getSize().x;
    float scaleY = newHeight / game->background.getSize().y;
    float scale = std::max(scaleX, scaleY); // Maintain aspect ratio
    game->backgroundSprite.setScale(scale, scale);
    game->backgroundSprite.setPosition(0, 0); // Always align to top-left

    // Reposition Menu Text
    MenuText.setPosition(newWidth / 2 - MenuText.getGlobalBounds().width / 2, newHeight / 10);

    // Reposition Buttons to be centered correctly
    float playX = newWidth / 2 - playbtn.getShape().getGlobalBounds().width / 2;
    float playY = newHeight * 0.28;
    float exitY = newHeight - exitbtn.getShape().getGlobalBounds().height * 1.2;

    playbtn.set_position(playX, playY);
    exitbtn.set_position(5, exitY);
}


void MainMenu::handleInputs(sf::Event& event)
{

    //if (event.type == sf::Event::MouseButtonPressed && playbtn.isMouseIn(this->game->window))
    //{
  //      game->pushState(new MainGame(game));//push the main game as the current state, with the constructor that has as parameter a Game class


//    }
}

