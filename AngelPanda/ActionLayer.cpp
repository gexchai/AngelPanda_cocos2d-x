//
//  ActionLayer.cpp
//  AngelPanda
//
//  Created by happybubsy on 9/23/13.
//
//

#include "ActionLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace std;


#pragma mark 实现辅助方法

float ActionLayer::randomValueBetween(float low, float high){
    
    return (((float)arc4random()/0xFFFFFFFFu)*(high-low))+low;
    
}

float ActionLayer::getTimeTick(){
    
    
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec*1000)+(time.tv_usec/1000);
    return (float)millisecs;
}


void ActionLayer::setInvisible(cocos2d::CCNode *node){
    
    node->setVisible(false);
    
}
#pragma mark 创建怪物阵列（导弹，地面，空中，硬币，急救包）~
//导弹
void ActionLayer::createMissleArray()
{
    
    #define kNumberOfMissles 15
    missleArray = new CCArray();
    for (int i =0;i< kNumberOfMissles;++i){
        CCSprite *missle = CCSprite::createWithSpriteFrameName("missle.png");
        missle->setVisible(false);
        batchNode->addChild(missle);
        missleArray->addObject(missle);
    }
    
    
//    CCLog("Successfully created the missle array,now it contains %d missles",missleArray->count());
}

void ActionLayer::updateMissleArray(){
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > nextMissleSpawn) {
        
        float randMillisecs = randomValueBetween(10.0,12.0) * 1000;
        nextMissleSpawn = randMillisecs + curTimeMillis;
        
        float randY = randomValueBetween(50.0,size.height-50);
        float randDuration = randomValueBetween(0.3,0.5);
        
        CCSprite *missle = (CCSprite *)missleArray->objectAtIndex(nextMissle);
        nextMissle++;
        
        if (nextMissle >= missleArray->count())
            nextMissle = 0;
        
        missle->stopAllActions();
        missle->setPosition( ccp(size.width+missle->getContentSize().width/2, randY));
        missle->setVisible(true);
        
        
        missle->runAction(CCSequence::create(CCDelayTime::create(4.0),
                                             CCMoveBy::create(randDuration, ccp(-1.3*size.width-missle->getContentSize().width, 0)), CCCallFuncN::create(this, callfuncN_selector(ActionLayer::setInvisible)),
                                                  NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
                                             ));        
    }
    
    
}

//地面怪物
void ActionLayer::createGroundObstacleArray(){
    
#define kNumberOfGroundObstacles 20
    
    groundObjectsArray = new CCArray();
    
    for (int i =0;i< kNumberOfGroundObstacles;++i){
        CCSprite *groundObstacle = CCSprite::createWithSpriteFrameName("carrot.png");
        groundObstacle->setVisible(false);
        batchNode->addChild(groundObstacle);
        groundObjectsArray->addObject(groundObstacle);
    }
    
}

void ActionLayer::updateGroundObstacleArray(){
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > nextGroundObstacleSpawn) {
        
        float randMillisecs = randomValueBetween(3.0,5.0) * 1000;
        nextGroundObstacleSpawn = randMillisecs + curTimeMillis;
        
        float randDuration = randomValueBetween(1.6,2.0);
        
        CCSprite *groundObstacle = (CCSprite *)groundObjectsArray->objectAtIndex(nextGroundObject);
        nextGroundObject++;
        
        if (nextGroundObject >= groundObjectsArray->count())
            nextGroundObject = 0;
        
        //设置一个随机大小
        int randNum = arc4random()%3;
        if(randNum ==0){
            groundObstacle->setScale(0.4);
        }else if(randNum ==1){
            groundObstacle->setScale(0.6);
        }else {
            groundObstacle->setScale(0.9);
        }
        
        groundObstacle->stopAllActions();
        groundObstacle->setPosition( ccp(size.width+groundObstacle->getContentSize().width/2, groundObstacle->getContentSize().height/2));
        groundObstacle->setVisible(true);
        

        groundObstacle->runAction(CCSequence::create(CCDelayTime::create(4.0),
                                                     CCMoveBy::create(randDuration, ccp(-1.3*size.width-groundObstacle->getContentSize().width, 0)),
                                                     CCCallFuncN::create(this, callfuncN_selector(ActionLayer::setInvisible)),
                                                     NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
                                             ));
    }
    
}

//空中怪物
void ActionLayer::createAirObstacleArray(){
    
#define kNumberOfAirObstacles 20
    
    airObjectsArray = new CCArray();
    
    for (int i =0;i< kNumberOfAirObstacles;++i){
        CCSprite *airObstacle = CCSprite::createWithSpriteFrameName("plane3.png");
        airObstacle->setVisible(false);
        batchNode->addChild(airObstacle);
        airObjectsArray->addObject(airObstacle);
    }
    
    
}

void ActionLayer::updateAirObstacleArray(){
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > nextAirObstacleSpawn) {
        
        float randMillisecs = randomValueBetween(3.0,5.0) * 1000;
        nextAirObstacleSpawn = randMillisecs + curTimeMillis;
        
        float randDuration = randomValueBetween(1.6,2.0);
        float randY = randomValueBetween(50.0,size.height-50);
        
        CCSprite *airObstacle = (CCSprite *)airObjectsArray->objectAtIndex(nextAirObject);
        nextAirObject++;
        
        if (nextAirObject >= airObjectsArray->count())
            nextAirObject = 0;
        
        //设置一个随机大小
        int randNum = arc4random()%3;
        if(randNum ==0){
            airObstacle->setScale(0.6);
        }else if(randNum ==1){
            airObstacle->setScale(0.8);
        }else {
            airObstacle->setScale(1.2);
        }
        
        airObstacle->stopAllActions();
        airObstacle->setPosition( ccp(size.width+airObstacle->getContentSize().width/2, randY));
        airObstacle->setVisible(true);
        
        
        airObstacle->runAction(CCSequence::create(CCDelayTime::create(4.0),
                                                  CCMoveBy::create(randDuration, ccp(-1.3*size.width-airObstacle->getContentSize().width, 0)),
                                                  CCCallFuncN::create(this, callfuncN_selector(ActionLayer::setInvisible)),
                                                  NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
                                                     ));
    }
    
}

//金币
void ActionLayer::createCoinArray(){
    
#define kNumberOfCoins 40
    
    coinsArray = new CCArray();
    
    for (int i =0;i< kNumberOfCoins;++i){
        CCSprite *coin = CCSprite::createWithSpriteFrameName("coin.png");
        coin->setVisible(false);
        batchNode->addChild(coin);
        coinsArray->addObject(coin);
    }
    
    
}

void ActionLayer::updateCoinArray(){
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > nextAirObstacleSpawn) {
        
        float randMillisecs = randomValueBetween(3.0,6.0) * 1000;
        nextAirObstacleSpawn = randMillisecs + curTimeMillis;
        
        float randDuration = randomValueBetween(1.6,2.0);
        float randY = randomValueBetween(size.height/2,size.height-100);
        
        CCSprite *coin = (CCSprite *)coinsArray->objectAtIndex(nextCoin);
        nextCoin++;
        
        if (nextCoin >= coinsArray->count())
            nextCoin = 0;
        
        coin->stopAllActions();
        coin->setPosition( ccp(size.width+coin->getContentSize().width/2, randY+30));
        coin->setVisible(true);
        
        
        coin->runAction(CCSequence::create(CCDelayTime::create(4.0),
                                           CCMoveBy::create(randDuration, ccp(-1.3*size.width-coin->getContentSize().width, 0)),
                                           CCCallFuncN::create(this, callfuncN_selector(ActionLayer::setInvisible)),
                                           NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
                                                  ));
    }
    
}
//急救包
void ActionLayer::createAidArray(){
    
    
#define kNumberOfAids 20
    
    aidArray = new CCArray();
    
    for (int i =0;i< kNumberOfAids;++i){
        CCSprite *aid = CCSprite::createWithSpriteFrameName("aid.png");
        aid->setVisible(false);
        batchNode->addChild(aid);
        aidArray->addObject(aid);
    }
    
    
    
}

void ActionLayer::updateAidArray(){
    
    float curTimeMillis = getTimeTick();
    if (curTimeMillis > nextAidSpawn) {
        
        float randMillisecs = randomValueBetween(3.0,5.0) * 1000;
        nextAidSpawn = randMillisecs + curTimeMillis;
        
        float randDuration = randomValueBetween(1.6,2.0);
        float randY = randomValueBetween(50.0,size.height-50);
        
        CCSprite *aid = (CCSprite *)aidArray->objectAtIndex(nextAid);
        nextAid++;
        
        if (nextAid >= aidArray->count())
            nextAid = 0;
        
        //设置一个随机大小
        int randNum = arc4random()%3;
        if(randNum ==0){
            aid->setScale(0.6);
        }else if(randNum ==1){
            aid->setScale(0.8);
        }else {
            aid->setScale(1.2);
        }
        
        aid->stopAllActions();
        aid->setPosition( ccp(size.width+aid->getContentSize().width/2, randY));
        aid->setVisible(true);
        
        
        aid->runAction(CCSequence::create(CCDelayTime::create(4.0),
                                          CCMoveBy::create(randDuration, ccp(-1.3*size.width-aid->getContentSize().width, 0)),
                                          CCCallFuncN::create(this, callfuncN_selector(ActionLayer::setInvisible)),
                                          NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
                                                  ));
    }

    
}

#pragma mark 创建场景

CCScene* ActionLayer::scene()
{
    
    CCScene *scene = CCScene::create();
    
    ActionLayer *layer = ActionLayer::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

#pragma mark 创建动画

CCAnimation* ActionLayer::createAnimWithSingleFrameN(const char *name, int count, float delay)
{
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCArray* framesArray = CCArray::createWithCapacity(count);
    
    char str[80];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, "%s%d.png", name, i);
        framesArray->addObject(cache->spriteFrameByName(str));
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesArray);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);
    
    return animation;
}

#pragma mark 添加游戏主角

void ActionLayer::addCharacter()
{
    batchNode = CCSpriteBatchNode::create("panda-hd.png");
    this->addChild(batchNode);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panda-hd.plist");
    
    panda = CCSprite::createWithSpriteFrameName("panda_1.png");
    panda->setPosition(ccp(-panda->getContentSize().width/2,16+panda->getContentSize().height/2));
    batchNode->addChild(panda,1);
    
    //add action
    CCFiniteTimeAction *easeOutAction = CCEaseOut::create(
                                                    CCMoveBy::create(0.5, ccp(panda->getContentSize().width/2+size.width*0.3,0))
                                                          , 4.0);
    CCFiniteTimeAction *easeInOutAction = CCEaseInOut::create(
                                                    CCMoveBy::create(0.5, ccp(-size.width*0.2,0))
                                                              , 4.0);
    CCSequence *sequenceActions = CCSequence::create(easeOutAction,easeInOutAction,NULL);
    
    panda->runAction(sequenceActions);
                                                          
    //add animation
    
    this->createAnimWithSingleFrameN("panda_", 2, 0.1);
}

#pragma mark 设置背景

void ActionLayer::setBackground()
{
    
    mainBg = CCSprite::create("bg-hd.png");
    mainBg2 = CCSprite::create("grass-hd.png");
    
    mainBg->setPosition(ccp(size.width/2,size.height/2));
    mainBg2->setPosition(ccp(size.width/2,0));
    
    this->addChild(mainBg,-1);
    this->addChild(mainBg2,0);
    
    backgroundNode = CCParallaxNodeExtras::node();
    this->addChild(backgroundNode,-1);
    

    cloud1 = CCSprite::create("bg_cloud_1-hd.png");
    cloud2 = CCSprite::create("bg_cloud_2-hd.png");
    cloud3 = CCSprite::create("bg_cloud_3-hd.png");
    
    CCPoint cloudSpeed1 = ccp(0.1,0.1);
    CCPoint cloudSpeed2 = ccp(0.05,0.05);
    
    backgroundNode->addChild(cloud1, 0, cloudSpeed1, ccp(size.width*0.5,size.height*0.6));
    backgroundNode->addChild(cloud2, 0, cloudSpeed1, ccp(size.width*0.9,size.height*0.6));
    backgroundNode->addChild(cloud3, 0, cloudSpeed2, ccp(0,size.height*0.6));
    
    
}

#pragma mark 游戏机制

void ActionLayer::update(float dt)
{
    
    //update scroll background
    
    CCPoint backgroundScrollVel = ccp(-1000,0);
    backgroundNode->setPosition(ccpAdd(backgroundNode->getPosition(), ccpMult(backgroundScrollVel, dt)));
    
    CCArray *clouds = CCArray::createWithCapacity(3);
    clouds->addObject(cloud1);
    clouds->addObject(cloud2);
    clouds->addObject(cloud3);
    
    for (int i= 0;i<clouds->count();i++)
    {
        CCSprite *cloud = (CCSprite*)(clouds->objectAtIndex(i));
        float xPosition = backgroundNode->convertToNodeSpace(cloud->getPosition()).x;
        float fullWidth = cloud->getContentSize().width;
        
        if(xPosition <-fullWidth/2){
            
            backgroundNode->incrementOffset(ccp(cloud->getContentSize().width*2,0), cloud);
        }
        
    }

    
    this->updatePlayerPos(dt);
    
    this->updateMissleArray();
    
    this->updateGroundObstacleArray();

    this->updateAirObstacleArray();
    
    this->updateAidArray();
    
    this->updateCoinArray();
    
    
    //碰撞机制
    this->updateCollision(dt);
    
    this->updateGameLogic(dt);
}

void ActionLayer::updateBackgroundScroll(float dt){
    
    //update background
   
        if(backgroundNode->getPosition().x <0){
    
//            backgroundNode->setPosition(-size.width*2,size.height/2);
               backgroundNode->setPosition(-size.width,size.height/2);
        }

    
    
}

#pragma mark 播放背景音乐

void ActionLayer::playBackgroundMusic()
{
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("begin.mp3", true);
    SimpleAudioEngine::sharedEngine()->preloadEffect("angry_girl.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("babycry.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("babylaugh.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("coin.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("missle_warning.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("mother.mp3");
    
}

#pragma mark 触摸代理
void ActionLayer::registerWithTouchDispatcher(void){
    
    //委托，优先级
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, kCCMenuHandlerPriority);
    
    
}

#pragma mark 触摸机制处理

void ActionLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    playerPointsPerSecY =100.0f;
}

void ActionLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    
    playerPointsPerSecY =-150.0f;
}


void ActionLayer::updatePlayerPos(float dt){
    
    float maxY = size.height - panda->getContentSize().height/2;
    float minY = 15 + panda->getContentSize().height/2;
    
    float newY = panda->getPosition().y +(playerPointsPerSecY *dt);
    newY = MIN(MAX(newY,minY),maxY);
    panda->setPosition(ccp(panda->getPosition().x, newY));
    
}

#pragma mark 碰撞机制
void ActionLayer::updateCollision(float dt){
    
    CCObject *missleObject;
    CCObject *aidObject;
    CCObject *airObstacleObject;
    CCObject *groundObstacleObject;
    CCObject *coinObject;
    
    //熊猫和导弹碰撞
    CCARRAY_FOREACH(missleArray, missleObject){
        
         CCSprite *missle = (CCSprite *)missleObject;
        if(!missle->isVisible()){
            continue;
        }
    
        if(panda->boundingBox().intersectsRect(missle->boundingBox() )){
            
            //发生了碰撞
            missle->setVisible(false);
            panda->runAction(CCBlink::create(1.0, 9));
            lives-=2;
            
            //播放音效
            SimpleAudioEngine::sharedEngine()->playEffect("angry_girl.mp3");
            
        }
    }
    
    //熊猫和应急包碰撞
    CCARRAY_FOREACH(aidArray, aidObject){
        
        CCSprite *aid = (CCSprite *)aidObject;
        if(!aid->isVisible()){
            continue;
        }
        
        if(panda->boundingBox().intersectsRect(aid->boundingBox() )){
            
            //发生了碰撞
            aid->setVisible(false);
        //    panda->runAction(CCBlink::create(1.0, 9));
            lives++;
            //播放音效
            SimpleAudioEngine::sharedEngine()->playEffect("mother.mp3");
            
        }
    }
    
    //熊猫和空中障碍物碰撞
    CCARRAY_FOREACH(airObjectsArray, airObstacleObject){
        
        CCSprite *airObstacle = (CCSprite *)airObstacleObject;
        if(!airObstacle->isVisible()){
            continue;
        }
        
        if(panda->boundingBox().intersectsRect(airObstacle->boundingBox() )){
            
            //发生了碰撞
            airObstacle->setVisible(false);
            panda->runAction(CCBlink::create(1.0, 9));
            lives--;
            //播放音效
            SimpleAudioEngine::sharedEngine()->playEffect("angry_girl.mp3");
            
        }
    }
    
    //熊猫和地面障碍物碰撞
    CCARRAY_FOREACH(groundObjectsArray, groundObstacleObject){
        
        CCSprite *groundObstacle = (CCSprite *)groundObstacleObject;
        if(!groundObstacle->isVisible()){
            continue;
        }
        
        if(panda->boundingBox().intersectsRect(groundObstacle->boundingBox() )){
            
            //发生了碰撞
            groundObstacle->setVisible(false);
            panda->runAction(CCBlink::create(1.0, 9));
            lives--;
            //播放音效
            SimpleAudioEngine::sharedEngine()->playEffect("angry_girl.mp3");
            
        }
    }
    
    //熊猫和金币碰撞
    CCARRAY_FOREACH(coinsArray, coinObject){
        
        CCSprite *coin = (CCSprite *)coinObject;
        if(!coin->isVisible()){
            continue;
        }
        
        if(panda->boundingBox().intersectsRect(coin->boundingBox() )){
            
            //发生了碰撞
            coin->setVisible(false);
//            panda->runAction(CCBlink::create(1.0, 9));
//            lives--;
            
            SimpleAudioEngine::sharedEngine()->playEffect("coin.mp3");
        }
    }
    
}

#pragma mark 游戏机制

void ActionLayer::endGame(EndReason endReason){
    
    if(gameOver)
        return;
    gameOver = true;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    char message[100] = "Congratulations, you win!";
    
    if ( endReason == KENDREASONLOSE)
        strcpy(message,"Sorry ,you lose!");
    CCLabelBMFont * label ;
    label = CCLabelBMFont::create(message, "Arial.fnt");
    label->setScale(0.1);
    label->setPosition(ccp(winSize.width/2 , winSize.height*0.6));
    this->addChild(label);
    
    CCLabelBMFont * restartLabel;
    strcpy(message,"Restart");
    restartLabel = CCLabelBMFont::create(message, "Arial.fnt");
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(ActionLayer::restartTapped) );
    restartItem->setScale(0.1);
    restartItem->setPosition( ccp(winSize.width/2, winSize.height*0.4));
    
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    // clear label and menu
    restartItem->runAction(CCScaleTo::create(0.5, 1.0));
    label ->runAction(CCScaleTo::create(0.5, 1.0));
    // Terminate update callback
    this->unscheduleUpdate();

    
    
}

void ActionLayer::restartTapped(){
    
    CCDirector::sharedDirector()->replaceScene
    (CCTransitionZoomFlipX::create(0.5, this->scene()));
    // reschedule
    this->scheduleUpdate();
    
}

void ActionLayer::updateGameLogic(float dt){
    
    if(lives<=0){
        
        panda->stopAllActions();
        panda->setVisible(false);
        this->endGame(KENDREASONLOSE);
    }else if(curTimeMillis >= gameOverTime){
        this->endGame(KENDREASONWIN);
    }
    
}

#pragma mark 初始化

bool ActionLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    lives = 5;
    score = 100;
    
    double curTime = getTimeTick();
    gameOverTime = curTime +30000;
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    this->playBackgroundMusic();
    this->setBackground();
    this->addCharacter();
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(ActionLayer::updateBackgroundScroll), 6.0);
    
    
    this->setTouchEnabled(true);
    
    this->createMissleArray();
    this->createGroundObstacleArray();
    this->createAirObstacleArray();
    this->createCoinArray();
    this->createAidArray();
    
    return true;
}


