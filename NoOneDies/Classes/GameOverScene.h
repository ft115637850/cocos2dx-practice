#pragma once

#include <cocos2d.h>

class GameOverScene: public cocos2d::LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(GameOverScene);
	static cocos2d::Scene* createScene();
};

