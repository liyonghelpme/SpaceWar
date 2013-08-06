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
    void playNow(CCObject *);
    void playNow1(CCObject*);
    void playNow2(CCObject*);
    HelloWorld *logic;

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif
