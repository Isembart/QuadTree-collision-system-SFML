#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
quadTree::quadTree()
{
    divided=false;
    capacity=9999;
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
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));

    objects.clear();

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


    //draw points
    for (int i = 0; i < objects.size(); i++)
    {
        sf::CircleShape circle;
        circle.setPosition(objects.at(i)->getPosition());
        circle.setRadius(1);
        window.draw(circle);
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

    // nw = new quadTree(rect.getSize().x/2,rect.getSize().y/2,capacity);
    nw = std::make_shared<quadTree>(boundary.left, boundary.top, boundary.width/2, boundary.height/2, capacity);
     
    nw->getRect()->setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 256,255)); 

    sw = std::make_shared<quadTree>(boundary.left, boundary.top+boundary.height/2, boundary.width/2, boundary.height/2, capacity);
    // sw->getRect()->setPosition(getPosition()+sf::Vector2f(0,rect.getSize().y/2));
    sw->getRect()->setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 256,255)); 

    ne = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top, boundary.width/2, boundary.height/2, capacity);
    // ne->getRect()->setPosition(getPosition()+sf::Vector2f(rect.getSize().x/2,0));
    ne->getRect()->setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 2560,255)); 

    se = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top+ boundary.height/2, boundary.width/2, boundary.height/2, capacity);
    // se->getRect()->setPosition(getPosition()+sf::Vector2f(rect.getSize().x/2,rect.getSize().y/2));
    se->getRect()->setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 256,100)); 
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
        if(range.contains(objects.at(i)->getPosition())){
            found.push_back(objects.at(i));
        }
    }   
    if(divided){
        // v1.insert(v1.end(), v2.begin(), v2.end());
        auto fnw = nw->query(range);
        auto fne = ne->query(range);
        auto fsw = sw->query(range);
        auto fse = se->query(range);
        found.reserve( fnw.size() + fne.size() + fsw.size() + fse.size()); // preallocate memory
        found.insert(found.end(),fnw.begin(),fnw.end());
        found.insert(found.end(),fne.begin(),fne.end());
        found.insert(found.end(),fsw.begin(),fsw.end());
        found.insert(found.end(),fse.begin(),fse.end());
    }
    return found;
}