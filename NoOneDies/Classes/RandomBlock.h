#pragma once
#include "cocos2d.h"

class RandomBlock: public cocos2d::Sprite
{
public:
	RandomBlock();
	~RandomBlock();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(RandomBlock);
};

