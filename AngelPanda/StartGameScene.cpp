//
//  StartGameScene.cpp
//  AngelPanda
//
//  Created by happybubsy on 9/23/13.
//
//

#include "StartGameScene.h"
#include "SimpleAudioEngine.h"
#include "ActionLayer.h"


using namespace cocos2d;
using namespace CocosDenshion;


CCScene* StartGameScene::scene()
{
    
    CCScene * scene = CCScene::create();
    StartGameScene *layer = StartGameScene::create();
    
    scene->addChild(layer);
    
    return  scene;

}

void StartGameScene::addWelcomeLabel(){
    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
    helloLabel = CCLabelTTF::create("ANGEL PANDA", "Noteworthy-Bold", 50);
    helloLabel->setPosition(ccp(size.width/2,size.height*0.85));
    this->addChild(helloLabel,1);
    
}

void StartGameScene::addStartMenu(){
    
    
    CCLabelTTF *startLabel = CCLabelTTF::create("Start", "Noteworthy-Bold", 50);
    CCMenuItemLabel *startItem = CCMenuItemLabel::create(startLabel, this, menu_selector(StartGameScene::startTapped));
    startItem->setPosition(ccp(size.width/2,size.height*0.65));
    
    CCMenu *menu = CCMenu::create(startItem,NULL);
    menu->setPosition(CCPointZero);
    
    this->addChild(menu);
    
}

void StartGameScene::startTapped(){
    
    //transition
//    CCLog("Enter the game scene");
    
  //  CCDirector::sharedDirector()->replaceScene(ActionLayer::scene());
    
    CCTransitionCrossFade *trans = CCTransitionCrossFade::create(1, ActionLayer::scene());
    CCDirector::sharedDirector()->replaceScene(trans);
}

void StartGameScene::addBackgroundPicture(){
    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("bg-hd.png");
    bgSprite->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(bgSprite);
    
}

// add batch Node and its child

void StartGameScene::addBatchNode(){
    
    batchNode = CCSpriteBatchNode::create("panda-hd.png");
    this->addChild(batchNode,1);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("panda-hd.plist");
    
    pandaBaby = CCSprite::createWithSpriteFrameName("panda_1.png");
    carrot = CCSprite::createWithSpriteFrameName("carrot.png");
    pumpkin = CCSprite::createWithSpriteFrameName("pumpkin.png");
    
    pandaBaby->setPosition(ccp(size.width/2,size.height*0.35));
    carrot->setPosition(ccp(size.width*0.3,size.height*0.35));
    pumpkin->setPosition(ccp(size.width*0.7,size.height*0.35));
    
    batchNode->addChild(pandaBaby, 1);
    batchNode->addChild(carrot,1);
    batchNode->addChild(pumpkin,1);
    
    
}

//add actions of characters
void StartGameScene::addActions(){
    
    CCAction *pandaAction = CCJumpBy::create(10.0, ccp(size.width*0.65,size.height*0.45), 20, 10);
    pandaBaby->runAction(pandaAction);
    
}


//music

void StartGameScene::playBackgroundMusic(){
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("begin.mp3", true);
    
}
//init

bool StartGameScene::init()
{
    if(!CCLayer::init())
    {

        return  false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    this->addWelcomeLabel();
    this->addBackgroundPicture();
    this->playBackgroundMusic();
    this->addStartMenu();
    
    this->addBatchNode();
    
    this->addActions();
    
    return  true;
}


