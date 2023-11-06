#include <SFML/Graphics.hpp>
#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
#include "particle.hpp"
#include <iostream>
#include <string>


void randomPoints(sf::RenderWindow &window, quadTree &mainQT, std::vector<gameObjectPtr> &objects){
    // random initial points
    for (int i = 0; i < 5; i++)
    {
        // gameObjectPtr go = new gameObject();
        sf::Vector2f vec(rand()%window.getSize().x,rand()%window.getSize().y);
        gameObjectPtr go = std::make_shared<particle>(vec);
        mainQT.insert(go);
        objects.push_back(go);
    }
}

void checkRange(sf::RenderWindow &window, quadTree &mainQT)
{
    //Create a range to query object
    sf::FloatRect boundary(100,100,100,100);
    sf::RectangleShape rect;
    //convert the range to rectangleShape to draw it
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(255,0,0,255));
    rect.setOutlineThickness(3);

    //Mouse movement
    sf::Vector2 position = sf::Mouse::getPosition(window);
    boundary.left = position.x;
    boundary.top = position.y;
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    std::vector<gameObjectPtr> result = mainQT.query(boundary); 
    window.draw(rect);
    if(result.size() != 0){
        for(auto obj : result)
        { 
            sf::CircleShape circle(5);
            circle.setOrigin(sf::Vector2f(circle.getRadius(),circle.getRadius()));
            circle.setPosition(obj->getPosition()); 
            circle.setFillColor(sf::Color(255,0,0,255));
            window.draw(circle);
            
        }
    }
}

int main()
{
    auto window = sf::RenderWindow{ { 600, 600 }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<gameObjectPtr> objects;    
    quadTree mainQT(0,0,window.getSize().x,window.getSize().y,5);
    
    randomPoints(window,mainQT,objects);
    
    

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

        //insert new points on mouseClick
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            gameObjectPtr go = std::make_shared<particle>(sf::Vector2f(position));
            // gameObjectPtr go = new gameObject();
            mainQT.insert(go); 
            objects.push_back(go);
        }
/////////////////////////////////////////////////////Update////////////////////
        for(auto obj : objects){
            obj->update();
        }



//////////////////////////////////////////////DRAW/////////////////////////////
        window.clear();
        mainQT.draw(window);

        ///////////////////////////////////////////Collision Check////////////////////////
        for(auto obj : objects) {
            for (auto otherObj : objects)
            { 
                if(obj->intersects(otherObj) && otherObj != obj){
                    //collision!
                    sf::CircleShape c1,c2;
                    sf::Vector2f newOrigin(5,5);
                    c1.setRadius(5);
                    c2.setRadius(5);
                    c1.setOrigin(newOrigin);
                    c2.setOrigin(newOrigin);
                    c1.setPosition(obj->getPosition());
                    c2.setPosition(otherObj->getPosition());
                    c1.setFillColor(sf::Color(255,255,255,255));                    
                    c2.setFillColor(sf::Color(255,255,255,255));                    
                    window.draw(c1);
                    window.draw(c2);
                }
            }
            
        }


        //draw object in the objects vector
        for(auto obj : objects) {
            obj->draw(window);
        }

        //check for range
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            checkRange(window,mainQT);
        }

        window.display();
    }
}
