#include "FailOrWin.h"
FailOrWin *FailOrWin::create(const char *word) {
    FailOrWin *pRet = new FailOrWin();
    pRet->init(word);
    pRet->autorelease();
    return pRet;
}
void FailOrWin::init(const char *word) {
    CCLayer::init();
    CCLog("FailOrWin %s", word);
    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);

    CCLabelTTF* label = CCLabelTTF::create(word, "", 30);
    label->setPosition(ccp(400, 340));
    label->setAnchorPoint(ccp(0.5, 0.5));
    addChild(label);
    CCMenuItemFont::setFontSize(20);
    CCMenuItemFont *play = CCMenuItemFont::create("重新开始", this, menu_selector(FailOrWin::playNow));
    CCMenu *menu = CCMenu::create(play, NULL);
    addChild(menu);
}
void FailOrWin::playNow() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = HelloWorld::scene();
    pDirector->replaceScene(pScene);
}

bool FailOrWin::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;}
void FailOrWin::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}
void FailOrWin::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}
