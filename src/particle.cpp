#include "particle.hpp"

particle::particle()
{
}

particle::particle(sf::Vector2f position)
{
    setPosition(position);
}

particle::~particle()
{
}

void particle::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(255,255,255,100));
    circle.setPosition(position);
    circle.setRadius(3);
    circle.setOrigin(sf::Vector2f(circle.getRadius(),circle.getRadius()));
    window.draw(circle);
}

void particle::update()
{
    position += sf::Vector2f(rand()%3-1,rand()%3-1);
}
