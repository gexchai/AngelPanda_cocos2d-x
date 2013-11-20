//
//  StartGameScene.h
//  AngelPanda
//
//  Created by happybubsy on 9/23/13.
//
//

#ifndef __AngelPanda__StartGameScene__
#define __AngelPanda__StartGameScene__

#include <iostream>
#include "cocos2d.h"


class StartGameScene : public cocos2d::CCLayer{
    
  
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
private:
    cocos2d::CCLabelTTF *helloLabel;
    cocos2d::CCSize size;
    
    cocos2d::CCSpriteBatchNode *batchNode;
    cocos2d::CCSprite *pandaBaby;
    cocos2d::CCSprite *carrot;
    cocos2d::CCSprite *pumpkin;
    
    void addWelcomeLabel();
    void addBackgroundPicture();
    void playBackgroundMusic();
    void addStartMenu();
    void startTapped();
    void addBatchNode();
    void addActions();
    
    CREATE_FUNC(StartGameScene);
    
};

#endif /* defined(__AngelPanda__StartGameScene__) */
