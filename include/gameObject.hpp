#pragma once
#include "SFML/Graphics.hpp"
#include "typedefs.hpp"

class gameObject
{
protected:
    sf::Vector2f position;
    float hitboxRadius = 3;
public:
    gameObject();
    ~gameObject();

    sf::Vector2f getPosition(); 
    virtual void draw(sf::RenderWindow &window);
    virtual void update();
    void setPosition(sf::Vector2f position); 
    bool intersects(gameObjectPtr other);
};
