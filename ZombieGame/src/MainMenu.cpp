#include "../include/MainMenu.h"


#include "../include/States.h"
#include "../include/MainGame.h"
#include <map>
#include <string>

const std::string DATAFILE= "assets/files/gamedata.dat";
 std::ifstream FILEINPUT("assets/files/gamedata.dat");

MainMenu::MainMenu(Game* game)
    :playbtn(230, 100, "NEW GAME", 30,sf::Color::Green),exitbtn(200,80,"EXIT",40,sf::Color::Cyan), loadbtn(230,100, "LOAD GAME", 30, sf::Color::Green)
{       
    this->game = game;
    printf("main menu constructor done");
    


    float xPos = game->getWindowWidth() / 2 - playbtn.getShape().getGlobalBounds().width / 2;
    float yPos = game->getWindowHeight()*0.28;
    float exity = game->getWindowHeight()-exitbtn.getShape().getGlobalBounds().height*1.2;

    playbtn.set_position(xPos, yPos);
    loadbtn.set_position(xPos, yPos+250);
    exitbtn.set_position(5,exity);

    if (!background.loadFromFile("assets/images/map/background_menu.png"))
    {
        printf("da serror loading background image\n");
    }

  backgroundSprite.setTexture(background);
   backgroundSprite.setOrigin(0, 0);
    backgroundSprite.setScale( 1920 / backgroundSprite.getLocalBounds().width,  1080 /backgroundSprite.getLocalBounds().height);

    this->set_text(); //set main menu text

    
    
}
void MainMenu::draw()
{           
   
    init();
        
    this->game->window.draw(this->backgroundSprite);
    this->game->window.draw(MenuText);
    
    exitbtn.draw_button(this->game->window);
    playbtn.draw_button(this->game->window);

    if (!is_empty(FILEINPUT))
    loadbtn.draw_button(this->game->window);
    
}

void MainMenu::update(sf::Time timePerFrame)
{
    
}

void MainMenu::handleInput()
{
   


   PressedPlay();
    PressedExit();
    if (!is_empty(FILEINPUT))
    PressedLoad();

}


void MainMenu::init()
{//reset view to initial
    menuview.setSize(1920, 1080);
    menuview.setCenter(1920 / 2, 1080 / 2);
    this->game->window.setView(menuview);
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
        MainGame* mg = new MainGame(game);
        //no deserialization needed
        //player put in a basic location, from the main gmae's constructor
        game->pushState(mg);//push the main game as the current state, with the constructor that has as parameter a Game class

       // game->pushState(new MainGame(game));
    }


}

void MainMenu::PressedExit()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && exitbtn.isMouseIn(this->game->window))
    {
        this->game->window.close();
    }

}

void MainMenu::PressedLoad()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && loadbtn.isMouseIn(this->game->window))
    {    
       // MainGame* mg = new MainGame(game);
        
        MainGame* mg = MainGame::deserializeData(game,DATAFILE);
        mg->loadPlayer();//put the player in the last position
        game->pushState(mg);//push the main game as the current state, with the constructor that has as parameter a Game class
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
    float scaleX = newWidth /background.getSize().x;
    float scaleY = newHeight / background.getSize().y;
    float scale = std::max(scaleX, scaleY); // Maintain aspect ratio
    backgroundSprite.setScale(scale, scale);
    backgroundSprite.setPosition(0, 0); // Always align to top-left

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
   
}

