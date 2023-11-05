#include <SFML/Graphics.hpp>
#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
#include <iostream>
#include <string>

int main()
{
    auto window = sf::RenderWindow{ { 600, 600 }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    
    //initiate main quadtree
    quadTree mainQT(0,0,window.getSize().x,window.getSize().y,5);
    
    //random initial points
    // for (int i = 0; i < 10000; i++)
    // {
    //     gameObject go;
    //     sf::Vector2f vec(rand()%1920,rand()%1080);
    //     go.setPosition(vec);
    //     mainQT.insert(&go);
    // }
    
   

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            std::cout<< position.x << " "<< position.y<<std::endl;
            gameObjectPtr go = std::make_shared<gameObject>();
            go->setPosition(sf::Vector2f(position));
            mainQT.insert(go);
        }
        window.clear();
        mainQT.draw(window);
        // std::cout<<std::to_string(mainQT.getPosition().x)<<" "<< std::to_string(mainQT.getPosition().y)<<std::endl;
        window.display();
    }
}