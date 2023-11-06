#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
quadTree::quadTree()
{
    divided=false;
    capacity=9999;
}

quadTree::quadTree(float x, float y, float a, float b,int _capacity)
{
    // rect.setSize(sf::Vector2f(x,y));
    boundary.left=x;
    boundary.top=y;
    boundary.width=a;
    boundary.height=b;
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
    //construct a recntagle shape from sf::Rect
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(255,255,255,255));
    rect.setOutlineThickness(1); 

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

void quadTree::insert(gameObjectPtr object)
{
    if(!boundary.contains(object->getPosition())){
        return;
    }
    if(objects.size() < capacity) {
        objects.push_back(object);
    } 
    else {
        if(divided==false) {
            subdivide();
        }
        //once the quadTree has subdivided it passes the object to its children
        nw->insert(object);
        sw->insert(object);
        ne->insert(object);
        se->insert(object);
    }
}

//subidives the quadtree 
void quadTree::subdivide()
{
    divided = true;
    //the quadtrees are named as the poles
    //eg: southwest = se
    nw = std::make_shared<quadTree>(boundary.left, boundary.top, boundary.width/2, boundary.height/2, capacity);
    sw = std::make_shared<quadTree>(boundary.left, boundary.top+boundary.height/2, boundary.width/2, boundary.height/2, capacity);
    ne = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top, boundary.width/2, boundary.height/2, capacity);
    se = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top+ boundary.height/2, boundary.width/2, boundary.height/2, capacity);
}

std::vector<gameObjectPtr> quadTree::query(sf::FloatRect range)
{
    std::vector<gameObjectPtr> found;
    found.clear();
    if(range.left - range.width > boundary.left + boundary.width || range.left + range.width < boundary.left - boundary.width || range.top - range.height > boundary.top + boundary.height || range.top + range.height < boundary.top - boundary.height ) {
        return found;
    }
    for (int i = 0; i < objects.size(); i++)
    {
        gameObjectPtr obj = objects.at(i);
        if(range.contains(obj->getPosition())){
            found.push_back(obj);
        }
    }   
    if(divided){
        // v1.insert(v1.end(), v2.begin(), v2.end());
        std::vector<gameObjectPtr> fnw = nw->query(range);
        std::vector<gameObjectPtr> fne = ne->query(range);
        std::vector<gameObjectPtr> fsw = sw->query(range);
        std::vector<gameObjectPtr> fse = se->query(range);
        found.reserve( fnw.size() + fne.size() + fsw.size() + fse.size()); // preallocate memory
        found.insert(found.end(),fnw.begin(),fnw.end());
        found.insert(found.end(),fne.begin(),fne.end());
        found.insert(found.end(),fsw.begin(),fsw.end());
        found.insert(found.end(),fse.begin(),fse.end());
    }
    return found;
}