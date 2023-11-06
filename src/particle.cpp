#include "particle.hpp"


particle::particle(sf::Vector2f position, float _size)
{
    setPosition(position);
    setHitboxRadius(_size);
    size = _size;
}

particle::~particle()
{
}

void particle::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(255,255,255,100));
    circle.setPosition(position);
    circle.setRadius(size);
    circle.setOrigin(sf::Vector2f(circle.getRadius(),circle.getRadius()));
    window.draw(circle);
}

void particle::update()
{
    position += sf::Vector2f(rand()%3-1,rand()%3-1);
}
