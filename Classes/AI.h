#ifndef __AI_H__
#define __AI_H__
#include "cocos2d.h"
using namespace cocos2d;
class AI : public CCNode {
public:
    static AI *create();
    void init();
    void update(float dt);
};
#endif
