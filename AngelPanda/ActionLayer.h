//
//  ActionLayer.h
//  AngelPanda
//
//  Created by happybubsy on 9/23/13.
//
//

#ifndef __AngelPanda__ActionLayer__
#define __AngelPanda__ActionLayer__

#include <iostream>
#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"

USING_NS_CC;

typedef enum {
    KENDREASONWIN,
    KENDREASONLOSE
    
}EndReason;

class ActionLayer: public cocos2d::CCLayer{
    
private:
    
    int lives;
    
    int score;
    
    double gameOverTime;
    bool gameOver;
    
    CCSpriteBatchNode *batchNode;
    CCSprite *panda;
    
    CCParallaxNodeExtras *backgroundNode;
    CCSprite *mainBg;
    CCSprite *mainBg2;
    CCSprite *cloud1;
    CCSprite *cloud2;
    CCSprite *cloud3;
    
    CCSize size;
    
    
    CCArray *missleArray;
    CCArray *groundObjectsArray;
    CCArray *airObjectsArray;
    CCArray *coinsArray;
    CCArray *aidArray;
    
    int nextMissle;
    int nextGroundObject;
    int nextAirObject;
    int nextCoin;
    int nextAid;
    
    float curTimeMillis;
    
    double nextMissleSpawn;
    double nextGroundObstacleSpawn;
    double nextAirObstacleSpawn;
    double nextCoinSpawn;
    double nextAidSpawn;
    
    float playerPointsPerSecY;
    
    void playBackgroundMusic();
    
    void setBackground();
    void addCharacter();
    
    void createMissleArray();
    void createGroundObstacleArray();
    void createAirObstacleArray();
    void createCoinArray();
    void createAidArray();
    
    void updateMissleArray();
    void updateGroundObstacleArray();
    void updateAirObstacleArray();
    void updateCoinArray();
    void updateAidArray();
    
    void updateCollision(float dt);
    
    void updatePlayerPos(float dt);

    void updateGameLogic(float dt);
    
    void updateBackgroundScroll(float dt);
    void update(float dt);
    
    void endGame(EndReason endReason);
    
    void restartTapped();
    
public:
    //
    virtual bool init();
    CCAnimation * createAnimWithSingleFrameN(const char* name,int count,float delay);
    
    float randomValueBetween(float low,float high);
    void setInvisible(CCNode *node);
    float getTimeTick();
    

    
    static cocos2d::CCScene * scene();
    
    CREATE_FUNC(ActionLayer);
    
    virtual void registerWithTouchDispatcher(void);
    
    //addStandardDelegate()
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);

    
    
};




#endif /* defined(__AngelPanda__ActionLayer__) */
