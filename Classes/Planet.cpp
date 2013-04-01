#include "Planet.h"
#include "math.h"
Planet *Planet::create(float r) {
    Planet *pRet = new Planet();
    pRet->init(r);
    pRet->autorelease();
    return pRet;
}
void Planet::init(float r) {
    shipNum = 0;
    maxShip = 999;
    productRate = 1;//100ms 生产1只飞船
    passTime = 0;
    back = CCSpriteBatchNode::create("edge.png");
    addChild(back);
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    back->setBlendFunc(blendFunc);

    int divideNum = 5;
    float delta = 2*kmPI/divideNum; 
    kmVec3 a, b;
    radius = r;
    ccColor3B c = {255, 255, 255};
    for(int i = 0; i < divideNum; i++) {

        kmVec3Fill(&a, cos(i*delta)*radius, sin(i*delta)*radius, 0);
        kmVec3Fill(&b, cos((i+1)*delta)*radius, sin((i+1)*delta)*radius, 0);

        CCLog("circle %f %f %f %f", a.x, a.y, b.x, b.y);
        
        makeLine("edge.png", a, b, 10, c, back);
    }
    number = Number::create();
    addChild(number);
    
    int dir = random()%2;
    if(dir == 0)
        dir = -1;
    float duration = (random()%1000+1000)/1000.;//1-2s
    back->runAction(CCRepeatForever::create(CCRotateBy::create(duration, dir*360)));
}
void Planet::setColor(int c) {
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
void Planet::update(float dt) {
    if(color != 2 && logic->state == 1) {
        if(passTime >= productRate) {
            if(shipNum < maxShip)
                shipNum += 1;
            passTime -= productRate;
        }
        passTime += dt;
    }
    number->setValue(shipNum);
}
void Planet::onEnter() {
    CCNode::onEnter();
    scheduleUpdate();
}
bool Planet::checkIn(float x, float y) {
    CCPoint pos = getPosition();
    return sqrt((pos.x-x)*(pos.x-x)+(pos.y-y)*(pos.y-y)) < radius;
}
void Planet::sendShip(int num, Planet *end) {
    shipNum -= num;

}
void Planet::shipArrive(Ship *ship) {
    if(ship->color == color)
        shipNum += ship->number;
    else {
        if(shipNum >= ship->number)
            shipNum -= ship->number;
        else {
            shipNum = ship->number-shipNum;
            setColor(ship->color);
        }
    }
}