#include "Number.h"
Number *Number::create() {
   Number *pRet = new Number();
   pRet->init();
   pRet->autorelease();
   return pRet;
}
bool Number::init() {
    back = CCSpriteBatchNode::create("edge.png");
    addChild(back);
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    back->setBlendFunc(blendFunc);
	return true;
}
void Number::singleNum(int v, float offX, float offY) {
    //CCLog("singleNum %d %f", v, offX);
    float numHeight = 8;
    float numWidth = 8;
    int pos[] = {
        0, numHeight, 0, numHeight*2,
        0, numHeight*2, numWidth, numHeight*2,
        numWidth, numHeight*2, numWidth, numHeight,
        numWidth, numHeight, numWidth, 0,
        numWidth, 0, 0, 0,
        0, 0, 0, numHeight,
        0, numHeight, numWidth, numHeight,
        -1,
    };
    int zeroPos[] = {0, 1, 2, 3, 4, 5, -1};
    int onePos[] = {2, 3, -1};
    int twoPos[] = {1, 2, 6, 5, 4, -1};
    int threePos[] = {1, 2, 6, 3, 4, -1};
    int fourPos[] = {0, 6, 2, 3, -1};
    int fivePos[] = {1, 0, 6, 3, 4, -1};
    int sixPos[] = {1, 0, 5, 4, 3, 6, -1};
    int seventPos[] = {1, 2, 3, -1};
    int eightPos[] = {0, 1, 2, 3, 4, 5, 6, -1};
    int ninePos[] = {0, 1, 2, 6, 3, -1};

    int *posMap[] = {zeroPos, onePos, twoPos, threePos, fourPos, fivePos, sixPos, seventPos, eightPos, ninePos};
    int *showPos = posMap[v];

    //CCLog("show Number");
    kmVec3 a, b;
    ccColor3B c = {200, 255, 20};
    for(int i = 0; showPos[i] != -1; i++) {
        kmVec3Fill(&a, pos[showPos[i]*4]+offX, pos[showPos[i]*4+1]+offY, 0);
        kmVec3Fill(&b, pos[showPos[i]*4+2]+offX, pos[showPos[i]*4+3]+offY, 0);
        makeLine("edge.png", a, b, 10, c, back);
    }
}
void Number::setValue(int v) {
    value = v;
    back->removeAllChildren();
    int numbers[100];
    int len = 0;
    for(;true;) {
        int d = v%10;
        numbers[len++] = d;
        v = v/10;
        if(v == 0)
            break;
    }
    //CCLog("number is %d", len);
    int singleWidth = 15;
    int totalWidth = len*singleWidth;

    for(int i = len-1; i >= 0; i--) {
        //CCLog("each Number %d", numbers[i]);
        singleNum(numbers[i], (len-1-i)*singleWidth-totalWidth/2, -8/2);
    }
}
