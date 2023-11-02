#include "gameObject.hpp"

gameObject::gameObject(){

}

gameObject::~gameObject(){

}

sf::Vector2f gameObject::getPosition()
{
    return position;
}

void gameObject::setPosition(sf::Vector2f pos)
{
    position =  pos;
}
