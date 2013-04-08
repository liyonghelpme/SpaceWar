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
#include "FailOrWin.h"
#include "stdlib.h"

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
//边缘 和 中心 去除掉
void HelloWorld::randomPlanet() {

    for(int i = 0; i < 5; ){
        float x = random()%100000/100000.*(400-planetRadius*2)+planetRadius;
        float y = random()%100000/100000.*(240-planetRadius*2)+planetRadius;
        int dir = random()%2;
        if(dir == 1)
            x = 800-x;
        dir = random()%2;
        if(dir == 1)
            y = 480-y;
        bool tooClose = false;
        //CCLog("find position %f %f", x, y);
        for(unsigned int j = 0; j < planets->count(); j++) {
            Planet *neibor = (Planet*)planets->objectAtIndex(j);
            CCPoint p = neibor->getPosition();
            if(sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)) <= minPlanetDistance) {
                tooClose = true;
                break;
            }
        }
        if(!tooClose) {
            int type = random()%3;
            Planet *p = Planet::create(planetRadius);
            planets->addObject(p);
            addChild(p);
            p->setPosition(x, y);
            p->setType(type);
            if(i == 0)
                p->setColor(0);
            else
                p->setColor(2);
            p->logic = this;



            p = Planet::create(planetRadius);
            planets->addObject(p);
            addChild(p);
            p->setPosition(-x+800, -y+480);
            p->setType(type);
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
    //CCLog("initHello world");
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    minPlanetDistance = 150;
    state = 0;
    countTime = 0;
    thinkTime = 1;
    holdTime = 0.5;
    planetRadius = 40;

    planets = new CCArray();
    ships = new CCArray();

    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);


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

    CCSprite *sp = CCSprite::create("edge.png");
    CCTexture2D *tex = sp->getTexture();
    tex->generateMipmap();

    ccTexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };    
    sp->getTexture()->setTexParameters(&texParams);


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
    //CCLog("hello touchBegan");

    startPlanet = NULL;
    endPlanet = NULL;
    arrow = NULL;
    passTime = 0;
    transferNum = 0;

    CCPoint pos = pTouch->getLocation();
    startPlanet = checkInPlanet(pos); 
    if(startPlanet != NULL && startPlanet->color != 0)
        startPlanet = NULL;
    if(startPlanet != NULL) {
        transferNum = startPlanet->shipNum/4;
        transferNum = transferNum > 0 ? transferNum : 1;
    }

    //CCLog("pos is %f %f %x", pos.x, pos.y, startPlanet);
    return true;
}
//show arrow
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint tar = pTouch->getLocation();
    //CCLog("move start %f %f", tar.x, tar.y);

    if(startPlanet != NULL) {
        if(startPlanet->color != 0) {
            arrow->removeFromParent();
            startPlanet = NULL;
            arrow = NULL;
        } else {
            Planet *old = endPlanet;
            endPlanet = checkInPlanet(tar);
            if(old != endPlanet)
                passTime = 0;
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

            //CCLog("Move %f %f %f %f %x", a.x, a.y, tar.x, tar.y, arrow);
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
    passTime = 0;
}

void HelloWorld::sendShip() {
    int realTransferNum = transferNum <= startPlanet->shipNum ? transferNum : startPlanet->shipNum;
    if(realTransferNum > 0) {
        startPlanet->sendShip(realTransferNum, endPlanet);
        Ship *ship = Ship::create(); 
        ship->number = realTransferNum;
        ship->setType(startPlanet->type);
        ship->setColor(startPlanet->color);

        ship->startPlanet = startPlanet;
        ship->endPlanet = endPlanet;
        ship->logic = this;

        ship->startMove();

        ships->addObject(ship);
        addChild(ship);
    }
}

//保证所有类型设定应该在 颜色设定之前生效
void HelloWorld::aiSendShip(Planet *start, Planet *end) {
    int aiTransferNum = start->shipNum/sendPercent;
    if(aiTransferNum > 0) {
        start->sendShip(aiTransferNum, end);
        Ship *ship = Ship::create(); 
        ship->number = aiTransferNum;
        ship->setType(start->type);
        ship->setColor(start->color);
        ship->startPlanet = start;
        ship->endPlanet = end;
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
                //CCLog("send shis %f %f", passTime, holdTime);
                sendShip();
                passTime -= holdTime;
            }
            passTime += dt;
        }
    }
    think(dt);
}

void HelloWorld::onEnter() {
    CCLayer::onEnter();
    scheduleUpdate();
}

//一方的星球 和 飞船全部消失的时候 就失败了 失败页面 重新弹出新的场景
void HelloWorld::shipArrive(Ship *ship) {
    ships->removeObject(ship);
    ship->endPlanet->shipArrive(ship);
    ship->removeFromParent();
    int countRed = 0;
    int countBlue = 0;
    int shipRed = 0;
    int shipBlue = 0;
    for(unsigned int i = 0; i < planets->count(); i++) {
        Planet *p = (Planet *)planets->objectAtIndex(i);
        if(p->color == 0)
            countRed++;
        else if(p->color == 1)
            countBlue++;
    }
    for(unsigned int i = 0; i < ships->count(); i++) {
        Ship *s = (Ship*)ships->objectAtIndex(i);
        if(s->color == 0)
            shipRed++;
        else if(s->color == 1)
            shipBlue++;
    }
    //CCLog("red blue %d %d %d %d", countRed, shipRed, countBlue, shipBlue);
    if(countRed == 0 && shipRed == 0)
        failNow();
    else if(countBlue == 0 && shipBlue == 0)
        winNow();
}
void HelloWorld::failNow(){
    if(state == 1) {
        state = 2;
        FailOrWin *fail = FailOrWin::create("你失败了!!");
        addChild(fail);
    }
}
void HelloWorld::winNow() {
    if(state == 1) {
        state = 3;
        FailOrWin *fail = FailOrWin::create("你胜利了!!");
        addChild(fail);
        //CCLog("add Fail or Win!");
    }
}
void HelloWorld::playNow(int aiDegree) {
    if(aiDegree == 0) {
        thinkTime = 2;
        sendPercent = 4;
    } else if(aiDegree == 1) {
        thinkTime = 0.8;
        sendPercent = 3;
    } else {
        thinkTime = 0.5;
        sendPercent = 2;
    }

    state = 1;
}
void HelloWorld::think(float dt) {
    if(state == 1) {
        if(countTime >= thinkTime) {
            //two stage initial
            CCArray *bluePlanets = new CCArray();
            bluePlanets->init();
            CCArray *redPlanets = new CCArray();
            redPlanets->init();
            for(unsigned int i = 0; i < planets->count(); i++) {
                Planet *p = (Planet*)planets->objectAtIndex(i);
                if(p->color == 1) {
                    bluePlanets->addObject(p);
                } else {
                    redPlanets->addObject(p);
                }
            }
            if(bluePlanets->count() > 0 && redPlanets->count() > 0) {
                int randBlue = random()%bluePlanets->count();
                float minCost = 999999;
                Planet *target = NULL;
                //最近消耗最少兵力的红色星球 
                Planet *blue = (Planet *)bluePlanets->objectAtIndex(randBlue);
                CCPoint curPos = blue->getPosition();
                for(int i = 0; i < redPlanets->count(); i++) {
                    Planet *p = (Planet*)redPlanets->objectAtIndex(i);
                    CCPoint pos = p->getPosition();
                    float dx = curPos.x-pos.x;
                    float dy = curPos.y-pos.y;
                    float cost = sqrt(dx*dx+dy*dy);
                    if(cost < minCost) {
                        target = p;
                        minCost = cost;
                    }
                }
                if(target != NULL)
                    aiSendShip((Planet *)bluePlanets->objectAtIndex(randBlue), target);                
            }
            bluePlanets->release();
            redPlanets->release();

            countTime -= thinkTime;
        }
        countTime += dt;    
    }
}
