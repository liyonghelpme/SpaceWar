#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Planet.h"
#include "math.h"
#include "Arrow.h"
#include "Ship.h"
#include "WelcomeScene.h"

class Planet;
class Ship;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    void randomPlanet();
    ~HelloWorld();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void update(float dt);
    void shipArrive(Ship*);
    void playNow();

    int state;
private:
    CCArray *planets;
    Planet *startPlanet;
    Planet *endPlanet;

    Arrow *arrow;
    Planet *checkInPlanet(CCPoint&);
    float passTime;
    int transferNum;
    int holdTime;
    CCArray *ships;
    void sendShip();
};

#endif // __HELLOWORLD_SCENE_H__
