#ifndef __NUMBER_H__
#define __NUMBER_H__
#include "cocos2d.h"
#include "Lightning.h"
#include "kazmath/vec3.h"
#include "kazmath/utility.h"
using namespace cocos2d;
class Number : public CCNode {
public:
    static Number*create();
    void init();
    void setValue(int v);
private:
    CCSpriteBatchNode *back;
    int value;
    void singleNum(int n, float, float);
};
#endif
