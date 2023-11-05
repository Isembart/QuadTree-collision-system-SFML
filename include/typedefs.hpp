#pragma once
#include <memory>

class gameObject;
class quadTree;

// typedef gameObject* gameObjectPtr;
typedef std::shared_ptr<gameObject> gameObjectPtr;
typedef std::shared_ptr<quadTree> quadTreePtr;