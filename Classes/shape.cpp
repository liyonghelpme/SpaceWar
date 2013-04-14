#include "shape.h"
#include "Lightning.h"

void makeScissor(CCSpriteBatchNode *back) {
    kmVec3 a, b;
    ccColor3B c = {255, 255, 255};

    kmVec3Fill(&a, 0, 9, 0);
    kmVec3Fill(&b, -9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
    kmVec3Fill(&a, 0, 9, 0);
    kmVec3Fill(&b, 9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
}

void makeHammer(CCSpriteBatchNode *back) {
    kmVec3 a, b;
    ccColor3B c = {255, 255, 255};

    kmVec3Fill(&a, -9, 9, 0);
    kmVec3Fill(&b, 9, 9, 0);
    makeLine("edge.png", a, b,15, c, back);

    kmVec3Fill(&a, -1, 9, 0);
    kmVec3Fill(&b, -1, -9, 0);
    makeLine("edge.png", a, b,15, c, back);

    kmVec3Fill(&a, 1, 9, 0);
    kmVec3Fill(&b, 1, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
}
void makeCloth(CCSpriteBatchNode *back) {
    kmVec3 a, b;
    ccColor3B c = {255, 255, 255};

    kmVec3Fill(&a, -9, 9, 0);
    kmVec3Fill(&b, -9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);

    kmVec3Fill(&a, -9, 9, 0);
    kmVec3Fill(&b, 9, 9, 0);
    makeLine("edge.png", a, b,15, c, back);

    kmVec3Fill(&a, 9, 9, 0);
    kmVec3Fill(&b, 9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);

    kmVec3Fill(&a, -9, -9, 0);
    kmVec3Fill(&b, 9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
}


void makeShape(int type, CCSpriteBatchNode *back) {
    if(type == 0) {
        makeScissor(back);
    } else if(type == 1) {
        makeCloth(back);
    } else if(type == 2) {
        makeHammer(back);
    }
}

