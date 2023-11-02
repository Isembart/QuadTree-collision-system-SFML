#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class gameObject;

class quadTree
{
private:
    // sf::Vector2f size;
    sf::RectangleShape rect;
    sf::FloatRect boundary;
    int capacity;
    std::vector<gameObject*> objects; 
    bool divided;

    //child quadTrees, remains NULL till division
    quadTree* nw;
    quadTree* ne;
    quadTree* sw;
    quadTree* se;
public:
    //used to make empty quadtree objects available in the parent quadtree before subdivision
    quadTree();
    // quadTree(sf::Vector2f size,int capacity);
    quadTree(float x,float y, float a, float b, int capacity);
    ~quadTree();

    void subdivide();
    void draw(sf::RenderWindow& window);
    void insert(gameObject* object);

    const sf::Vector2f getPosition();
    sf::FloatRect* getBoundary();
    sf::RectangleShape* getRect();

};