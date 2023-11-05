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
    
    // random initial points
    for (int i = 0; i < 1000; i++)
    {
        gameObjectPtr go = std::make_shared<gameObject>();
        // gameObjectPtr go = new gameObject();
        sf::Vector2f vec(rand()%1920,rand()%1080);
        go->setPosition(vec);
        mainQT.insert(go);
    }
    
    //Create a range to query object
    sf::FloatRect boundary(rand()%600,rand()%600,rand()%600,rand()%600);
    sf::RectangleShape rect;
    //convert the range to rectangleShape to draw it
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(255,0,0,255));
    rect.setOutlineThickness(3);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                }
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            gameObjectPtr go = std::make_shared<gameObject>();
            // gameObjectPtr go = new gameObject();
            go->setPosition(sf::Vector2f(position));
            mainQT.insert(go); 
        }
        window.clear();
        mainQT.draw(window);
        // std::cout<<std::to_string(mainQT.getPosition().x)<<" "<< std::to_string(mainQT.getPosition().y)<<std::endl;
    
        window.draw(rect);
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            std::vector<gameObjectPtr> result = mainQT.query(boundary); 
            if(result.size() != 0){
                for(auto obj : result)
                { 
                    sf::CircleShape circle(2);
                    circle.setPosition(obj->getPosition()); 
                    circle.setFillColor(sf::Color(255,0,0,255));
                    window.draw(circle);
                }
            }
        }

        window.display();
    }
}