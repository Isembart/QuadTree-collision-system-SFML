#include <SFML/Graphics.hpp>
#include "quadTree.hpp"
#include "gameObject.hpp"

#include <iostream>
#include <string>

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    
    //initiate main quadtree
    quadTree mainQT(0,0,1920,1080,5);
    
    for (int i = 0; i < 1000; i++)
    {
        gameObject go;
        sf::Vector2f vec(rand()%580,rand()%520);
        go.setPosition(vec);
        mainQT.insert(&go);
    }
    
   

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
            gameObject* go = new gameObject();
            go->setPosition(sf::Vector2f(position));
            mainQT.insert(go);
        }
        window.clear();
        mainQT.draw(window);
        // std::cout<<std::to_string(mainQT.getPosition().x)<<" "<< std::to_string(mainQT.getPosition().y)<<std::endl;
        window.display();
    }
}