#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "Lightning.h"
#include "Bomb.h"
#include "Cannon.h"
#include "SpaceBack.h"
#include "Ship.h"
#include "stdlib.h"
#include "Number.h"
#include "Arrow.h"

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
void HelloWorld::randomPlanet() {
    for(int i = 0; i < 5; ){
        float x = random()%100000/100000.*(800-60)+30;
        float y = random()%100000/100000.*(480-60)+30;
        bool tooClose = false;
        CCLog("find position %f %f", x, y);
        for(unsigned int j = 0; j < planets->count(); j++) {
            Planet *neibor = (Planet*)planets->objectAtIndex(j);
            CCPoint p = neibor->getPosition();
            if(sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)) <= 100) {
                tooClose = true;
                break;
            }
        }
        if(!tooClose) {
            Planet *p = Planet::create();
            planets->addObject(p);
            addChild(p);
            p->setPosition(x, y);
            if(i == 0)
                p->setColor(0);
            else
                p->setColor(2);
            p->logic = this;


            p = Planet::create();
            planets->addObject(p);
            addChild(p);
            p->setPosition(-x+800, -y+480);
            if(i == 0)
                p->setColor(1);
            else
                p->setColor(2);
            p->logic = this;
            i++;
        }
    }
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    CCLog("initHello world");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    state = 0;

    planets = new CCArray();
    ships = new CCArray();

    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);
    holdTime = 1;

    //resourceSize / designSize
    CCDirector::sharedDirector()->setContentScaleFactor(1.0);
    //DesignResolution
    CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(800, 480, kResolutionExactFit);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize winPixle = CCDirector::sharedDirector()->getWinSizeInPixels();

    float contentScalor = CCDirector::sharedDirector()->getContentScaleFactor();

    printf("%f, %f, %f, %f\n", visibleSize.width, visibleSize.height, origin.x, origin.y);
    printf("winSize %f, %f, %f, %f, %f, %f, %f\n", winSize.width, winSize.height, winPixle.width, winPixle.height, contentScalor, visibleSize.width, visibleSize.height);

    
    Lightning *lightning = Lightning::create(NULL, 100, 10.0, 10.0, 20.0);
    lightning->midDisplacement(0, 160, 480, 160, 100.0);
    this->addChild(lightning);

    SpaceBack *sb = SpaceBack::create();
    addChild(sb);

    randomPlanet();


    WelcomeScene *welcome = WelcomeScene::create();
    welcome->logic = this;
    addChild(welcome);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

HelloWorld::~HelloWorld() {
    planets->release();
}

Planet *HelloWorld::checkInPlanet(CCPoint &pos) {
    for(unsigned int i = 0; i < planets->count(); i++) {
        Planet *p = (Planet *)planets->objectAtIndex(i);
        bool find = p->checkIn(pos.x, pos.y);
        if(find) {
            return p;
        }
    }
    return NULL;
}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCLog("hello touchBegan");

    startPlanet = NULL;
    endPlanet = NULL;
    arrow = NULL;
    passTime = 0;
    transferNum = 0;

    CCPoint pos = pTouch->getLocation();
    startPlanet = checkInPlanet(pos); 
    if(startPlanet->color != 0)
        startPlanet = NULL;
    if(startPlanet != NULL) {
        transferNum = startPlanet->shipNum/4;
        transferNum = transferNum > 0 ? transferNum : 1;
    }

    CCLog("pos is %f %f %x", pos.x, pos.y, startPlanet);
    return true;
}
//show arrow
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint tar = pTouch->getLocation();
    CCLog("move start %f %f", tar.x, tar.y);

    if(startPlanet != NULL) {
        if(startPlanet->color != 0) {
            arrow->removeFromParent();
            startPlanet = NULL;
            arrow = NULL;
        } else {
            endPlanet = checkInPlanet(tar);
            if(endPlanet != NULL) {
                tar = endPlanet->getPosition();
            }
            CCPoint st = startPlanet->getPosition();
            kmVec3 a = {st.x, st.y, 0};
            kmVec3 b = {tar.x, tar.y, 0};
                
            if(arrow == NULL) {
                arrow = Arrow::create();
                addChild(arrow);
            }

            CCLog("Move %f %f %f %f %x", a.x, a.y, tar.x, tar.y, arrow);
            arrow->setStartEnd(a, b);
        }
    }
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if(arrow != NULL) { 
        arrow->removeFromParent();
        arrow = NULL;
    }
    startPlanet = NULL;
    endPlanet = NULL;
}

void HelloWorld::sendShip() {
    int realTransferNum = transferNum <= startPlanet->shipNum ? transferNum : startPlanet->shipNum;
    if(realTransferNum > 0) {
        startPlanet->sendShip(realTransferNum, endPlanet);
        Ship *ship = Ship::create(); 
        ship->number = realTransferNum;
        ship->color = startPlanet->color;
        ship->startPlanet = startPlanet;
        ship->endPlanet = endPlanet;
        ship->logic = this;

        ship->startMove();

        ships->addObject(ship);
        addChild(ship);
    }
}
void HelloWorld::update(float dt) {
    if(startPlanet != NULL && endPlanet != NULL) {
        if(startPlanet->color == 0) {   
            if(passTime > holdTime) {
                sendShip();
                passTime -= holdTime;
            }
            passTime += dt;
        }
    }
}

void HelloWorld::onEnter() {
    CCLayer::onEnter();
    scheduleUpdate();
}

void HelloWorld::shipArrive(Ship *ship) {
    ships->removeObject(ship);
    ship->endPlanet->shipArrive(ship);
    ship->removeFromParent();
}
void HelloWorld::playNow() {
    state = 1;
}
