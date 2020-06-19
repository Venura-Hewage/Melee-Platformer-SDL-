#ifndef _SDLGameObject_
#define _SDLGameObject_


#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    
    virtual ~SDLGameObject() {}
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() {}
    virtual void collision() {}

    virtual std::string type() { return "SDLGameObject"; }
    
protected:
	
    SDLGameObject();
};

#endif