#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Game.h"
#include "include/DBManager.h"

int main()
{
    Game game;
   // DatabaseManager dm("gamedb.db");
    //if (!dm.createTable()) {
       // std::cerr << "Failed to create table!" << std::endl;
      //  return -1;
    //}

    // Step 3: Insert data into the table
   // if (!dm.insertData(3100, 1700)) {
      //  std::cerr << "Failed to insert data!" << std::endl;
     //   return -1;
    //}
   // dm.queryData();

    
    game.mainloop();
    
    

}





//whule is done==false, contained in the update window

//while (!game.GetWindow()->IsDone()) {
    // Game loop.


  //  game.Update();
  //  game.Render();

//}








/*int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ZombieGame");
    sf::Vector2f targetSize(1920.0f, 1080.0f);
    sf::Texture menu_background;
    if (!menu_background.loadFromFile("background_menu.png"))
    {
        printf("error loading background image\n");
    }
    menu_background.loadFromFile("background_menu.png");
   sf:: Sprite sprite;
   sprite.setTexture(menu_background);  
   sprite.setOrigin(0,0);
   sprite.setScale(
       targetSize.x / sprite.getLocalBounds().width,
       targetSize.y / sprite.getLocalBounds().height);


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
      
        window.draw(sprite);
        window.display();
    }

    return 0;
}

*/