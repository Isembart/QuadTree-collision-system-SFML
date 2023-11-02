#pragma once
#include "SFML/Graphics.hpp"

class gameObject
{
private:
    sf::Vector2f position;
public:
    gameObject();
    ~gameObject();

    sf::Vector2f getPosition(); 
    void setPosition(sf::Vector2f position); 
};
