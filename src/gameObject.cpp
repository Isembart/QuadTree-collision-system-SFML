#include "typedefs.hpp"
#include "gameObject.hpp"
#include "math.h"

gameObject::gameObject(){

}

gameObject::~gameObject(){

}

sf::Vector2f gameObject::getPosition()
{
    return position;
}

void gameObject::draw(sf::RenderWindow &window)
{
    
}

void gameObject::update()
{
}

void gameObject::setPosition(sf::Vector2f pos)
{
    position =  pos;
}

bool gameObject::intersects(gameObjectPtr other)
{
    return hitboxRadius >= sqrt((other->getPosition().x - position.x)*(other->getPosition().x - position.x) + (other->getPosition().y - position.y)*(other->getPosition().y - position.y));
}
