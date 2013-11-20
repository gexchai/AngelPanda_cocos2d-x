//
//  SpriteArray.h
//  AngelPanda
//
//  Created by happybubsy on 9/24/13.
//
//

#ifndef __AngelPanda__SpriteArray__
#define __AngelPanda__SpriteArray__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class SpriteArray : public cocos2d::CCObject{
    

    
public:
    CCArray *array;
    
    bool initWithParameters(int capacity,CCString *spriteFrameName, CCSpriteBatchNode* batchNode);
    void nextSprite();
    int nextItem;
};





#endif /* defined(__AngelPanda__SpriteArray__) */
