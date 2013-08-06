#ifndef __PLANET_H__
#define __PLANET_H__
#include "cocos2d.h"
#include "Lightning.h"
#include "kazmath/vec3.h"
#include "kazmath/utility.h"
#include "Ship.h"
#include "Number.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class Ship;
class HelloWorld;
class Planet : public CCNode {
public:
    static Planet *create(float);
    int type;
    bool init(float);
    int shipNum;
    int color;
    int productRate;
    void setColor(int);
    void setType(int);
    virtual void onEnter();
    virtual void update(float dt);
    float radius;
    int maxShip;
    bool checkIn(float x, float y);
    void sendShip(int, Planet *);
    void shipArrive(Ship*);
    HelloWorld *logic;
private:
    CCNode *back;
    float passTime;
    Number *number;

};
#endif
