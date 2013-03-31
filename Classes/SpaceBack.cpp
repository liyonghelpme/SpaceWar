#include "SpaceBack.h"
SpaceBack *SpaceBack::create() {
    SpaceBack *pRet = new SpaceBack();
    pRet->autorelease();
    pRet->init();
    return pRet;
}
void SpaceBack::init() {
    back = CCSpriteBatchNode::create("edge.png");
    addChild(back);
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    back->setBlendFunc(blendFunc);

    int width = 800;
    int height = 480;
    int gridX = 40;
    int gridY = 40;
    ccColor3B c = {255, 255, 255};
    kmVec3 a, b;


    for(int i = 0; i < height/gridY+1; i++) {
        kmVec3Fill(&a, 0, gridY*i, 0);
        kmVec3Fill(&b, width, gridY*i, 0);
        Line *l = Line::create("edge.png", a, b, 2, c); 
        back->addChild(l);
    }

    for(int j = 0; j < width/gridX+1; j++) {
        kmVec3Fill(&a, gridX*j, 0, 0);
        kmVec3Fill(&b, gridX*j, height, 0);
        Line *l = Line::create("edge.png", a, b, 2, c); 
        back->addChild(l);
    }
}


