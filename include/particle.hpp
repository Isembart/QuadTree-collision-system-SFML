#pragma once
#include "gameObject.hpp"

class particle : public gameObject
{
private:
    
public:
    particle();
    particle(sf::Vector2f position);
    ~particle();
    
    virtual void draw(sf::RenderWindow &window) override;
    virtual void update() override;
};


