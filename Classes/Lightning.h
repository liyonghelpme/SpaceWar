#ifndef __LIGHTNING_H__
#define __LIGHTNING_H__
#include "cocos2d.h"
#include "kazmath/vec3.h"
#include "string"
/*
参考实现 http://gamedev.tutsplus.com/tutorials/implementation/how-to-generate-shockingly-good-2d-lightning-effects/
调用中位移动函数生成从点100,200 到点150,200 的闪电图像 初始偏移量是100 
Lightning *lightning = Lightning::create(NULL, 100, 20.0, 10.0, 20.0);
lightning->midDisplacement(100, 200, 150, 200, 100.0);
this->addChild(lightning);

capacity 决定CCSpriteBatchNode 能够容纳的线段数量
*/
using namespace std;
using namespace cocos2d;
class Lightning;

class Line : public CCSprite
{
public:
    kmVec3 a, b;
    static Line *create(const char *fileName, kmVec3 &a, kmVec3 &b, float thickness, ccColor3B c);
};
void makeLine(const char *fileName, kmVec3 &a, kmVec3 &b, float thickness, ccColor3B &c, CCNode *parent);

#endif
