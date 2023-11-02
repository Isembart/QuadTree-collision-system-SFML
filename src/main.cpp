#include <SFML/Graphics.hpp>
#include "quadTree.hpp"
#include "gameObject.hpp"

#include <iostream>
#include <string>

int main()
{
    auto window = sf::RenderWindow{ { 1080u, 720u }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    
    //initiate main quadtree
    quadTree mainQT(0,0,1080,720,1);
    
   

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            mainQT.insert(new gameObject());
        }
        window.clear();
        mainQT.draw(window);
        // std::cout<<std::to_string(mainQT.getPosition().x)<<" "<< std::to_string(mainQT.getPosition().y)<<std::endl;
        window.display();
    }
}