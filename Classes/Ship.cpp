#include "Ship.h"
#include "math.h"
#include "stdlib.h"
#include "shape.h"

Ship *Ship::create() {
    Ship *pRet = new Ship();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Ship::setType(int t) {
    type = t;
    makeShape(type, back);
}
void Ship::init() {
    type = random()%3;

    back = CCSpriteBatchNode::create("edge.png");
    addChild(back);
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    back->setBlendFunc(blendFunc);
    
    speed = 80;
}
void Ship::onEnter() {
    CCNode::onEnter();
    scheduleUpdate();
}
void Ship::update(float dt) {
    float dist = dt*speed;
    CCPoint pos = getPosition();
    CCPoint end = endPlanet->getPosition();
    if(sqrt((pos.x-end.x)*(pos.x-end.x)+(pos.y-end.y)*(pos.y-end.y)) <= endPlanet->radius) {
        logic->shipArrive(this);
    } else {
        float dx = dist*cos(dir);
        float dy = dist*sin(dir);
        pos.x += dx;
        pos.y += dy;
        setPosition(pos);
    }
}
void Ship::startMove() {
    setPosition(startPlanet->getPosition());
    CCLog("startPosition %f %f", startPlanet->getPosition().x, startPlanet->getPosition().y);

    CCPoint start = startPlanet->getPosition();
    CCPoint end = endPlanet->getPosition();
    
    float dx = end.x-start.x;
    float dy = end.y-start.y;

    float theta = atan2(dx, dy);
    theta = theta/kmPI*180;//deg
    CCLog("rotation deg %f", theta);
    setRotation(theta);

    dir = atan2(dy, dx);
}

void Ship::setColor(int c) {
    color = c;
    CCArray *edge = back->getChildren();
    for(unsigned int i = 0; i < edge->count(); i++) {
        if(c == 0)
            ((CCSprite*)edge->objectAtIndex(i))->setColor(ccc3(255, 0, 0));
        else if(c == 1)
            ((CCSprite*)edge->objectAtIndex(i))->setColor(ccc3(0, 0, 255));
        else if(c == 2)
            ((CCSprite*)edge->objectAtIndex(i))->setColor(ccc3(128, 128, 128));
    }
}
