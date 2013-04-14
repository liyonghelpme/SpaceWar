#include "AI.h"
AI *AI::create() {
    AI *pRet = new AI();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void AI::init() {
}
