#include "quadTree.hpp"
#include "gameObject.hpp"

#include <iostream>
#include <string>

quadTree::quadTree()
{
    divided=false;
    capacity=1;
}

// quadTree::quadTree(sf::Vector2f _size, int _capacity)
// {
//     // size = _size;
//     rect.setSize(_size);
//     //capacity
//     capacity = _capacity;

//     divided=false;
// }

quadTree::quadTree(float x, float y, float a, float b,int _capacity)
{
    // rect.setSize(sf::Vector2f(x,y));
    boundary.left=x;
    boundary.top=y;
    boundary.width=a;
    boundary.height=b;

    //construct a recntagle shape from sf::Rect
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    // rect.setPosition(sf::Vector2f(boundary.width - boundary.left, boundary.height - boundary.top));
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    // rect.setPosition(sf::Vector2f(0,0));

    //capacity
    capacity = _capacity;
    divided=false;
}

quadTree::~quadTree()
{
}

const sf::Vector2f quadTree::getPosition()
{
    return rect.getPosition();
}

sf::RectangleShape* quadTree::getRect()
{
    return &rect;
}

sf::FloatRect* quadTree::getBoundary()
{
    return &boundary;
}
void quadTree::draw(sf::RenderWindow &window)
{
    window.draw(rect);
    // window.draw(rect);   
    if(divided){
        //draw the child quadTrees
        ne->draw(window);
        nw->draw(window);
        se->draw(window);
        sw->draw(window);
    }
}

void quadTree::insert(gameObject* object)
{
    if(objects.size() < capacity) {
        objects.push_back(object);
    } else{
        std::cout << "Subdividing!!@!" << std::endl;
        subdivide();
    }
}

//subidives the quadtree 
void quadTree::subdivide()
{
    divided = true;
    //the quadtrees are named as the poles
    //eg: southwest = se

    // nw = new quadTree(rect.getSize().x/2,rect.getSize().y/2,capacity);
    nw = new quadTree(boundary.left, boundary.top, boundary.width/2, boundary.height/2, capacity);
    nw->getRect()->setPosition(getPosition());
    nw->getRect()->setFillColor(sf::Color(0,100,0,100)); 

    sw = new quadTree(boundary.left, boundary.top/2, boundary.width, boundary.height/2, capacity);
    sw->getRect()->setPosition(getPosition()+sf::Vector2f(0,rect.getSize().y/2));
    sw->getRect()->setFillColor(sf::Color(255,0,0,100)); 

    ne = new quadTree(boundary.left + boundary.width/2, boundary.top, boundary.width/2, boundary.height/2, capacity);
    ne->getRect()->setPosition(getPosition()+sf::Vector2f(rect.getSize().x/2,0));
    ne->getRect()->setFillColor(sf::Color(255,100,0,100)); 

    se = new quadTree(boundary.width/2, boundary.height/2, boundary.width/2, boundary.height/2, capacity);
    se->getRect()->setPosition(getPosition()+sf::Vector2f(rect.getSize().x/2,rect.getSize().y/2));
    se->getRect()->setFillColor(sf::Color(255,255,0,100)); 
}

