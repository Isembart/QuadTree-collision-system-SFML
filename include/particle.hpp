#pragma once
#include "gameObject.hpp"

class particle : public gameObject
{
private:
    float size;
public:
    // particle();
    particle(sf::Vector2f position, float size);
    ~particle();
    
    virtual void draw(sf::RenderWindow &window) override;
    virtual void update() override;
};


