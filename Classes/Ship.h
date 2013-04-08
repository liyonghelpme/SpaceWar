#ifndef __SHIP_H__
#define __SHIP_H__
#include "cocos2d.h"
#include "Lightning.h"
#include "Planet.h"
#include "HelloWorldScene.h"
#include "kazmath/vec3.h"
#include "kazmath/utility.h"
using namespace std;
class Planet;
class HelloWorld;
class Ship : public CCNode {
public:
    static Ship *create();
    void init();
    int type;

    int number;
    int color;
    Planet *startPlanet;
    Planet *endPlanet;
    virtual void onEnter();
    virtual void update(float dt);

    HelloWorld *logic;
    void startMove();
    void setColor(int);
    void setType(int);
private:
    CCSpriteBatchNode *back;
    float speed;
    float dir;

};
#endif
