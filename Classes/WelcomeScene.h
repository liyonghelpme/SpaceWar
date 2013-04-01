#ifndef __WELCOMESCENE_H__
#define __WELCOMESCENE_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class HelloWorld;
class WelcomeScene : public CCLayer {
public:
    virtual bool init();
    CREATE_FUNC(WelcomeScene);
    void playNow();
    void playNow1();
    void playNow2();
    HelloWorld *logic;

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif
