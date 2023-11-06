#include <SFML/Graphics.hpp>
#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
#include "particle.hpp"
#include <iostream>
const float particleSize = 4;
const int quadTreeCapacity = 15;

void randomPoints(sf::RenderWindow &window, quadTreePtr mainQT, std::vector<gameObjectPtr> &objects){
    // random initial points
    for (int i = 0; i < 2000; i++)
    {
        sf::Vector2f vec(rand()%window.getSize().x,rand()%window.getSize().y);
        gameObjectPtr go = std::make_shared<particle>(vec,particleSize);
        mainQT->insert(go);
        objects.push_back(go);
    }
}

int main()
{
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    float fps;

    auto window = sf::RenderWindow{ { 1020, 720 }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<gameObjectPtr> objects;    
    quadTreePtr mainQT = std::make_shared<quadTree>(0,0,window.getSize().x,window.getSize().y,quadTreeCapacity);
    randomPoints(window,mainQT,objects);
    
    while (window.isOpen())
    {
        //fps 
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::cout << "fps =" << fps << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        //insert new points on mouseClick
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            gameObjectPtr go = std::make_shared<particle>(sf::Vector2f(position),particleSize);
            mainQT->insert(go); 
            objects.push_back(go);
        }
/////////////////////////////////////////////////////Update////////////////////
        mainQT = std::make_shared<quadTree>(0,0,window.getSize().x,window.getSize().y,quadTreeCapacity);
        for(auto obj : objects){
            obj->update();
            mainQT->insert(obj); //HOLY FUCK WHY DID I ADD THIS LINE
        }
//////////////////////////////////////////////DRAW/////////////////////////////
        window.clear();
        mainQT->draw(window);

        ///////////////////////////////////////////Collision Check////////////////////////
        for(gameObjectPtr obj : objects) {
            sf::Vector2f pos = obj->getPosition();
            float radius = obj->getHitboxRadius()*2;
            std::vector<gameObjectPtr> others;
            mainQT->query(sf::FloatRect(pos.x-radius,pos.y-radius,pos.x+radius,pos.y+radius),others);
            for(auto otherObj : others)
            { 
                if(obj->intersects(otherObj) && otherObj != obj){
                    //collision!
                    sf::CircleShape c1;
                    sf::Vector2f newOrigin(particleSize,particleSize);
                    c1.setRadius(particleSize);
                    c1.setOrigin(newOrigin);
                    c1.setPosition(obj->getPosition());
                    c1.setFillColor(sf::Color(255,255,255,150));                    
                    window.draw(c1);
                }
            }
            
        }

        //draw object in the objects vector
        for(auto obj : objects) {
            obj->draw(window);
        }

        window.display();

    }
}
