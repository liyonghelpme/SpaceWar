#include "Lightning.h"
#include "stdlib.h"
#include "cmath"
#include "kazmath/utility.h"

void makeLine(const char *fileName, kmVec3 &a, kmVec3 &b, float thickness, ccColor3B &c, CCNode *parent) {
    Line *l = Line::create(fileName, a, b, thickness, c);
    parent->addChild(l);
     
    kmVec3 temp;
    kmVec3Subtract(&temp, &b, &a);
    double deg = -atan2(temp.y, temp.x)*180/kmPI;

    CCSprite *s = CCSprite::create(fileName);
    s->setAnchorPoint(ccp(1.0, 0.5));
    s->setPosition(ccp(a.x, a.y));
    s->setRotation(deg);
    s->setScale(thickness/128);
    s->setColor(c);
    parent->addChild(s);

    s = CCSprite::create(fileName);
    s->setAnchorPoint(ccp(0, 0.5));
    s->setPosition(ccp(b.x, b.y));
    s->setRotation(deg);
    s->setFlipX(true);
    s->setScale(thickness/128);
    s->setColor(c);
    parent->addChild(s);
}

Line *Line::create(const char *fileName, kmVec3 &a, kmVec3 &b, float thickness, ccColor3B c)
{
    kmVec3 temp;
    kmVec3Subtract(&temp, &b, &a);
    double deg = -atan2(temp.y, temp.x)*180/kmPI;

    Line *line = new Line();
    line->initWithFile(fileName);
    line->setTextureRect(CCRectMake(63, 0, 1, 128));//宽第1的中间像素
    line->a = a;
    line->b = b;

    line->setAnchorPoint(ccp(0, 0.5));
    line->setScaleX(kmVec3Length(&temp)/1.0);
    line->setScaleY(thickness/128);
    line->setPosition(ccp(a.x, a.y));

    line->setRotation(deg);
    line->setColor(c);

    line->autorelease();
    return line;
}

