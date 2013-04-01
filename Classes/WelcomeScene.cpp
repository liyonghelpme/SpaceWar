#include "WelcomeScene.h"
bool WelcomeScene::init() {
    CCLayer::init();
    
    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);
    
    CCMenuItemFont::setFontSize(50);
    CCMenuItemFont *play = CCMenuItemFont::create("简单", this, menu_selector(WelcomeScene::playNow));
    CCMenuItemFont *play1 = CCMenuItemFont::create("中等", this, menu_selector(WelcomeScene::playNow1));
    CCMenuItemFont *play2 = CCMenuItemFont::create("困难", this, menu_selector(WelcomeScene::playNow2));
    play->setPosition(ccp(0, 60));
    play1->setPosition(ccp(0, 0));
    play2->setPosition(ccp(0, -60));

    CCMenu *menu = CCMenu::create(play, play1, play2, NULL);
    addChild(menu);

    return true;
}
void WelcomeScene::playNow() {
    removeFromParent();
    logic->playNow(0);
}

void WelcomeScene::playNow1() {
    removeFromParent();
    logic->playNow(1);
}

void WelcomeScene::playNow2() {
    removeFromParent();
    logic->playNow(2);
}

bool WelcomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){ return true;}
void WelcomeScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}
void WelcomeScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}
