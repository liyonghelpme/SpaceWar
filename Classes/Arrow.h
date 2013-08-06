#ifndef __ARROW_H__
#define __ARROW_H__
#include "cocos2d.h"
#include "Lightning.h"
#include "kazmath/vec3.h"
#include "kazmath/utility.h"
#include "math.h"
using namespace cocos2d;
class Arrow : public CCNode {
public:
    static Arrow*create();
    bool init();
    
    void setStartEnd(kmVec3 &a, kmVec3 &b);
private:
    CCSpriteBatchNode *back;
};
#endif
