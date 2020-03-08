#pragma once

#include "cocos2d.h"
#include "FlashTool.h"

class Hero: public cocos2d::Sprite
{
public:
	Hero();
	~Hero();
	virtual bool init();
	CREATE_FUNC(Hero);
};

