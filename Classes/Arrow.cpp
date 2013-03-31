#include "Arrow.h"

Arrow *Arrow::create() {
    Arrow *pRet = new Arrow();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Arrow::init() {
    back = CCSpriteBatchNode::create("edge.png");
    addChild(back);
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    back->setBlendFunc(blendFunc);
}
void Arrow::setStartEnd(kmVec3 &a, kmVec3 &b) {
    back->removeAllChildren();

    kmVec3 temp, e, f, g;
    kmVec3Subtract(&temp, &a, &b);
    kmVec3Normalize(&e, &temp);

    ccColor3B c = {20, 255, 20};
    makeLine("edge.png", a, b, 10, c, back);
    
    float theta = -30*kmPI/180;
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    temp.x = cosTheta*e.x-sinTheta*e.y;
    temp.y = sinTheta*e.x+cosTheta*e.y;
    kmVec3Scale(&f, &temp, 10);
    kmVec3Add(&g, &b, &f);
    makeLine("edge.png", b, g, 10, c, back);

    theta = 30*kmPI/180;
    cosTheta = cos(theta);
    sinTheta = sin(theta);

    temp.x = cosTheta*e.x-sinTheta*e.y;
    temp.y = sinTheta*e.x+cosTheta*e.y;
    kmVec3Scale(&f, &temp, 10);
    kmVec3Add(&g, &b, &f);
    makeLine("edge.png", b, g, 10, c, back);
}
