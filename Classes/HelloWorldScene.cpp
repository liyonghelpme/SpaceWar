#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "Lightning.h"
#include "Layer3d.h"

USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCDirector::sharedDirector()->setContentScaleFactor(1.0);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize winPixle = CCDirector::sharedDirector()->getWinSizeInPixels();

    float contentScalor = CCDirector::sharedDirector()->getContentScaleFactor();

    printf("%f, %f, %f, %f\n", visibleSize.width, visibleSize.height, origin.x, origin.y);
    printf("winSize %f, %f, %f, %f, %f\n", winSize.width, winSize.height, winPixle.width, winPixle.height, contentScalor);

    Lightning *lightning = Lightning::create(NULL, 100, 10.0, 10.0, 20.0);
    lightning->midDisplacement(0, 160, 480, 160, 100.0);
    //lightning->testLine(300 ,400, 50, 200);
    //lightning->testLine(50 ,200, 300, 400);
    this->addChild(lightning);
    //lightning->runAction(CCFadeOut::create(2));

    Layer3d *layer3d = Layer3d::create();
    this->addChild(layer3d);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
