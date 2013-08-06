#ifndef __FAILORWIN_H__
#define __FAILORWIN_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class FailOrWin : public CCLayer {
public:
    static FailOrWin *create(const char *word);
    void init(const char *word); 
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    HelloWorld *logic;
    void playNow();
};
#endif
