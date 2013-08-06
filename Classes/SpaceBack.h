#ifndef __SPACEBACK__H
#define __SPACEBACK__H
#include "cocos2d.h"
#include "Lightning.h"
#include "kazmath/vec3.h"
using namespace cocos2d;
class SpaceBack : public CCNode {
public:
    static SpaceBack *create();
    bool init();

private:
   CCSpriteBatchNode *back; 
};
#endif
