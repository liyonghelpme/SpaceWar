#include "shape.h"
#include "Lightning.h"

void makeScissor(CCNode *back) {
    kmVec3 a, b;
    ccColor3B c = {255, 255, 255};

    kmVec3Fill(&a, 0, 9, 0);
    kmVec3Fill(&b, -9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
    kmVec3Fill(&a, 0, 9, 0);
    kmVec3Fill(&b, 9, -9, 0);
    makeLine("edge.png", a, b,15, c, back);
}

void makeHammer(CCNode *back) {
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
void makeCloth(CCNode *back) {
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


void makeShape(int type, CCNode *back) {
    if(type == 0) {
        makeScissor(back);
    } else if(type == 1) {
        makeCloth(back);
    } else if(type == 2) {
        makeHammer(back);
    }
}

