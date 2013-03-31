#include "WelcomeScene.h"
bool WelcomeScene::init() {
    CCLayer::init();
    
    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);
    
    CCMenuItemFont::setFontSize(20);
    CCMenuItemFont *play = CCMenuItemFont::create("Play", this, menu_selector(WelcomeScene::playNow));
    CCMenu *menu = CCMenu::create(play, NULL);
    addChild(menu);

    return true;
}
void WelcomeScene::playNow() {
    removeFromParent();
    logic->playNow();
}
bool WelcomeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){}
void WelcomeScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}
void WelcomeScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}
